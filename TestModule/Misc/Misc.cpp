// Misc.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <typeinfo>
#include <map>
#include <unordered_map>
using namespace std;
#pragma  message("测试 pragma message!!!!!!");
typedef unsigned __int64 uint64;
typedef unsigned __int32 uint32;
typedef signed __int32 int32;
int main()
{
	cout << __TIMESTAMP__ << endl;

	int test = 14;
	uint64 snd_uid = 15;
	uint64 to_uid = 16;
	char uidpair[500] = {};
	cout << "size:" << sizeof(uidpair) <<" si:"<< (sizeof((char*)uidpair))<<" "<<sizeof(&test) << endl;
	//不要对常数用llu,可能会输出很大的数
	//snprintf(uidpair, sizeof(uidpair), "%llu %llu", snd_uid, 18);
	snprintf(uidpair, sizeof(uidpair), "%llu %lu", snd_uid, 18);
	cout << "size1:" << sizeof(uidpair) << " si:"  << endl;
	cout << "uidpair:"<<uidpair << endl;
	//对uint64用lu似乎没有出错，记得以前会出错
	snprintf(uidpair, sizeof(uidpair), "%lu %lu", snd_uid, to_uid);
	cout << "uidpair1:" << uidpair << endl;
	cout << "size2:" << sizeof(uidpair) << " si:"   << endl;
	snprintf(uidpair, sizeof(uidpair), "%llu %lu", snd_uid, 18);
	cout << "uidpair2 :" << uidpair << endl;

	int32 a = -1;
	uint32 b = 100;
	uint32 c = (uint32)a*b;
	uint32 d = a*b;
	int32 e = a*b;
	cout << "c:" << c <<" d:"<<d<<" e:"<<e<< endl;

	char* c1 = "a";
	char* c2 = "a";
	bool c_bo = c1 == c2;
	cout << "c1==c2:" << c_bo << endl;

	std::cout << typeid(b).name() << std::endl;
	const char* name = typeid(b).name();
	bool bo =  name== "unsigned int";
	std::cout << bo << std::endl;

	unordered_map<int, int>intmap;
	cout << typeid(intmap).name() << endl;
	//cout << typeof(a) << endl;

	getchar();
    return 0;
}

//
//Subsequent work with multilayer perceptrons has shown that they are capable of approximating an XOR operator as well as many other non - linear functions.
//
//Just as Rosenblatt based the perceptron on a McCulloch - Pitts neuron, conceived in 1943, so too, perceptrons themselves are building blocks that only prove to be useful in such larger functions as multilayer perceptrons.2)
//
//The multilayer perceptron is the hello world of deep learning : a good place to start when you are learning about deep learning.
//
//A multilayer perceptron(MLP) is a deep, artificial neural network.It is composed of more than one perceptron.They are composed of an input layer to receive the signal, an output layer that makes a decision or prediction about the input, and in between those two, an arbitrary number of hidden layers that are the true computational engine of the MLP.MLPs with one hidden layer are capable of approximating any continuous function.
//
//Multilayer perceptrons are often applied to supervised learning problems3 : they train on a set of input - output pairs and learn to model the correlation(or dependencies) between those inputs and outputs.Training involves adjusting the parameters, or the weights and biases, of the model in order to minimize error.Backpropagation is used to make those weigh and bias adjustments relative to the error, and the error itself can be measured in a variety of ways, including by root mean squared error(RMSE).
//
//Feedforward networks such as MLPs are like tennis, or ping pong.They are mainly involved in two motions, a constant back and forth.You can think of this ping pong of guesses and answers as a kind of accelerated science, since each guess is a test of what we think we know, and each response is feedback letting us know how wrong we are.
//
//In the forward pass, the signal flow moves from the input layer through the hidden layers to the output layer, and the decision of the output layer is measured against the ground truth labels.
//
//In the backward pass, using backpropagation and the chain rule of calculus, partial derivatives of the error function w.r.t.the various weights and biases are back - propagated through the MLP.That act of differentiation gives us a gradient, or a landscape of error, along which the parameters may be adjusted as they move the MLP one step closer to the error minimum.This can be done with any gradient - based optimisation algorithm such as stochastic gradient descent.The network keeps playing that game of tennis until the error can go no lower.This state is known as convergence.
