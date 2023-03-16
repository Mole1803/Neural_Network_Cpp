//
// Created by Moritz Hartmann on 13.03.23.
//

#include <iostream>
#include "Matrix.h"

Matrix::Matrix(int row, int column, double *matrix) {
    this->row = row;
    this->column = column;
    this->matrix = matrix;
}


void Matrix::mul(Matrix *matrix_1, Matrix *res_matrix) {
    if (this->column != matrix_1->row) {
        std::cout << "Matrix dimensions do not match" << std::endl;
        std::cout << "column: " << matrix_1->column << std::endl;
        std::cout << "row: " << matrix_1->row << std::endl;
        std::cout << "this->row: " << this->row << std::endl;
        std::cout << "this->column: " << this->column << std::endl;
        return;
    }

    int m_1_offset;
    int m_2_offset;
    double result;

    for (int i = 0; i < this->row * matrix_1->column; i++) {

        m_1_offset = (int) (i / matrix_1->column);
        m_2_offset = (i % matrix_1->column);

        result = 0.f;
        for (int j = 0; j < this->column; j++) {
            result += this->matrix[j + this->column * m_1_offset] *
                    matrix_1->matrix[m_2_offset + j * matrix_1->column];
        }

        res_matrix->matrix[i] = result;
    }


    /*for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < matrix_1->column; j++) {
            res_matrix->matrix[i * matrix_1->column + j] = 0;
            for (int k = 0; k < this->column; k++) {
                res_matrix->matrix[i * matrix_1->column + j] +=
                        this->matrix[i * this->column + k]
                        * matrix_1->matrix[k * matrix_1->column + j];
            }
            // TODO: Use multithreading
            //Matrix::DotproductRowColumn(i, j, this, matrix_1, res_matrix);
        }
    }*/
}

void Matrix::DotproductRowColumn(int i, int j, Matrix *matrix_1, Matrix *m2, Matrix *res_matrix) {
    for (int k = 0; k < matrix_1->row; ++k) {
        res_matrix->matrix[i * matrix_1->column + j] +=
                matrix_1->matrix[i * matrix_1->column + k]
                * m2->matrix[k * m2->column + j];
    }
}

void Matrix::transmul(Matrix *matrix_1, Matrix *res_matrix) {
    if (this->row != matrix_1->row) {
        std::cout << "Matrix dimensions do not match" << std::endl;
        std::cout << "column: " << this->column << std::endl;
        std::cout << "row: " << this->row << std::endl;
        return;
    }
    double result;
    int m_1_offset;
    int m_2_offset;
    for (int i = 0; i < res_matrix->row * res_matrix->column; i++) {
        result = 0.f;
        m_1_offset = (i % this->column);
        m_2_offset = (i % matrix_1->column);
        for (int j = 0; j < this->row; j++) {
            result += this->matrix[m_1_offset + j * this->column] *
                    matrix_1->matrix[m_2_offset + j * matrix_1->column];
        }

        res_matrix->matrix[i] = result;
    }

    /*for (int i = 0; i < this->column; i++){
        for (int j = 0; j<matrix_1->column; j++){
            res_matrix->matrix[i * this->column + j] = 0;


            for(int k = 0; k<this->row; k++){
                res_matrix->matrix[i * this->column + j] +=
                        this->matrix[k * this->column + i] *
                        matrix_1->matrix[k * this->column + j];
            }
        }
    }*/

}


Matrix *Matrix::CreateRandomMatrix(int row, int column, double min, double max) {
    double *matrix = (double *) malloc(sizeof(double) * row * column);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            matrix[i * column + j] = (double) rand() / RAND_MAX * (max - min) + min;


        }
    }
    Matrix *m = (Matrix *) malloc(sizeof(Matrix));
    m = new Matrix(row, column, matrix);
    return *&m;
}

Matrix *Matrix::InitializeValue(int row, int column, double value) {
    double *matrix = (double *) malloc(sizeof(double) * row * column);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            matrix[i * column + j] = value;
        }
    }
    Matrix *m = (Matrix *) malloc(sizeof(Matrix));
    m = new Matrix(row, column, matrix);
    return *&m;
}

void Matrix::PrintMatrix() {
    for (int i = 0; i < this->row; ++i) {
        for (int j = 0; j < this->column; ++j) {
            std::cout << this->matrix[i * this->column + j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}



