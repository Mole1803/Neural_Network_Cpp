//
// Created by Moritz Hartmann on 14.03.23.
//
#ifndef MATRIX_H
#include "Matrix.h"
#endif

#ifndef CPPEASYCPP_UTILS_H
#define CPPEASYCPP_UTILS_H

typedef struct ImageTuple{
    int label;
    Matrix* image;
} ImageTuple;

class Utils{
public:
    static void shuffle_training_data(ImageTuple* training_data, int size);
};
#endif //CPPEASYCPP_UTILS_H
