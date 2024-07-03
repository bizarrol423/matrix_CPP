#ifndef __S21_MATRIX_OOP_H__
#define __S21_MATRIX_OOP_H__

#include <cmath>
#include <iostream>

class S21Matrix  // тело класса
{
 public:  // публичные функции для вызова из любой части
          // конструкторы и деструктор
  S21Matrix();
  S21Matrix(int rows, int cols);      //  определённый размер
  S21Matrix(const S21Matrix& other);  // копирование
  S21Matrix(S21Matrix&& other);       // перенос
  ~S21Matrix();

  // accessor
  int get_rows();
  int get_cols();

  // mutator
  void set_rows(int rows);
  void set_cols(int cols);

  // math matrix
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);

  // func matrix
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix Transpose();
  S21Matrix InverseMatrix();

  // operators
  S21Matrix& operator=(const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double num);
  friend S21Matrix operator*(const double num, const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  double& operator()(const int i, const int j);

  void s21_print_matrix();

 private:  // приватные переменные для использования внутри класса
  double** matrix_;
  int rows_;
  int cols_;

  // additional
  S21Matrix matrix_down(int x, int y);
  void check_matrix(int rows, int cols);
};

#endif
