#include "s21_matrix_oop.h"

S21Matrix::S21Matrix(/* args */)  // конструктор
{
  rows_ = 1;
  cols_ = 1;
  matrix_ = new double*();  // начальное выделение памяти
  matrix_[0] = new double();  // начальное выделение памяти
}

S21Matrix::~S21Matrix()  // деструктор
{
  if (this->matrix_ != nullptr) {
    // std::cout << "clean_memory" << std::endl;
    for (int i = 0; i < this->rows_; ++i) {  // очищение памяти
      if (this->matrix_[i] != nullptr) {
        delete[] this->matrix_[i];
      }
    }
    delete[] this->matrix_;  // очищение массива
  }
}

S21Matrix::S21Matrix(int rows, int cols) {
  check_matrix(rows, cols);
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double*[rows_];  // выделение памяти по строкам
  for (int i = 0; i < rows_; ++i) {  // выделение памяти по колонкам
    matrix_[i] = new double[cols_]();  // изначальное запаолнение 0
  }
}

S21Matrix::S21Matrix(const S21Matrix& other) {  // копирвоание
  if (this != &other) {  // проверка на ссылание самого себя
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    this->matrix_ = new double*[this->rows_];  // выделение памяти по строкам
    for (int i = 0; i < this->rows_; ++i) {  // выделение памяти по колонкам
      this->matrix_[i] = new double[this->cols_];
      for (int j = 0; j < this->cols_; ++j) {
        this->matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  if (this != &other) {  // проверка на ссылание самого себя
    this->rows_ = other.rows_;  // копируем и удаляем
    this->cols_ = other.cols_;
    this->matrix_ = other.matrix_;  // выделение памяти по строкам
    other.cols_ = other.rows_ = 0;
    other.matrix_ = nullptr;
  }
}

int S21Matrix::get_rows() { return rows_; }

int S21Matrix::get_cols() { return cols_; }

void S21Matrix::set_rows(int rows) {
  if (rows == this->rows_) {
    return;  // если заданное значение уже присутвует ,то смысла нет
  } else if (rows < 1) {
    throw std::invalid_argument("rows can\'not be negative or equalent zero");
  }
  S21Matrix copy_matrix(*this);           // создаём копию
  for (int i{0}; i < this->rows_; ++i) {  // отчистка массива
    delete[] this->matrix_[i];
  }
  delete[] this->matrix_;
  this->rows_ = rows;                        // перезапись строк
  this->matrix_ = new double*[this->rows_];  // создание обнолённого массива
  for (int i{0}; i < this->rows_; ++i) {
    this->matrix_[i] = new double[this->cols_]();
  }
  for (int i{0}; i < this->rows_; ++i) {
    for (int j{0}; j < this->cols_; ++j) {
      if (i < copy_matrix.rows_) {
        this->matrix_[i][j] = copy_matrix.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::set_cols(int cols) {
  if (cols == this->rows_) {
    return;  // если заданное значение уже присутвует ,то смысла нет
  } else if (cols < 1) {
    throw std::invalid_argument("cols can\'not be negative or equalent zero");
  }
  S21Matrix copy_matrix(*this);  // создаём идиентичную матрицу
  for (int i{0}; i < this->rows_; ++i) {
    delete[] this->matrix_[i];
    matrix_[i] = new double[cols]();  // пересоздаём столбец
  }
  this->cols_ = cols;  // изменяем значение столбца в обьекте
  for (int i{0}; i < this->rows_; ++i) {  // перезаписываем значения
    for (int j{0}; j < this->cols_; ++j) {
      if (j < copy_matrix.cols_) {
        this->matrix_[i][j] = copy_matrix.matrix_[i][j];
      }
    }
  }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if (this->rows_ == other.rows_ && this->cols_ == other.cols_) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        if (fabs(this->matrix_[i][j] - other.matrix_[i][j]) >
            1e-7) {  // если не равны то прервать
          return false;
        }
      }
    }
  } else {
    return false;
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::logic_error("diferent size");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (this->matrix_[i][j] != this->matrix_[i][j] ||
          other.matrix_[i][j] != other.matrix_[i][j]) {
        throw std::invalid_argument("NOT NAN");
      }
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::logic_error("diferent size");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (this->matrix_[i][j] != this->matrix_[i][j] ||
          other.matrix_[i][j] != other.matrix_[i][j]) {
        throw std::invalid_argument("NOT NAN");
      }
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  if (num != num) {
    throw std::invalid_argument("NAN? seriously?");
  }
  for (int i{0}; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (this->matrix_[i][j] != this->matrix_[i][j]) {
        throw std::invalid_argument("NOT NAN");
      }
      this->matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (this->cols_ != other.rows_) {
    throw std::invalid_argument("they columns are not equal to other rows!");
  }
  // создание результирующей матрицы
  S21Matrix result(this->rows_, other.cols_);
  for (int i{0}; i < result.rows_; ++i) {  // перемножение
    for (int j{0}; j < result.cols_; ++j) {
      for (int k{0}; k < this->cols_; k++) {
        result.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = result;  // приравнивание
}

S21Matrix S21Matrix::CalcComplements() {
  if (this->cols_ != this->rows_) {
    throw std::invalid_argument("cols are not equal rows");
  } else if (this->rows_ == 1) {
    throw std::logic_error("cols and rows == 1");
  }
  // создаём матрицу для работы
  S21Matrix other(this->rows_, this->cols_);
  // матрица для вычислений
  S21Matrix copy_other(other.rows_ - 1, other.cols_ - 1);
  double determ{0};  // переменная для вычисления детерминанта
  int sign{0};  // переменная для определения знака
  for (int i{0}; i < this->rows_; ++i) {  // проходимся по каждой строке
    for (int j{0}; j < this->cols_; ++j) {
      sign = pow(-1, i + j + 2);
      // обрезать матрицу
      copy_other = this->matrix_down(i, j);
      // вычислить детеминант
      determ = copy_other.Determinant();
      // std::cout << determ << std::endl;
      //  записать в рабочую матрицу
      other.matrix_[i][j] = sign * determ;
    }
  }
  return other;
}

S21Matrix S21Matrix::Transpose() {
  // создаём транспонировованую матрицу
  S21Matrix new_matrix(this->cols_, this->rows_);
  for (int i{0}; i < new_matrix.rows_; ++i) {
    for (int j{0}; j < new_matrix.cols_; ++j) {
      // обмен данными
      new_matrix.matrix_[i][j] = this->matrix_[j][i];
    }
  }
  return new_matrix;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (this->Determinant() == 0) {
    throw std::invalid_argument("determinant = 0");
  }
  S21Matrix result(this->rows_, this->cols_);
  // если матрица состоит из одного элемента
  if (this->rows_ == 1) {
    result.matrix_[0][0] = 1. / this->matrix_[0][0];
    return result;
  }
  double determ = this->Determinant();  // определитель
  result = this->CalcComplements().Transpose();
  result.MulNumber(1. / determ);
  return result;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {  // проверка на ссылание самого себя
    if (this->matrix_ != nullptr) {
      for (int i = 0; i < this->rows_; ++i) {  // очищение памяти
        if (this->matrix_[i] != nullptr) {
          delete[] this->matrix_[i];
        }
      }
      delete[] this->matrix_;  // очищение массива
    }
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    // выделение памяти по строкам
    this->matrix_ = new double*[this->rows_];
    for (int i = 0; i < this->rows_; ++i) {  // выделение памяти по колонкам
      this->matrix_[i] = new double[this->cols_];
      for (int j = 0; j < this->cols_; ++j) {
        this->matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) {
  return this->EqMatrix(other);
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

S21Matrix operator*(const double num, const S21Matrix& other) {
  S21Matrix result(other);
  result.MulNumber(num);
  return result;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

double& S21Matrix::operator()(const int i, const int j) {
  if (i >= this->rows_ || j >= this->cols_ || i < 0 || j < 0) {
    throw std::out_of_range("out of range");
  }
  return this->matrix_[i][j];
}

S21Matrix S21Matrix::matrix_down(int x, int y) {
  S21Matrix other(this->rows_ - 1, this->cols_ - 1);
  for (int i{0}, i_r{0}; i_r < this->rows_ - 1; ++i, i_r++) {
    if (i == x) {
      ++i;
    }
    for (int j{0}, j_r{0}; j_r < this->cols_ - 1; j_r++, ++j) {
      if (j == y) {
        ++j;
      }
      other.matrix_[i_r][j_r] = this->matrix_[i][j];
    }
  }
  return other;
}

void S21Matrix::check_matrix(int rows, int cols) {
  if (rows < 1 || cols < 1) {
    throw std::runtime_error("bad_matrix");
  }
}

double S21Matrix::Determinant() {
  if (this->cols_ != this->rows_) {
    throw std::invalid_argument("cols are not equal rows");
  } else if (this->cols_ == 0 || this->rows_ == 0) {
    throw std::invalid_argument("cols = 0 or rows = 0");
  }
  if (this->rows_ == 1)
    return this->matrix_[0][0];
  else if (this->rows_ == 2)
    return this->matrix_[0][0] * this->matrix_[1][1] -
           this->matrix_[0][1] * this->matrix_[1][0];
  else {
    int d = 0;
    for (int k = 0; k < this->rows_; k++) {
      S21Matrix other(this->rows_ - 1, this->cols_ - 1);
      for (int i = 1; i < this->rows_; ++i) {
        for (int j = 0; j < this->rows_; ++j) {
          if (j == k)
            continue;
          else if (j < k)
            other.matrix_[i - 1][j] = this->matrix_[i][j];
          else
            other.matrix_[i - 1][j - 1] = this->matrix_[i][j];
        }
      }
      d += pow(-1, k + 2) * this->matrix_[0][k] * other.Determinant();
    }
    return d;
  }
}
