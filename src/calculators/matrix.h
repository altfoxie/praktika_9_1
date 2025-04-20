#pragma once
#include <iostream>

using namespace std;

void create_array(double **matrix, int rows, int columns);

void matrix_input(double **matrix, int rows, int columns);

void matrix_output(double **matrix, int rows, int columns);

void matrix_delete(double **matrix, int rows, int columns);

void matrix_sum();

void matrix_subtraction();

void matrix_multiplication();

void matrix_multiplication_by_number();

void matrix_plus_number();

void matrix_minus_number();

double **transpose(double **matrix, int rows, int columns);

void matrix_transpose();

double **get_minor(double** mat, int n, int row, int col);

double determinant(double** mat, int n);

void matrix_determinant();

void inverse_matrix();

int matrix_entry();