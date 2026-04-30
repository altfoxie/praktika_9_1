#include "perspective.h"
#include "../common/menu.h"
#include <SDL2/SDL.h>
#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string_view>

namespace {

template <typename T>
bool read_positive(std::string_view prompt, T &value) {
    std::cout << prompt;
    if (std::cin >> value && value > 0) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return true;
    }
    std::cout << "Ошибка: значение должно быть положительным.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
}

// 4x4 матрица (row-major)
struct Mat4 {
    double m[4][4] = {};
};

// Перспективная матрица проекции (OpenGL-стиль, NDC z в [-1, 1])
Mat4 perspective_matrix(double fov_deg, double aspect, double near_z, double far_z) {
    Mat4 mat;
    double fov_rad = fov_deg * M_PI / 180.0;
    double f = 1.0 / std::tan(fov_rad / 2.0);
    mat.m[0][0] = f / aspect;
    mat.m[1][1] = f;
    mat.m[2][2] = (far_z + near_z) / (near_z - far_z);
    mat.m[2][3] = (2.0 * far_z * near_z) / (near_z - far_z);
    mat.m[3][2] = -1.0;
    return mat;
}

struct Vec4 { double x, y, z, w; };

Vec4 mat4_mul_vec4(const Mat4 &m, Vec4 v) {
    return {
        m.m[0][0]*v.x + m.m[0][1]*v.y + m.m[0][2]*v.z + m.m[0][3]*v.w,
        m.m[1][0]*v.x + m.m[1][1]*v.y + m.m[1][2]*v.z + m.m[1][3]*v.w,
        m.m[2][0]*v.x + m.m[2][1]*v.y + m.m[2][2]*v.z + m.m[2][3]*v.w,
        m.m[3][0]*v.x + m.m[3][1]*v.y + m.m[3][2]*v.z + m.m[3][3]*v.w,
    };
}

void print_matrix(const Mat4 &mat) {
    std::cout << std::fixed << std::setprecision(4);
    for (int i = 0; i < 4; i++) {
        std::cout << "[ ";
        for (int j = 0; j < 4; j++) {
            std::cout << std::setw(10) << mat.m[i][j] << " ";
        }
        std::cout << "]\n";
    }
}

// Единичная матрица
Mat4 mat4_identity() {
    Mat4 m;
    m.m[0][0] = m.m[1][1] = m.m[2][2] = m.m[3][3] = 1.0;
    return m;
}

Mat4 mat4_mul(const Mat4 &a, const Mat4 &b) {
    Mat4 c;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                c.m[i][j] += a.m[i][k] * b.m[k][j];
    return c;
}

Mat4 rotation_y(double angle) {
    Mat4 m = mat4_identity();
    m.m[0][0] =  std::cos(angle);
    m.m[0][2] =  std::sin(angle);
    m.m[2][0] = -std::sin(angle);
    m.m[2][2] =  std::cos(angle);
    return m;
}

Mat4 rotation_x(double angle) {
    Mat4 m = mat4_identity();
    m.m[1][1] =  std::cos(angle);
    m.m[1][2] = -std::sin(angle);
    m.m[2][1] =  std::sin(angle);
    m.m[2][2] =  std::cos(angle);
    return m;
}

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

// Вершины единичного куба [-1, 1]^3
constexpr std::array<Vec4, 8> CUBE_VERTICES = {{
    {-1, -1, -1, 1}, { 1, -1, -1, 1}, { 1,  1, -1, 1}, {-1,  1, -1, 1},
    {-1, -1,  1, 1}, { 1, -1,  1, 1}, { 1,  1,  1, 1}, {-1,  1,  1, 1},
}};

// Рёбра куба: пары индексов вершин
constexpr std::array<std::pair<int,int>, 12> CUBE_EDGES = {{
    {0,1},{1,2},{2,3},{3,0},
    {4,5},{5,6},{6,7},{7,4},
    {0,4},{1,5},{2,6},{3,7},
}};

// Проецируем 3D-точку и конвертируем в экранные координаты
// Возвращает false если точка за камерой (w <= 0)
bool project_point(const Mat4 &proj, Vec4 v, int &sx, int &sy) {
    Vec4 clip = mat4_mul_vec4(proj, v);
    if (clip.w <= 0)
        return false;
    double ndcX = clip.x / clip.w;
    double ndcY = clip.y / clip.w;
    sx = static_cast<int>((ndcX + 1.0) / 2.0 * SCREEN_WIDTH);
    sy = static_cast<int>((1.0 - (ndcY + 1.0) / 2.0) * SCREEN_HEIGHT);
    return true;
}

void render_cube_sdl(double fov_deg, double near_z, double far_z) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Ошибка инициализации SDL: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN,
                                    &window, &renderer) < 0) {
        std::cout << "Ошибка создания окна: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    double aspect = static_cast<double>(SCREEN_WIDTH) / SCREEN_HEIGHT;
    Mat4 proj = perspective_matrix(fov_deg, aspect, near_z, far_z);

    double angleY = 0.0, angleX = 0.2;
    const double CAMERA_Z = 5.0; // куб в начале координат, камера отодвинута по Z

    SDL_Event e;
    Uint32 last = SDL_GetTicks();
    while (true) {
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT ||
                (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
                break;
        }

        Uint32 now = SDL_GetTicks();
        double dt = (now - last) / 1000.0;
        last = now;
        angleY += 1.0 * dt;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // матрица модели-вида: поворот + перенос (куб перед камерой)
        Mat4 rotY = rotation_y(angleY);
        Mat4 rotX = rotation_x(angleX);
        Mat4 rot   = mat4_mul(rotX, rotY);

        // перенос куба вдоль -Z (в сторону камеры)
        Mat4 trans = mat4_identity();
        trans.m[2][3] = -CAMERA_Z;

        Mat4 mv = mat4_mul(trans, rot);
        Mat4 mvp = mat4_mul(proj, mv);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        for (auto &edge : CUBE_EDGES) {
            Vec4 v0 = CUBE_VERTICES[edge.first];
            Vec4 v1 = CUBE_VERTICES[edge.second];
            int x0, y0, x1, y1;
            if (project_point(mvp, v0, x0, y0) && project_point(mvp, v1, x1, y1))
                SDL_RenderDrawLine(renderer, x0, y0, x1, y1);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 60);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

} // namespace

int perspective_entry() {
    constexpr std::string_view title = "Перспективная проекция";
    constexpr std::array<const char*, 3> entries{
        "Вычислить матрицу перспективной проекции",
        "Проецировать 3D-точку на экран",
        "Визуализация вращающегося куба (SDL)",
    };

    while (true) {
        int choice = menu_ask(title.data(), entries.data(), entries.size());
        switch (choice) {
        case 0:
            return 0;

        case 1: {
            double fov, aspect, near_z, far_z;
            while (true) {
                std::cout << "Угол обзора FOV (градусы, > 0): ";
                if (std::cin >> fov && fov > 0 && fov < 180) {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                std::cout << "Ошибка: FOV должен быть в диапазоне (0, 180).\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            if (!read_positive("Соотношение сторон экрана (ширина/высота, > 0): ", aspect)) break;
            if (!read_positive("Ближняя плоскость отсечения (near, > 0): ", near_z)) break;
            while (true) {
                std::cout << "Дальняя плоскость отсечения (far, > near): ";
                if (std::cin >> far_z && far_z > near_z) {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                std::cout << "Ошибка: far должен быть больше near (" << near_z << ").\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            Mat4 mat = perspective_matrix(fov, aspect, near_z, far_z);
            std::cout << "\nМатрица перспективной проекции:\n";
            print_matrix(mat);
            break;
        }

        case 2: {
            double fov, aspect, near_z, far_z;
            double px, py, pz;
            while (true) {
                std::cout << "Угол обзора FOV (градусы, > 0): ";
                if (std::cin >> fov && fov > 0 && fov < 180) {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                std::cout << "Ошибка: FOV должен быть в диапазоне (0, 180).\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            if (!read_positive("Соотношение сторон экрана (ширина/высота, > 0): ", aspect)) break;
            if (!read_positive("Ближняя плоскость отсечения (near, > 0): ", near_z)) break;
            while (true) {
                std::cout << "Дальняя плоскость отсечения (far, > near): ";
                if (std::cin >> far_z && far_z > near_z) {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                std::cout << "Ошибка: far должен быть больше near (" << near_z << ").\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cout << "Координата X точки: "; std::cin >> px;
            std::cout << "Координата Y точки: "; std::cin >> py;
            std::cout << "Координата Z точки (отрицательная — перед камерой): "; std::cin >> pz;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            Mat4 proj = perspective_matrix(fov, aspect, near_z, far_z);
            Vec4 clip = mat4_mul_vec4(proj, {px, py, pz, 1.0});
            if (clip.w <= 0) {
                std::cout << "Точка находится за камерой или в плоскости камеры.\n";
            } else {
                double ndcX = clip.x / clip.w;
                double ndcY = clip.y / clip.w;
                double ndcZ = clip.z / clip.w;
                std::cout << std::fixed << std::setprecision(6);
                std::cout << "\nКлип-координаты: (" << clip.x << ", " << clip.y
                          << ", " << clip.z << ", " << clip.w << ")\n";
                std::cout << "NDC-координаты:  (" << ndcX << ", " << ndcY
                          << ", " << ndcZ << ")\n";
                bool visible = ndcX >= -1 && ndcX <= 1 && ndcY >= -1 && ndcY <= 1
                               && ndcZ >= -1 && ndcZ <= 1;
                std::cout << "Точка " << (visible ? "видима" : "вне усечённого объёма") << ".\n";
            }
            break;
        }

        case 3: {
            double fov, near_z, far_z;
            while (true) {
                std::cout << "Угол обзора FOV (градусы, > 0): ";
                if (std::cin >> fov && fov > 0 && fov < 180) {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                std::cout << "Ошибка: FOV должен быть в диапазоне (0, 180).\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            if (!read_positive("Ближняя плоскость отсечения (near, > 0): ", near_z)) break;
            while (true) {
                std::cout << "Дальняя плоскость отсечения (far, > near): ";
                if (std::cin >> far_z && far_z > near_z) {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                std::cout << "Ошибка: far должен быть больше near (" << near_z << ").\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cout << "Открытие окна SDL... Нажмите ESC или закройте окно для выхода.\n";
            render_cube_sdl(fov, near_z, far_z);
            break;
        }

        default:
            break;
        }
        std::cout << std::endl;
    }
    return 0;
}
