cmake_minimum_required(VERSION 3.23)
project(CPPEasyCpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(CPPEasyCpp main.cpp Matrix.cpp Matrix.cpp Matrix.h  Reader.cpp Reader.h NeuralNetwork.cpp NeuralNetwork.cpp NeuralNetwork.h Stackmanager.cpp Stackmanager.h Utils.cpp Utils.h)

add_subdirectory(GoogleTest)
