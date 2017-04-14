#ifndef NEURALNET_H
#define NEURALNET_H

#define DEFITER 10000
#define LEN_DATA 12
#define NUM_DATA_SETS 5

///update synapse1
///param synapse: syn to update, layer1: layer
void updatesynapse1(double synapse[], double layer1[][NUM_DATA_SETS],double layer2delta[]);
///update synapse0
void updatesynapse0(double synapse[][NUM_DATA_SETS], int layer0[][LEN_DATA], double layer1delta[][NUM_DATA_SETS]);

///deep copy of matrix
///param m: matrix to copy, m: new array
void deepcopy(int rows, int cols, int m[][cols], int newm[][cols]);
void doubledeepcopy(int rows, int cols, double m[][cols], double newm[][cols]);

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
void elementwiseMatrix(int size, double matrix1[][size], double matrix2[][size], double result[][size]);

///vector vector matrix product
///param: vector1,2 vectors of format a>b b=1 (a,b)*(b,a), result array
void vectorvectordot(double vector1[],double vector2[], int size,double result[][size]);

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

///validation routine
///param: syn0: synapse0, syn1: synapse1. data: test data
///void
void validate(double synapse0[][NUM_DATA_SETS], double synapse1[], int data[][LEN_DATA]);

#endif
