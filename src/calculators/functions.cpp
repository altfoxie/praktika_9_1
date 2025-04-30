#include "functions.h"

#define INTEGRAL_STEP 0.001
#define ROOT_EPSILON 1e-6
#define EXTREMA_STEP 0.01

class IFunction {
public:
  virtual ~IFunction() = default;
  virtual double eval(double x) = 0;
  virtual std::string to_string() = 0;

  virtual double integrate(double a, double b) {
    // метод трапеций
    double sum = 0;
    for (double x = a; x < b; x += INTEGRAL_STEP) {
      double x1 = x + INTEGRAL_STEP;
      sum += 0.5 * (eval(x) + eval(x1)) * INTEGRAL_STEP;
    }
    return sum;
  }

  virtual double find_root(double a, double b) {
    // метод бисекции
    double fa = eval(a);
    double fb = eval(b);

    // проверка, есть ли корень на отрезке
    if (fa * fb > 0) {
      // нет корня или четное количество корней
      return std::numeric_limits<double>::max();
    }

    double c, fc;
    while (std::abs(b - a) > ROOT_EPSILON) {
      c = (a + b) / 2;
      fc = eval(c);

      if (std::abs(fc) < ROOT_EPSILON) {
        return c; // нашли корень
      }

      if (fa * fc < 0) {
        b = c;
        fb = fc;
      } else {
        a = c;
        fa = fc;
      }
    }

    return (a + b) / 2; // приближенное значение корня
  }

  virtual std::vector<double> find_extrema(double a, double b) {
    std::vector<double> extrema;

    // аппроксимация производной и поиск точек, где она меняет знак
    double prevSlope = 0;
    double x = a + EXTREMA_STEP;

    while (x < b) {
      double currSlope = (eval(x + EXTREMA_STEP) - eval(x - EXTREMA_STEP)) /
                         (2 * EXTREMA_STEP);

      // если производная меняет знак, то здесь экстремум
      if (prevSlope * currSlope < 0 || std::abs(currSlope) < ROOT_EPSILON) {
        // уточняем положение экстремума методом бисекции для производной
        double left = x - EXTREMA_STEP;
        double right = x + EXTREMA_STEP;
        double mid;

        for (int i = 0; i < 10; i++) { // несколько итераций для уточнения
          mid = (left + right) / 2;
          double midSlope =
              (eval(mid + EXTREMA_STEP / 10) - eval(mid - EXTREMA_STEP / 10)) /
              (2 * EXTREMA_STEP / 10);

          if (std::abs(midSlope) < ROOT_EPSILON) {
            break;
          }

          if (prevSlope * midSlope < 0) {
            right = mid;
          } else {
            left = mid;
          }
        }

        extrema.push_back(mid);
      }

      prevSlope = currSlope;
      x += EXTREMA_STEP;
    }

    return extrema;
  }
};

class Polynomial : public IFunction {
public:
  Polynomial(const std::vector<double> coefficients)
      : coefficients(coefficients) {}

  double eval(double x) override {
    double result = 0;
    for (size_t i = 0; i < coefficients.size(); ++i) {
      result += coefficients[i] * std::pow(x, i);
    }
    return result;
  }

  std::string to_string() override {
    std::ostringstream ss;
    for (size_t i = 0; i < coefficients.size(); ++i) {
      if (i > 0) {
        ss << (coefficients[i] >= 0 ? "+" : "");
      }
      ss << coefficients[i];
      if (i > 0) {
        ss << "*x";
        if (i > 1) {
          ss << "^" << i;
        }
      }
    }
    return ss.str();
  }

private:
  std::vector<double> coefficients;
};

class PowerFunction : public IFunction {
public:
  PowerFunction(double a, double b, double c) : a(a), b(b), c(c) {}

  double eval(double x) override { return a * std::pow(x, b) + c; }

  std::string to_string() override {
    std::ostringstream ss;
    ss << a << "*x^" << b << (c >= 0 ? "+" : "") << c;
    return ss.str();
  }

private:
  double a, b, c;
};

class ExponentialFunction : public IFunction {
public:
  ExponentialFunction(double a, double b, double c, double d)
      : a(a), b(b), c(c), d(d) {}

  double eval(double x) override { return a * std::pow(b, c * x) + d; }

  std::string to_string() override {
    std::ostringstream ss;
    ss << a << "*" << b << "^(" << c << "*x)" << (d >= 0 ? "+" : "") << d;
    return ss.str();
  }

private:
  double a, b, c, d;
};

class LogarithmicFunction : public IFunction {
public:
  LogarithmicFunction(double a, double b, double c) : a(a), b(b), c(c) {}

  double eval(double x) override {
    if (x <= 0 || b <= 0)
      return std::numeric_limits<double>::max();
    return a * std::log(b * x) + c;
  }

  std::string to_string() override {
    std::ostringstream ss;
    ss << a << "*ln(" << b << "*x)" << (c >= 0 ? "+" : "") << c;
    return ss.str();
  }

private:
  double a, b, c;
};

class SinFunction : public IFunction {
public:
  SinFunction(double a, double b, double c, double d)
      : a(a), b(b), c(c), d(d) {}

  double eval(double x) override { return a * std::sin(b * x + c) + d; }

  std::string to_string() override {
    std::ostringstream ss;
    ss << a << "*sin(" << b << "*x" << (c >= 0 ? "+" : "") << c << ")"
       << (d >= 0 ? "+" : "") << d;
    return ss.str();
  }

private:
  double a, b, c, d;
};

class CosFunction : public IFunction {
public:
  CosFunction(double a, double b, double c, double d)
      : a(a), b(b), c(c), d(d) {}

  double eval(double x) override { return a * std::cos(b * x + c) + d; }

  std::string to_string() override {
    std::ostringstream ss;
    ss << a << "*cos(" << b << "*x" << (c >= 0 ? "+" : "") << c << ")"
       << (d >= 0 ? "+" : "") << d;
    return ss.str();
  }

private:
  double a, b, c, d;
};

void input_bounds(double *a, double *b) {
  std::cout << "Левая граница отрезка: ";
  std::cin >> *a;

  std::cout << "Правая граница отрезка: ";
  std::cin >> *b;

  if (*a > *b)
    std::swap(*a, *b);
}

IFunction *input_function() {
  const char *title = "Тип уравнения";
  const char *entries[] = {"Полином степени N: a0+a1*x+a2*x^2+...+aN*x^N",
                           "Степенная: a*x^b+c",
                           "Показательная: a*b^(c*x)+d",
                           "Логарифмическая: a*ln(b*x)+c",
                           "Синусоида: a*sin(b*x+c)+d",
                           "Косинусоида: a*cos(b*x+c)+d"};

  int choice = menu_ask(title, entries, sizeof(entries) / sizeof(entries[0]));
  if (choice == 0)
    return NULL;

  double a, b, c, d;
  int degree;
  std::vector<double> coefficients;

  switch (choice) {
  case 1: { // полином
    while (true) {
      std::cout << "Степень полинома: ";
      std::cin >> degree;
      if (degree >= 0)
        break;
      std::cout << "Значение должно быть неотрицательным" << std::endl;
    }

    coefficients.resize(degree + 1);
    for (int i = 0; i <= degree; ++i) {
      std::cout << "a" << i << ": ";
      std::cin >> coefficients[i];
    }

    return new Polynomial(coefficients);
  }
  case 2: { // степенная
    std::cout << "a: ";
    std::cin >> a;

    std::cout << "b: ";
    std::cin >> b;

    std::cout << "c: ";
    std::cin >> c;
    
    return new PowerFunction(a, b, c);
  }
  case 3: { // показательная
    std::cout << "a: ";
    std::cin >> a;

    std::cout << "b: ";
    std::cin >> b;

    std::cout << "c: ";
    std::cin >> c;

    std::cout << "d: ";
    std::cin >> d;

    return new ExponentialFunction(a, b, c, d);
  }
  case 4: { // логарифмическая
    std::cout << "a: ";
    std::cin >> a;

    std::cout << "b: ";
    std::cin >> b;

    std::cout << "c: ";
    std::cin >> c;

    return new LogarithmicFunction(a, b, c);
  }
  case 5: { // синусоида
    std::cout << "a: ";
    std::cin >> a;

    std::cout << "b: ";
    std::cin >> b;

    std::cout << "c: ";
    std::cin >> c;

    std::cout << "d: ";
    std::cin >> d;

    return new SinFunction(a, b, c, d);
  }
  case 6: { // косинусоида
    std::cout << "a: ";
    std::cin >> a;

    std::cout << "b: ";
    std::cin >> b;

    std::cout << "c: ";
    std::cin >> c;

    std::cout << "d: ";
    std::cin >> d;

    return new CosFunction(a, b, c, d);
  }
  default:
    return NULL;
  }
}

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define CENTER_X SCREEN_WIDTH / 2
#define CENTER_Y SCREEN_HEIGHT / 2

void render_function_sdl(IFunction *func, double a, double b) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Ошибка инициализации SDL: " << SDL_GetError() << std::endl;
    return;
  }

  SDL_Window *window;
  SDL_Renderer *renderer;
  if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN,
                                  &window, &renderer) < 0) {
    std::cout << "Ошибка создания окна и рендерера: " << SDL_GetError()
              << std::endl;
    return;
  }

  double min_y = func->eval(a), max_y = min_y;
  for (double x = a; x <= b; x += (b - a) / SCREEN_WIDTH) {
    double y = func->eval(x);
    if (y < min_y)
      min_y = y;
    if (y > max_y)
      max_y = y;
  }
  if (min_y == max_y) {
    min_y -= 1;
    max_y += 1;
  }

  SDL_Event e;
  while (true) {
    if (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT ||
          (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
        break;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // оси
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    int zero_y = CENTER_Y + int(min_y * (SCREEN_HEIGHT / (min_y - max_y)));
    int zero_x = int((0 - a) / (b - a) * SCREEN_WIDTH);
    SDL_RenderDrawLine(renderer, 0, zero_y, SCREEN_WIDTH, zero_y);
    SDL_RenderDrawLine(renderer, zero_x, 0, zero_x, SCREEN_HEIGHT);

    // график
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    int prev_x = 0, prev_y = 0;
    bool first = true;
    for (int px = 0; px < SCREEN_WIDTH; ++px) {
      double x = a + (b - a) * px / (SCREEN_WIDTH - 1);
      double y = func->eval(x);
      int py = CENTER_Y - int((y - (max_y + min_y) / 2) *
                              (SCREEN_HEIGHT / (max_y - min_y)));

      if (!first)
        SDL_RenderDrawLine(renderer, prev_x, prev_y, px, py);

      prev_x = px;
      prev_y = py;
      first = false;
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(1000 / 60);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
}

void functions_entry() {
  IFunction *current_function = NULL;
  std::string title = "Работа с функциями";

  const char *entries[] = {
      "Выбрать уравнение", "Вычисление определенного интеграла на отрезке",
      "Построение графика функции (SDL)", "Поиск корня Y=0 на отрезке",
      "Поиск экстремумов на отрезке"};

  while (true) {
    std::string menu_title = title;
    if (current_function != NULL) {
      menu_title += "\nВыбрано уравнение: " + current_function->to_string();
    }

    int choice = menu_ask(menu_title.c_str(), entries,
                          sizeof(entries) / sizeof(entries[0]));
    if (choice == 0)
      break;

    switch (choice) {
    case 1: { // выбор уравнения
      if (current_function != NULL)
        delete current_function;

      current_function = input_function();
      break;
    }
    case 2: { // вычисление интеграла
      if (current_function == NULL) {
        std::cout << "Сначала выберите уравнение" << std::endl;
        break;
      }

      double a, b;
      input_bounds(&a, &b);

      double result = current_function->integrate(a, b);
      std::cout << "Значение интеграла на отрезке [" << a << ", " << b
                << "]: " << result << std::endl;
      break;
    }
    case 3: { // построение графика
      if (current_function == NULL) {
        std::cout << "Сначала выберите уравнение" << std::endl;
        break;
      }

      double a, b;
      input_bounds(&a, &b);
      
      render_function_sdl(current_function, a, b);
      break;
    }
    case 4: { // поиск корня
      if (current_function == NULL) {
        std::cout << "Сначала выберите уравнение" << std::endl;
        break;
      }

      double a, b;
      input_bounds(&a, &b);

      double root = current_function->find_root(a, b);
      if (root == std::numeric_limits<double>::max()) {
        std::cout << "Корень не найден на отрезке [" << a << ", " << b << "]"
                  << std::endl;
      } else {
        std::cout << "Корень уравнения на отрезке [" << a << ", " << b
                  << "]: " << root << std::endl;
        std::cout << "Значение функции в точке x = " << root << ": "
                  << current_function->eval(root) << std::endl;
      }
      break;
    }
    case 5: { // поиск экстремумов
      if (current_function == NULL) {
        std::cout << "Сначала выберите уравнение" << std::endl;
        break;
      }

      double a, b;
      input_bounds(&a, &b);

      std::vector<double> extrema = current_function->find_extrema(a, b);
      if (!extrema.empty()) {
        std::cout << "Экстремумы функции на отрезке [" << a << ", " << b
                  << "]:" << std::endl;
        for (double point : extrema) {
          std::cout << "x = " << point
                    << ", f(x) = " << current_function->eval(point) << std::endl;
        }
      } else {
        std::cout << "Экстремумы не найдены на отрезке [" << a << ", " << b
                  << "]" << std::endl;
      }
      break;
    }
    }

    std::cout << std::endl;
  }

  if (current_function != NULL)
    delete current_function;
}