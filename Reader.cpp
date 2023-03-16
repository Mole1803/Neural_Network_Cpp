//
// Created by Moritz Hartmann on 14.03.23.
//

#include <string>
#include <fstream>
#include <utility>
#include <iostream>
#include "Reader.h"


Reader::Reader() {
}

int Reader::reverse_int(int i) {
    unsigned char ch1, ch2, ch3, ch4;

    ch1 = i & 255;// 8 bit

    ch2 = (i >> 8) & 255;

    ch3 = (i >> 16) & 255;

    ch4 = (i >> 24) & 255;

    return ((int) ch1 << 24) + ((int) ch2 << 16) + ((int) ch3 << 8) + ch4;
}

ImageTuple *Reader::read(std::string image_path, std::string label_path) {
    std::ifstream training_data_image(image_path, std::ios::in | std::ios::binary);
    std::ifstream training_data_label(label_path, std::ios::in | std::ios::binary);

    this->magic_number_images = 0;
    this->number_of_images = 0;
    this->n_rows = 0;
    this->n_cols = 0;
    this->magic_number_labels = 0;
    this->number_of_labels = 0;

    // Read Image File

    // Read the magic number
    training_data_image.read((char*)&this->magic_number_images, sizeof(this->magic_number_images));
    this->magic_number_images = reverse_int(this->magic_number_images);

    // Read the number of images
    training_data_image.read((char*)&this->number_of_images, sizeof(this->number_of_images));
    this->number_of_images = reverse_int(this->number_of_images);

    // Read the number of rows and columns
    training_data_image.read((char*)&this->n_rows, sizeof(this->n_rows));
    this->n_rows = reverse_int(this->n_rows);
    training_data_image.read((char*)&this->n_cols, sizeof(this->n_cols));
    this->n_cols = reverse_int(this->n_cols);


    // Read Label File

    // Read the magic number
    training_data_label.read((char*)&this->magic_number_labels, sizeof(this->magic_number_labels));
    this->magic_number_labels = reverse_int(this->magic_number_labels);

    // Read the number of labels
    training_data_label.read((char*)&this->number_of_labels, sizeof(this->number_of_labels));
    this->number_of_labels = reverse_int(this->number_of_labels);

    // Output the values
    //

    std::cout << "Magic Number: " << this->magic_number_images << std::endl;
    std::cout << "Number of Images: " << this->number_of_images << std::endl;
    std::cout << "Number of Rows: " << this->n_rows << std::endl;
    std::cout << "Number of Columns: " << this->n_cols << std::endl;

    std::cout << "Magic Number: " << this->magic_number_labels << std::endl;
    std::cout << "Number of Labels: " << this->number_of_labels << std::endl;

    // Validate the values
    if (this->magic_number_images != 2051) {
        std::cout << "Invalid magic number for image file!" << std::endl;
        return nullptr;
    }

    if (this->magic_number_labels != 2049) {
        std::cout << "Invalid magic number for label file!" << std::endl;
        return nullptr;
    }

    if (this->number_of_images != this->number_of_labels) {
        std::cout << "Number of images and labels do not match!" << std::endl;
        return nullptr;
    }

    // Read the images and labels

    auto *image_tuple_array = (ImageTuple *) malloc(number_of_images * sizeof(ImageTuple));

    for (int i = 0; i < number_of_images; i++) {
        image_tuple_array[i].image = (Matrix *) malloc(sizeof(Matrix));
        image_tuple_array[i].image->matrix = (double *) malloc(n_rows * n_cols * sizeof(double));
        image_tuple_array[i].image->row = n_rows* n_cols;
        image_tuple_array[i].image->column = 1;

        for (int j = 0; j < n_rows * n_cols; j++) {
            image_tuple_array[i].image->matrix[j] = (double) training_data_image.get() / 255;
        }
        image_tuple_array[i].label = training_data_label.get();

    }

    return image_tuple_array;

}


