#ifndef MATH_HPP
#define MATH_HPP
#include <math.h>
#include <float.h>
#include <string>
#include <iomanip>
#include "defination.hpp"

namespace mess
{
// single operation iteration over a matrix
#define matrix_iter                      \
    for (int i = 0; i < matrix_row; i++) \
        for (int j = 0; j < matrix_col; j++)

    // int or double only, not some random imaginary numbers matrices
    class matrix
    {
    public:
        // size of matrix
        int matrix_row, matrix_col;
        // matrix body
        double **__matrix = nullptr;
        matrix(int matrix_row = 1, int matrix_col = 1, double init = 0)
        {
            this->matrix_row = matrix_row;
            this->matrix_col = matrix_col;

            // create matrix
            this->__matrix = new double *[matrix_row];
            for (int i = 0; i < matrix_row; i++)
                __matrix[i] = new double[matrix_col];

            // init, fill the matrix
            matrix_iter
                __matrix[i][j] = init;
        }

        double sum()
        {
            double res = 0;
            matrix_iter
                res += __matrix[i][j];
            return res;
        }

        // get an indexed value, replacement of [][]
        double operator()(int x, int y) { return __matrix[x][y]; }
        void operator()(int x, int y, double value) { __matrix[x][y] = value; }

        // overload add matrix to matrix
        matrix operator+(matrix m2)
        {
            if (matrix_row != m2.matrix_row || matrix_col != m2.matrix_col)
                throw logic_error("addition can only be performed between matrices of same size");

            matrix_iter
                __matrix[i][j] += m2.__matrix[i][j];
            return *this;
        }

        matrix operator+(double value)
        {
            matrix_iter
                __matrix[i][j] += value;
            return *this;
        }

        template <typename T>
        // minus = plus negative, value can either be a matrix or double
        matrix operator-(T v)
        {
            // throwing the matrix size exception to addition part
            *this + v * (-1);
            return *this;
        }

        matrix operator*(matrix m2)
        {
            if (matrix_col != m2.matrix_row)
                throw logic_error("multiplication can only be performed between matrices with size of of x*y and y*z");

            // C[i][j] = sum(A[i][k]*B[k][j] for k in range(0, A_matrix_col))

            matrix *res = new matrix(matrix_row, m2.matrix_col, 0);
            for (int i = 0; i < matrix_row; i++)
            {
                for (int j = 0; j < m2.matrix_col; j++)
                {
                    int sum = 0;
                    for (int k = 0; k < matrix_col; k++)
                    {
                        sum += ((*this)(i, k) * m2(k, j));
                    }
                    res->__matrix[i][j] = sum;
                }
            }
            return *res;
        }

        matrix operator*(double value)
        {
            matrix_iter
                __matrix[i][j] *= value;
            return *this;
        }

        // overload the cout behaviour
        friend ostream &operator<<(ostream &out, matrix *matrix)
        {
            return out << *matrix;
        }

        friend ostream &operator<<(ostream &out, matrix matrix)
        {
            for (int i = 0; i < matrix.matrix_row; i++)
            {
                for (int j = 0; j < matrix.matrix_col; j++)
                {
                    out << std::setfill(' ') << std::setw(5) << matrix(i, j);
                    if (j != matrix.matrix_col - 1)
                        out << " ";
                }
                out << "\n";
            }
            return out;
        }
    };
}

#endif
