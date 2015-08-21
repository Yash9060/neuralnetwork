# Neural-Network
This is a repo containing some programs on Neural Networks.

nn.c & Neural Network XOR.c is same file. This files contains ready-made code for training XOR to a Neural Network.

Exp_Man.c is code written by me for training neural network table of 2.

Exp-1.c is a modified version of nn.c created by me for training neural network table of 2.

mul_train.c and mul_test.c are neural networks created with the help of fann.h library, this library contains all required function and easy to create. This library can be much more useful.

scanner.c is program i created to so that we can set input values and their diesired output values in arrays so we can train our neural network.

train_data_9-to-20.data contains a randomly generated input file for training neural network table of 2.
train_data_9-to-100.data contains a randomly generated input file for training neural network tables from 1 and upto 9.

fann_train_data.data is a training input file which is passed directly to fann functions so it can train neural networks based on that.
fann_output_data.data is a output file generated by mul_train.c, generally this file is passed to mul_test.c for testing out our inputs and check accuracy. This file contains every detail of neural network that we trained.

Generator.py is a python file created for generating input training file, containing random values.
