#ifndef NEURALNET_H
#define NEURALNET_H

#define DEFITER 10000
#define LEN_DATA 3
#define NUM_DATA_SETS 4

///deep copy of matrix
///param m: matrix to copy, m: new array
void deepcopy(int rows, int cols, int m[][cols], int newm[][cols]);

///vector matrix multiplication
///param matrix: the matrix, vector: vector to multiply the matrix by
void vector_matrix(int size, double matrix[][size], double vector[], double newvec[]);

///matrix multiplication for layer 0 and synapse 0
///param size1,size2: sizes, matrix1, and matrix2 to be multiplied
void matrix_mult(int size1, int matrix1[][size1], int size2, double matrix[][size2], double result[][size1]);

///generate a list of random numbers
///param: synapse: list
void generate_synapse1(double synapse[]);

///generate table of random values between -1 and 1
///param: size: depth of table, synapse: table of values
void generate_synapse0(int size, double synapse[][size]);

///nonlinearity derivative to test against
///the neural nets confidence
///param: x: the value to put though sigmoid derivative
void nonlinearityprime(int size, double table[][size]);
///same thing but for vectors
void nonlinearityprimeVector(double table[]);

///nonlinearity using a sigmoid function to map
///any value to a number between 0 and 1
///param: x: the value to put through sigmoid function
void nonlinearity(int size, double table[][size]);
///same thing but for vectors
void nonlinearityVector(double table[]);

///element wise vector multiplication
///for multiplying "guesses" by offset
void elementwiseVector(double vector1[], double vector2[], double result[]);

///calculate error vector 
///param: layer2: layer2 vector. solution: solution, error: error vector
void checkerror(double layer2[], int solution[], double error[]); 

///mean the absolute values of the vector
///param: error: error vector
double meanabs(double error[]);

///main learning routine, 
///param: iterations: number of training loops
///if iterations is 0 default to 10,000
void analyze(int iterations, int size, int data[][size], int solution[]);

#endif
