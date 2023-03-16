//
// Created by Moritz Hartmann on 14.03.23.
//

#include "Matrix.h"

#ifndef UTILS_H
#include "Utils.h"
#endif

#ifndef CPPEASYCPP_NEURALNETWORK_H
#define CPPEASYCPP_NEURALNETWORK_H


class NeuralNetwork {
public:
    NeuralNetwork(int, int*);
    ~NeuralNetwork();
    int *layer;
    int layerCount;
    Matrix **layer_values;
    Matrix **layer_errors;
    Matrix **weights;

    void Init();

    void Feedforward();


    void TestPerformance(ImageTuple *test_data, int test_data_size);

    //void Train(int learningRate, int epochs, ImageTuple *training_data, int training_data_size);

    bool Evaluate(int label, Matrix *Test);

    void Backpropagation(double learning_rate);

    void Train(double learningRate, int epochs, ImageTuple *training_data, int training_data_size);

    void EvaluateError(int expected_value, Matrix *output);

    void sigmoid(Matrix *m_1);
};


#endif //CPPEASYCPP_NEURALNETWORK_H
