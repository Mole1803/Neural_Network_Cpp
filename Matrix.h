//
// Created by Moritz Hartmann on 13.03.23.
//




#ifndef CPPEASYCPP_MATRIX_H
#define CPPEASYCPP_MATRIX_H


class Matrix {
public:
    double* matrix;
    int row;
    int column;

    Matrix(int, int, double*);
    void mul(Matrix*,Matrix*);
    static void DotproductRowColumn(int i, int j, Matrix *matrix_1, Matrix *m2, Matrix *res_matrix);
    static Matrix* CreateRandomMatrix(int row, int column, double min, double max);
    void transmul(Matrix*,Matrix*);

    void PrintMatrix();

    static Matrix *InitializeValue(int row, int column, double value);
};


#endif //CPPEASYCPP_MATRIX_H
