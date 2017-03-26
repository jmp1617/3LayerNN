//3 layer deep learning network
//random initial weights
//backpropagation
//
//usage: neuralnet [iterations of learning]

#include "neuralnet.h"
#include <stdio.h>
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

void matrix_mult(int size1, double matrix1[][size1], int size2, double matrix2[][size2], int result[][size1]){

}

void generate_synapse1(double synapse[]){
    srand(time(NULL));
    for(int col=0;col<NUM_DATA_SETS;col++){
        synapse[col] = (double)rand()/RAND_MAX*2.0-1.0;//rand between -1 and 1
    }
}

void generate_synapse0(int size, double synapse[][size]){
    srand(time(NULL));
    for(int row=0; row<NUM_DATA_SETS; row++){
        for(int col=0; col<LEN_DATA; col++){
            synapse[row][col] = (double)rand()/RAND_MAX*2.0-1.0; //rand float between -1 and 1
        }
    }
}

double nonlinearity(int x){
    return 1/(1+exp(-x));
}

double nonlinearityprime(int x){
    return x*(1-x);
}

void analyze(int iterations, int size, int data[][size], int solution[]){
    //generate initial synapse weights
    double synapse0[LEN_DATA][NUM_DATA_SETS];
    double synapse1[NUM_DATA_SETS];
    generate_synapse0(LEN_DATA, synapse0);
    generate_synapse1(synapse1);
    /*
    for(int row=0; row<LEN_DATA; row++){//print synapse0
        for(int col=0; col<NUM_DATA_SETS; col++){
            printf(">%f<",synapse0[row][col]);
        }
        printf("\n");
    }
    for(int col=0;col<NUM_DATA_SETS;col++){//print synapse1
        printf(">%f<\n",synapse1[col]);
    }
    for(int row=0; row<NUM_DATA_SETS; row++){//print the data
        for(int col=0; col<LEN_DATA; col++){
            printf("-%d-",data[row][col]);
        }
        printf("\n");
    }
    */
    //training loop
    for(int train = 0; train<1; train++){
        int layer0[NUM_DATA_SETS][LEN_DATA];//training data
        double layer1[NUM_DATA_SETS][LEN_DATA];//hidden weights
        double layer2[NUM_DATA_SETS];//guesses
        deepcopy(4,3,data,layer0);//fill up layer 1
        for(int row=0;row<4;row++){ 
         for(int col=0;col<3;col++){
             printf("%d",layer0[row][col]);
         }
         printf("\n");
     }


    }
}

int main(int argc, char * argv[]){

    //data to train
    int data[NUM_DATA_SETS][LEN_DATA] = {
        {0,0,1},
        {0,1,1},
        {1,0,1},
        {1,1,1}
    };

    //the pattern is the 2nd col must contain a 1 and either the
    //0th or 1st col must also be 1, but not both
    int solution[NUM_DATA_SETS] = {0,1,1,0}; 

    if (argc==1){//use default iterations
        analyze(0,LEN_DATA,data,solution);
    }
    else if(argc==2){//use user specified inputs
        analyze(atoi(argv[1]),LEN_DATA,data,solution); 
    }
    else{
        printf("Usage: neuralnet [optional iter count]");
    }
    return 0;
}
