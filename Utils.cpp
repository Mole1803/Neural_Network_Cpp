//
// Created by Moritz Hartmann on 14.03.23.
//


#include "Utils.h"
#include <cstdlib>
#include <ctime>



void Utils::shuffle_training_data(ImageTuple *training_data, int size) {
    time_t t;
    srand((unsigned) time(&t));
    for (int i = 0; i < size; i++) {
        int random_index = rand() % size;
        ImageTuple temp = training_data[i];
        training_data[i] = training_data[random_index];
        training_data[random_index] = temp;
    }
}
