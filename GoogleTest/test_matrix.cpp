//
// Created by Moritz Hartmann on 14.03.23.
//

#include "../Matrix.h"
#include "gtest/gtest.h"



TEST(Matrix, mul) {

    double arr[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    double arr_1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    double arr_2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};



    Matrix m = Matrix(4, 4, arr);
    Matrix m_1 = Matrix(4, 4, arr_1);
    Matrix m_2 = Matrix(4, 4, arr_2);

    double res[] = {90, 100, 110, 120, 202, 228, 254, 280, 314, 356, 398, 440, 426, 484, 542, 600};

    m_1.mul(&m_2, &m);

    for (int i = 0; i < 16; ++i) {
        EXPECT_EQ(m.matrix[i], res[i]);
    }
}

TEST(Matrix, mul2){
    //Tests a 2x4 matrix with a 4x2 matrix

    double arr[] = {0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0};
    double arr_1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    double arr_2[] = {1, 2, 3, 4, 5, 6, 7, 8};

    Matrix m = Matrix(4, 4, arr);
    Matrix m_1 = Matrix(2, 4, arr_1);

    Matrix m_2 = Matrix(4, 2, arr_2);

    m_1.PrintMatrix();
    m_2.PrintMatrix();

    m_2.mul(&m_1, &m);

    double res[] = {11,14,17,20,23,30,37,44,35,46,57,68,47,62,77,92};

    for (int i = 0; i < 16; ++i) {
        EXPECT_EQ(m.matrix[i], res[i]);
    }
}


TEST(Matrix, trasmul)
{
    double arr[] = {0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0};
    double arr_1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    double arr_2[] = {1, 2, 3, 4, 5, 6, 7, 8};

    Matrix m = Matrix(2, 2, arr);
    Matrix m_1 = Matrix(4, 2, arr_1);

    Matrix m_2 = Matrix(4, 2, arr_2);

    m_1.PrintMatrix();
    m_2.PrintMatrix();

    m_1.transmul(&m_2, &m);

    double res[] = {84,100,100,120};

    m.PrintMatrix();

    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(m.matrix[i], res[i]);
    }
}

TEST(Matrix, transmul_2)
{
   // Create 3x4 and 4x3 Matrix
    double arr[] = {0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0};
    double arr_1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    double arr_2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    Matrix m = Matrix(3, 3, arr);
    Matrix m_1 = Matrix(4, 3, arr_1);

    Matrix m_2 = Matrix(4, 3, arr_2);

    m_1.PrintMatrix();
    m_2.PrintMatrix();

    m_1.transmul(&m_2, &m);

    double res[] = {166, 188, 210, 188, 214, 240, 210, 240, 270};

    m.PrintMatrix();

    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(m.matrix[i], res[i]);
    }



}


TEST(Matrix, transmul_3)
{
    // Create 3x4 and 4x3 Matrix
    double arr[] = {0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0};
    double arr_1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    double arr_2[] = {15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};

    Matrix m = Matrix(3, 3, arr);
    Matrix m_1 = Matrix(4, 3, arr_1);

    Matrix m_2 = Matrix(4, 3, arr_2);

    m_1.PrintMatrix();
    m_2.PrintMatrix();

    m_1.transmul(&m_2, &m);

    double res[] = {474, 496,518,552,578,604,630,660,690};

    m.PrintMatrix();

    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(m.matrix[i], res[i]);
    }



}

