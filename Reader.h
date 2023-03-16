//
// Created by Moritz Hartmann on 14.03.23.
//


#ifndef UTILS_H
#include "Utils.h"
#endif

#ifndef CPPEASYCPP_READER_H
#define CPPEASYCPP_READER_H





class Reader {
public:
    int magic_number_images;
    int number_of_images;
    int n_rows;
    int n_cols;

    Reader();
    ImageTuple* read(std::string, std::string);

    static int reverse_int(int i);

    int magic_number_labels;
    int number_of_labels;
};


#endif //CPPEASYCPP_READER_H
