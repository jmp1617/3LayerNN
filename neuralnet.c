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

void vector_matrix(int size, double matrix[][size], double vector[], double newvec[]){
    for(int row=0;row<NUM_DATA_SETS;row++){
        for(int col=0;col<NUM_DATA_SETS;col++){
            newvec[row]+=matrix[row][col]*vector[row];
        }
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
     for(int row = 0;row<NUM_DATA_SETS;row++){
             for(int col=0;col<NUM_DATA_SETS;col++){
                 printf("%f ",result[row][col]);
             }
             printf("\n");
         }

}

void generate_synapse1(double synapse[]){
    srand(time(NULL));
    for(int col=0;col<NUM_DATA_SETS;col++){
        synapse[col] = (double)rand()/RAND_MAX*2.0-1.0;
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

void analyze(int iterations, int size, int data[][size], int solution[]){
    //generate initial synapse weights
    double synapse0[LEN_DATA][NUM_DATA_SETS]={0};
    double synapse1[NUM_DATA_SETS]={0};
    int layer0[NUM_DATA_SETS][LEN_DATA]={0};
    double layer1[NUM_DATA_SETS][NUM_DATA_SETS]={0};//hidden weights
    double layer2[NUM_DATA_SETS]={0};//guesses
    generate_synapse0(LEN_DATA, synapse0);
    generate_synapse1(synapse1);
    
#ifdef DEBUG
    printf("INITIAL DATA\n");
    for(int row=0; row<NUM_DATA_SETS; row++){//print the data
        for(int col=0; col<LEN_DATA; col++){
            printf("%d ",data[row][col]);
        }
        printf("\n");
    }
    printf("SOLUTION DATA\n");
    for(int i=0;i<4;i++){
        printf("%d\n", solution[i]);
    }
    printf("SYNAPSE1\n");
         for(int col=0;col<NUM_DATA_SETS;col++){//print synapse1
             printf("%f \n",synapse1[col]);
         }
    
#endif
    
    //training loop
    for(int train = 0; train<1; train++){
        //prepare layer 0
        deepcopy(4,3,data,layer0);//fill up layer 0
        //LAYER 0 COMPLETE
        //prepare layer 1
        //perform matrix multiplication on layer 0 and synapse0 and store the 
        //r}sults in layer 1
        matrix_mult(LEN_DATA, layer0, NUM_DATA_SETS, synapse0, layer1);
#ifdef DEBUG
        printf("SYNAPSE0\n");
        for(int row=0;row<3;row++){
            for(int col=0;col<4;col++){
                printf("%f ",synapse0[row][col]);
            }
            printf("\n");
        }
        printf("SYNAPSE1\n");
        for(int col=0;col<NUM_DATA_SETS;col++){//print synapse1
            printf("%f \n",synapse1[col]);
        }
        printf("LAYER1: MATRIX AFTER MULTIPLICATION, pre sigmoid\n");
        for(int row=0;row<4;row++){
            for(int col=0;col<4;col++){
                printf("%f ",layer1[row][col]);
            }
            printf("\n");
        }
#endif  //push layer one through the nunlinearitly function(sigmoid)
        nonlinearity(NUM_DATA_SETS, layer1);
#ifdef DEBUG
        printf("LAYER1: MATRIX AFTER NONLINEARITY, post sigmoid\n");
        for(int row=0;row<4;row++){
            for(int col=0;col<4;col++){
                printf("%f ",layer1[row][col]);
            }
            printf("\n");
        }
#endif
        //LAYER ONE COMPLETED
        //prepare layer 2
        //perform vertor matrix multiplication on layer1 and synapse 1 
        //store the results in layer2 matrix
        vector_matrix(NUM_DATA_SETS, layer1, synapse1, layer2);
#ifdef DEBUG
        printf("LAYER2: VECTOR AFTER MULTIPLICATION, pre sigmoid\n");
        for(int i=0;i<NUM_DATA_SETS;i++){
            printf("%f\n", layer2[i]);
        }
#endif  
        //run layer2 though the sigmoid function
        nonlinearityVector(layer2);
#ifdef DEBUG
        printf("LAYER2: VECTOR AFTER NONLINEARITY, post sigmoid\n");
        for(int i=0;i<NUM_DATA_SETS;i++){
            printf("%f\n", layer2[i]);
        }
#endif
        //LAYER TWO COMPLETED
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
