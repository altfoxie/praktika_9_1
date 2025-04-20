#include "matrix.h"
#include "../common/menu.h"

double **create_matrix(double **matrix, int rows, int columns)
{
	matrix = new double*[rows];
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new double[columns];
	}

	return matrix;
}

void matrix_input(double **matrix, int rows, int columns)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cout << "[" << i << "][" << j << "]: "; cin >> matrix[i][j];
		}
	}
}

void matrix_output(double **matrix, int rows, int columns)
{
	for (int i = 0; i < rows; i++)
	{
		cout << "[ ";
		for (int j = 0; j < columns; j++)
		{
			cout << matrix[i][j] << " "; 
		}
		cout << "]\n";
	}
}

void matrix_delete(double **matrix, int rows, int columns)
{
	for (int i = 0; i < rows; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

void matrix_sum()
{
	int rows1, columns1, rows2, columns2;
	double **matrix1 = 0, **matrix2 = 0, **answer_matrix = 0;
	cout << "Введите размеры первой матрицы: "; cin >> rows1 >> columns1;
	cout << "Введите размеры второй матрицы: "; cin >> rows2 >> columns2;

	if (rows1 == rows2 and columns1 == columns2)
	{
		matrix1 = create_matrix(matrix1, rows1, columns1);
		matrix2 = create_matrix(matrix2, rows2, columns2);
		answer_matrix = create_matrix(answer_matrix, rows1, columns1);

		matrix_input(matrix1, rows1, columns1);
		matrix_input(matrix2, rows2, columns2);

		for (int i = 0; i < rows1; i++)
		{
			for (int j = 0; j < columns1; j++)
			{
				answer_matrix[i][j] = matrix1[i][j] + matrix2[i][j];
			}
		}

		cout << "\nОтвет:\n";
		matrix_output(answer_matrix, rows1, columns1);
		matrix_delete(matrix1, rows1, columns1);
		matrix_delete(matrix2, rows2, columns2);
		matrix_delete(answer_matrix, rows1, columns1);
	}
	else
	{
		cout << "Матрицы разного размера. Сложение невозможно.\n";
	}
}

void matrix_subtraction()
{
	int rows1, columns1, rows2, columns2;
	double **matrix1 = 0, **matrix2 = 0, **answer_matrix = 0;
	cout << "Введите размеры первой матрицы: "; cin >> rows1 >> columns1;
	cout << "Введите размеры второй матрицы: "; cin >> rows2 >> columns2;

	if (rows1 == rows2 and columns1 == columns2)
	{
		matrix1 = create_matrix(matrix1, rows1, columns1);
		matrix2 = create_matrix(matrix2, rows2, columns2);
		answer_matrix = create_matrix(answer_matrix, rows1, columns1);

		matrix_input(matrix1, rows1, columns1);
		matrix_input(matrix2, rows2, columns2);

		for (int i = 0; i < rows1; i++)
		{
			for (int j = 0; j < columns1; j++)
			{
				answer_matrix[i][j] = matrix1[i][j] - matrix2[i][j];
			}
		}

		cout << "\nОтвет:\n";
		matrix_output(answer_matrix, rows1, columns1);
		matrix_delete(matrix1, rows1, columns1);
		matrix_delete(matrix2, rows2, columns2);
		matrix_delete(answer_matrix, rows1, columns1);
	}
	else
	{
		cout << "Матрицы разного размера. Вычитание невозможно.\n";
	}
}

void matrix_multiplication()
{
	int rows1, columns1, rows2, columns2;
	double **matrix1 = 0, **matrix2 = 0, **answer_matrix = 0;
	cout << "Введите размеры первой матрицы: "; cin >> rows1 >> columns1;
	cout << "Введите размеры второй матрицы: "; cin >> rows2 >> columns2;

	if (rows1 == columns2 and rows2 == columns1)
	{
		matrix1 = create_matrix(matrix1, rows1, columns1);
		matrix2 = create_matrix(matrix2, rows2, columns2);
		answer_matrix = create_matrix(answer_matrix, rows1, columns1);

		matrix_input(matrix1, rows1, columns1);
		matrix_input(matrix2, rows2, columns2);

		for (int i = 0; i < rows1; i++)
		{
			for (int j = 0; j < columns1; j++)
			{
				answer_matrix[i][j] = matrix1[i][j] * matrix2[j][i];
			}
		}

		cout << "\nОтвет:\n";
		matrix_output(answer_matrix, rows1, columns1);
		matrix_delete(matrix1, rows1, columns1);
		matrix_delete(matrix2, rows2, columns2);
		matrix_delete(answer_matrix, rows1, columns2);
	}
	else
	{
		cout << "Матрицы разного размера. Сложение невозможно.\n";
	}
}

void matrix_multiplication_by_number()
{
	int rows, columns, number;
	double **matrix = 0;
	cout << "Введите размеры матрицы: "; cin >> rows >> columns;
	cout << "Введите число: "; cin >> number;

	matrix = create_matrix(matrix, rows, columns);

	matrix_input(matrix, rows, columns);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			matrix[i][j] = matrix[i][j] * number;
		}
	}

	cout << "\nОтвет:\n";
	matrix_output(matrix, rows, columns);
	matrix_delete(matrix, rows, columns);
}

void matrix_plus_number()
{
	int rows, columns, number;
	double **matrix = 0;
	cout << "Введите размеры матрицы: "; cin >> rows >> columns;
	cout << "Введите число: "; cin >> number;

	matrix = create_matrix(matrix, rows, columns);

	matrix_input(matrix, rows, columns);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			matrix[i][j] = matrix[i][j] + number;
		}
	}

	cout << "\nОтвет:\n";
	matrix_output(matrix, rows, columns);
	matrix_delete(matrix, rows, columns);
}

void matrix_minus_number()
{
	int rows, columns, number;
	double **matrix = 0;
	cout << "Введите размеры матрицы: "; cin >> rows >> columns;
	cout << "Введите число: "; cin >> number;

	matrix = create_matrix(matrix, rows, columns);

	matrix_input(matrix, rows, columns);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			matrix[i][j] = matrix[i][j] - number;
		}
	}

	cout << "\nОтвет:\n";
	matrix_output(matrix, rows, columns);
	matrix_delete(matrix, rows, columns);
}

double **transpose(double **matrix, int rows, int columns)
{
	double **answer_matrix = 0;
	answer_matrix = create_matrix(answer_matrix, rows, columns);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            answer_matrix[j][i] = matrix[i][j];
        }
    }

    return answer_matrix;
}

void matrix_transpose()
{
	int rows, columns;
	double **matrix = 0, **answer_matrix = 0;
    cout << "Введите размеры матрицы: "; cin >> rows >> columns;

	matrix = create_matrix(matrix, rows, columns);
	answer_matrix = create_matrix(matrix, rows, columns);

    matrix_input(matrix, rows, columns);
    answer_matrix = transpose(matrix, rows, columns);

    cout << "\nОтвет:\n";
    matrix_output(answer_matrix, columns, rows);
    matrix_delete(matrix, rows, columns);
    matrix_delete(answer_matrix, columns, rows);
}

double **get_minor(double **matrix, int n, int row, int col)
{
	double **minor = 0;
	minor = create_matrix(minor, n-1, n-1);

    int r = 0, c = 0;
    for (int i = 0; i < n; i++) 
    {
        if (i == row)
        {
            continue;
        }
        c = 0;
        for (int j = 0; j < n; j++) 
        {
            if (j == col) 
			{
				continue;
			}
            minor[r][c] = matrix[i][j];
            c += 1;
        }
        r += 1;
    }
    return minor;
}

double determinant(double **matrix, int n) 
{
    if (n == 1)
    {
        return matrix[0][0];
    }
    if (n == 2)
    {
        return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
    }

    double det = 0;
    int sign = 1;
    for (int i = 0; i < n; i++)
    {
		double** minor = get_minor(matrix, n, 0, i);
		det += sign * matrix[0][i] * determinant(minor, n-1);
		sign = -sign;
		matrix_delete(minor, n-1, n-1);
    }
    return det;
}

void matrix_determinant()
{
    int rows, columns;
	double answer;
	double **matrix = 0;
    cout << "Введите размеры матрицы: "; cin >> rows >> columns;

	matrix = create_matrix(matrix, rows, columns);
    matrix_input(matrix, rows, columns);

    if (rows == columns)
    {
        answer = determinant(matrix, rows);
        cout << "\nОтвет:\n" << answer << "\n";
    }
	
	matrix_delete(matrix, rows, columns);
}

void inverse_matrix()
{
    int rows, columns;
	double **matrix = 0, **answer = 0;
	cout << "Введите размеры матрицы: "; cin >> rows >> columns;

	matrix = create_matrix(matrix, rows, columns);
	answer = create_matrix(answer, rows, columns);
    matrix_input(matrix, rows, columns);

    double det = determinant(matrix, rows);
    if (det != 0)
    {
		double **addition;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				addition = get_minor(matrix, rows, i, j);
				answer[i][j] = pow(-1, i+j) * determinant(addition, rows-1);
			}
		}

		answer = transpose(answer, rows, columns);

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				answer[i][j] = 1/det * answer[i][j];
			}
		}
		
		cout << "\nОтвет:\n";
		matrix_output(answer, rows, columns);
    }
	else
	{
		cout << "Определитель равен 0. Нахождение обратной матрицы невозможно.\n";
	}

	matrix_delete(answer, rows, columns);
	matrix_delete(matrix, rows, columns);
}

int matrix_entry() 
{
	const char *title = "Матрицы";
	const char *entries[] = {"Сложение матриц", "Вычитание", "Умножение матриц", 
		"Умножение матрицы на число", "Сложение матрицы с числом", "Вычитание числа из матрицы",
		"Транспонирование матрицы", "Обратная матрица", "Определитель"};

	while (true)
	{
		int choice = menu_ask(title, entries, sizeof(entries) / sizeof(entries[0]));
		switch (choice)
		{
		case 0:
			return 0;
		case 1:
			matrix_sum();
			break;
		case 2:
			matrix_subtraction();
			break;
		case 3:
			matrix_multiplication();
			break;
		case 4:
			matrix_multiplication_by_number();
			break;
		case 5:
			matrix_plus_number();
			break;
		case 6:
			matrix_minus_number();
			break;
		case 7:
			matrix_transpose();
			break;
		case 8:
			inverse_matrix();
			break;
		case 9:
			matrix_determinant();
			break;
		default:
			break;
		}
		cout << endl;
	}
	return 0;
}