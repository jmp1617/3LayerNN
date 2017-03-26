#ifndef NEURALNET_H
#define NEURALNET_H

#define DEFITER 10000
#define LEN_DATA 3
#define NUM_DATA_SETS 4

///generate a list of random numbers
///param: synapse: list
void generate_synapse1(double synapse[]);

///generate table of random values between -1 and 1
///param: size: depth of table, synapse: table of values
void generate_synapse0(int size, double synapse[][size]);

///nonlinearity derivative to test against
///the neural nets confidence
///param: x: the value to put though sigmoid derivative
double nonlinearityprime(int x);

///nonlinearity using a sigmoid function to map
///any value to a number between 0 and 1
///param: x: the value to put through sigmoid function
double nonlinearity(int x);

///main learning routine, 
///param: iterations: number of training loops
///if iterations is 0 default to 10,000
void analyze(int iterations, int size, int data[][size], int solution[]);

#endif
