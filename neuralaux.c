///contains all of the needed function declarations
#include <stdio.h>
#include "neuralnet.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

void validate(double synapse0[][NUM_DATA_SETS], double synapse1[], int data[][LEN_DATA]){
    int layer0[NUM_DATA_SETS][LEN_DATA]={0};
    double layer1[NUM_DATA_SETS][NUM_DATA_SETS]={0};
    double layer2[NUM_DATA_SETS]={0};
    deepcopy(NUM_DATA_SETS,LEN_DATA,data,layer0);
    matrix_mult(LEN_DATA, layer0, NUM_DATA_SETS, synapse0, layer1);
    nonlinearity(NUM_DATA_SETS, layer1);
    vector_matrix(NUM_DATA_SETS, layer1, synapse1, layer2);
    nonlinearityVector(layer2);
    for(int row=0;row<NUM_DATA_SETS;row++){
        printf("Test Set: ");
        for(int col=0;col<LEN_DATA;col++){
            printf("%d ",data[row][col]);
        }
        printf("- NN Guess: %f%% sure this is correct",(layer2[row])*100);
        if((layer2[row]*100)>90){
            printf(" -> 1\n");
        }
        else{
            printf(" -> 0\n");
        }
    }
}

void updatesynapse1(double synapse[], double layer1[][NUM_DATA_SETS], double layer2delta[]){
    double toadd[NUM_DATA_SETS]={0};       //vector matrix
    for(int col=0;col<NUM_DATA_SETS;col++){//using col first because the array needs to be
        for(int row=0;row<NUM_DATA_SETS;row++){// transposed
            toadd[col] += layer1[row][col] * layer2delta[row];
        }
    }
    for(int weight=0;weight<NUM_DATA_SETS;weight++){
        synapse[weight]+=toadd[weight];
    }
}

void updatesynapse0(double synapse[][NUM_DATA_SETS], int layer0[][LEN_DATA], double layer1delta[][NUM_DATA_SETS]){
    //transpose layer0;
    int transposedl0[LEN_DATA][NUM_DATA_SETS]={0};
    for(int col=0;col<LEN_DATA;col++){
        for(int row=0;row<NUM_DATA_SETS;row++){
            transposedl0[col][row] = layer0[row][col];
        }
    }
    float dotmult[LEN_DATA][NUM_DATA_SETS]={0};
    //matrix multiplication
    for(int row=0;row<LEN_DATA;row++){
        for(int col=0;col<NUM_DATA_SETS;col++){
            for(int inner=0;inner<NUM_DATA_SETS;inner++){
                dotmult[row][col] += transposedl0[row][inner] * layer1delta[inner][col];
            }
        }
    }
    //add the new matrix to the synapse weights
    for(int row=0;row<LEN_DATA;row++){
        for(int col=0;col<NUM_DATA_SETS;col++){
            synapse[row][col] += dotmult[row][col];
        }
    }
}

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
