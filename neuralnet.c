//3 layer deep learning network
//random initial weights
//backpropagation
//
//usage: neuralnet [iterations of learning]

#include "neuralnet.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double nonlinearity(int x){
    return 1/(1+exp(-x));
}

double nonlinearityprime(int x){
    return x*(1-x);
}

void analyze(int iterations, int size, int data[][size], int solution[]){

}

int main(int argc, char * argv[]){
    
    int len_data = 3;
    int num_data_sets = 4;

    //data to train
    int data[4][3] = {
        {0,0,1},
        {0,1,1},
        {1,0,1},
        {1,1,1}
    };

    //the pattern is the 2nd col must contain a 1 and either the
    //0th or 1st col must also be 1, but not both
    int solution[4] = {0,1,1,0}; 

    if (argc==1){//use default iterations
        analyze(0,len_data,data,solution);
    }
    else if(argc==2){//use user specified inputs
        analyze(atoi(argv[1]),len_data,data,solution); 
    }
    else{
        printf("Usage: neuralnet [optional iter count]");
    }
    return 0;
}
