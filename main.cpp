#include <iostream>
#include "Matrix.h"
#include "Reader.h"
#include "NeuralNetwork.h"

std::string TRAINING_IMAGE_PATH =   "/Users/moritzhartmann/CLionProjects/NeuralNetworkCPP/Ressources/training_data/train-images.idx3-ubyte";
std::string TRAINING_LABEL_PATH =   "/Users/moritzhartmann/CLionProjects/NeuralNetworkCPP/Ressources/training_data/train-labels.idx1-ubyte";
std::string TEST_IMAGE_PATH =       "/Users/moritzhartmann/CLionProjects/NeuralNetworkCPP/Ressources/data/t10k-images.idx3-ubyte";
std::string TEST_LABEL_PATH =       "/Users/moritzhartmann/CLionProjects/NeuralNetworkCPP/Ressources/data/t10k-labels.idx1-ubyte";


int main() {

    Matrix matrix(2,2, new double[4]{1,2,3,4});
    std::cout<< matrix.row << std::endl;

    Reader reader;
    ImageTuple *training_data = reader.read(TRAINING_IMAGE_PATH,TRAINING_LABEL_PATH);

    ImageTuple *test_data = reader.read(TEST_IMAGE_PATH,TEST_LABEL_PATH);


    NeuralNetwork neuralNetwork(3, new int[3]{784, 28, 10});
    for(int epoch=0; epoch<10; epoch++){
        neuralNetwork.Train(0.5, 1, training_data, 60000);
        neuralNetwork.TestPerformance(test_data, 10000);

    }
    neuralNetwork.TestPerformance(test_data, 10000);
    return 0;
}
