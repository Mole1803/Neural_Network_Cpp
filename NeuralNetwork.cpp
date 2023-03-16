//
// Created by Moritz Hartmann on 14.03.23.
//

#include <cstdlib>
#include <iostream>
#include <cmath>
#include "NeuralNetwork.h"



NeuralNetwork::NeuralNetwork(int size, int* layer) {
    this->layer = layer;
    this->layerCount = size;

    this->weights = (Matrix **) malloc(sizeof(Matrix *) * (this->layerCount - 1));
    this->layer_values = (Matrix **) malloc(sizeof(Matrix *) * this->layerCount);
    this->layer_errors = (Matrix **) malloc(sizeof(Matrix *) * this->layerCount-1);
    this->Init();
}

NeuralNetwork::~NeuralNetwork() {
    free(this->layer);
    free(this->weights);
    free(this->layer_values);
    free(this->layer_errors);
}

void NeuralNetwork::Init(){
    for(int i=0; i<this->layerCount-1; i++){
        this->weights[i] = Matrix::CreateRandomMatrix(this->layer[i+1], this->layer[i], 0.001, 0.01);
    }

    for(int i=0; i<this->layerCount; i++){
        this->layer_values[i] = Matrix::InitializeValue(this->layer[i], 1, 0);
    }

    for(int i=0; i<this->layerCount-1; i++){
        this->layer_errors[i] = Matrix::InitializeValue(this->layer[i+1], 1, 0);
    }
}

void NeuralNetwork::Train(double learningRate, int epochs, ImageTuple* training_data, int training_data_size){
    for(int i=0; i<epochs; i++){
        Utils::shuffle_training_data(training_data, training_data_size);
        for(int j=0; j<training_data_size; j++){
            this->layer_values[0] = training_data[j].image;
            this->Feedforward();
            this->EvaluateError(training_data[j].label, this->layer_values[this->layerCount-1]);
            this->Backpropagation(learningRate);
        }
    }
}

void NeuralNetwork::TestPerformance(ImageTuple* test_data, int test_data_size){
    int correct = 0;
    for(int i=0; i<test_data_size; i++){
        this->layer_values[0] = test_data[i].image;
        this->Feedforward();
        if(this->Evaluate(test_data[i].label, this->layer_values[this->layerCount-1])){
            correct++;
        }
    }

    std::cout<<"Performance: "<< correct<<" / "<<test_data_size<<std::endl;
}


void NeuralNetwork::Feedforward(){
    for(int i=0; i<this->layerCount-1; i++){
        this->weights[i]->mul(this->layer_values[i], this->layer_values[i+1]);
        // TODO: Add activation function
        this->sigmoid(this->layer_values[i+1]);
    }
}


void NeuralNetwork::EvaluateError(int expected_value, Matrix* output){
    for(int i=0; i<output->row; i++){
        if(i==expected_value){
            this->layer_errors[this->layerCount-2]->matrix[i] = 1 - output->matrix[i];
            continue;
        }
        this->layer_errors[this->layerCount-2]->matrix[i] = 0 - output->matrix[i];

    }
}

void NeuralNetwork::Backpropagation(double learning_rate=0.1){

    for(int i=this->layerCount-3;i>=0; i--){
        this->weights[i+1]->transmul(this->layer_errors[i+1], this->layer_errors[i]);
    }

    double activation_derivative;
    int rows;
    int columns;

    int row_columns;

    for(int weight_matrix_index = this->layerCount-2; weight_matrix_index>=0; weight_matrix_index--){
        rows = this->weights[weight_matrix_index]->row;
        columns = this->weights[weight_matrix_index]->column;
        for(int row=0;row<rows;row++){
            //TODO: Add activation function derivative
            activation_derivative = this->layer_values[weight_matrix_index+1]->matrix[row]
                    *(1-this->layer_values[weight_matrix_index+1]->matrix[row]);
            row_columns = row*columns;
            for(int column=0;column<columns;column++) {
                this->weights[weight_matrix_index]->matrix[row_columns + column] += learning_rate
                                                                                    *
                                                                                    this->layer_errors[weight_matrix_index]->matrix[row]
                                                                                    *
                                                                                    this->layer_values[weight_matrix_index]->matrix[column]
                                                                                    * activation_derivative;
            }
        }
    }
}

bool NeuralNetwork::Evaluate(int label, Matrix* Test){
    int max_index = -1;
    double max_value = 0;
    //Test->PrintMatrix();
    for(int i=0; i<this->layer_values[this->layerCount-1]->row; i++){

        if(Test->matrix[i]>max_value){
            max_value = Test->matrix[i];
            max_index = i;
        }
    }
    return max_index == label;
}

// Activation functions
void NeuralNetwork::sigmoid(Matrix* m_1){
    for(int i=0; i<m_1->row; i++){
        m_1->matrix[i] = 1/(1+exp(-m_1->matrix[i]));
    }
}

double sigmoid_derivative(int index){

}


// Created by Moritz Hartmann on 14.03.23
