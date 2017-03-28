///contains all of the needed function declarations
#include <stdio.h>
#include "neuralnet.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

void deepcopy(int rows, int cols, int m[][cols], int newm[][cols]){
    for(int row=0;row<rows;row++){
        for(int col=0;col<cols;col++){
            newm[row][col] = m[row][col];
        }
    }
}

void doubledeepcopy(int rows, int cols, double m[][cols], double newm[][cols]){
    for(int row=0;row<rows;row++){
        for(int col=0;col<cols;col++){
            newm[row][col] = m[row][col];
        }
    }
}

void vector_matrix(int size, double matrix[][size], double vector[], double newvec[]){
    for(int row=0;row<NUM_DATA_SETS;row++){
        for(int col=0;col<NUM_DATA_SETS;col++){
            newvec[row]+=matrix[row][col]*vector[col]; //real matrix vector mult
        }                                              //would be row instead col    
    }
}

void matrix_mult(int size1, int matrix1[][size1], int size2, double matrix2[][size2], double result[][size2]){
    for(int row=0;row<NUM_DATA_SETS;row++){
        for(int col=0;col<NUM_DATA_SETS;col++){
            for(int inner = 0;inner<LEN_DATA;inner++){
                result[row][col] += matrix1[row][inner] * matrix2[inner][col];
            }
        }
    }
}

void nonlinearity(int size, double table[][size]){
    for(int row=0;row<NUM_DATA_SETS;row++){
        for(int col=0;col<size;col++){
            table[row][col] = 1/(1+exp(-table[row][col]));
        }
    }
}

void nonlinearityVector(double vector[]){
    for(int i=0;i<NUM_DATA_SETS;i++){
        vector[i]=1/(1+exp(-vector[i]));
    }
}

void nonlinearityprime(int size, double table[][size]){
    for(int row=0;row<NUM_DATA_SETS;row++){
        for(int col=0;col<size;col++){
            table[row][col] = table[row][col]*(1-table[row][col]);
        }
    }
}

void nonlinearityprimeVector(double table[]){
    for(int col=0;col<NUM_DATA_SETS;col++){
        table[col]=table[col]*(1-table[col]);
    }
}

void elementwiseVector(double vector1[], double vector2[], double result[]){
    for(int element=0;element<NUM_DATA_SETS;element++){
        result[element] = vector1[element]*vector2[element];
    }
}

void elementwiseMatrix(int size, double matrix1[][size], double matrix2[][size], double result[][size]){
    for(int row=0;row<size;row++){
        for(int col=0;col<size;col++){
            result[row][col] = matrix1[row][col] * matrix2[row][col];
        }
    }
}

void vectorvectordot(double vector1[], double vector2[], int size, double result[][size]){
    for(int row=0;row<NUM_DATA_SETS;row++){
        for(int col=0;col<NUM_DATA_SETS;col++){
            result[row][col] = vector1[row] * vector2[col];
        }
    }
}

void checkerror(double layer2[], int solution[], double error[]){
    for(int sol=0;sol<NUM_DATA_SETS;sol++){
        error[sol] = solution[sol] - layer2[sol];
    }
}

double meanabs(double input_error[]){
    double mean = 0.0;
    for(int error=0;error<NUM_DATA_SETS;error++){
        mean = fabs(input_error[error]);
    }
    return mean/NUM_DATA_SETS;
}
