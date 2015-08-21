/*******************************************************************************
*    nn.c   1.0                                       � JOHN BULLINARIA  2004  *
*******************************************************************************/

/*      To compile use "cc nn.c -O -lm -o nn" and then run using "./nn"       */
/*      For explanations see:  http://www.cs.bham.ac.uk/~jxb/NN/nn.html       */

#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <math.h>
#include <fcntl.h>

#define NUMPAT 7
#define NUMIN  9
#define NUMOUT 20

#define rando() ((double)rand()/(RAND_MAX+1L))

main() {
    int    i, j, k, p, np, op, ranpat[NUMPAT+1], epoch;
    int    NumPattern = NUMPAT, NumInput = NUMIN, NumOutput = NUMOUT;
    double Input[NUMPAT+1][NUMIN+1];
    double Target[NUMPAT+1][NUMOUT+1];
    double WeightIO[NUMIN+1][NUMOUT+1];
    double SumO[NUMPAT+1][NUMOUT+1], Output[NUMPAT+1][NUMOUT+1];
    double DeltaO[NUMOUT+1];
    double DeltaWeightIO[NUMIN+1][NUMOUT+1];
    double Error, eta = 5.0, alpha = 0.8, smallwt = 0.7;
  
    for( j = 1 ; j <= NumOutput ; j++ ) {    /* initialize WeightIH and DeltaWeightIH */
        for( i = 0 ; i <= NumInput ; i++ ) { 
            DeltaWeightIO[i][j] = 0.0 ;
            WeightIO[i][j] = 2.0 * ( rando() - 0.5 ) * smallwt ;
        }
    }
    
    /* Learning from a trainig_data.data file. */
    FILE *f;
    f = fopen("train_data_9->20.data", "r");
    for(i=1; i<=NumPattern; i++)
    {
        Input[i][0]=0;
        Target[i][0]=0;
        for(j=1; j<=NumInput; j++)
        {
            Input[0][j]=0;
            fscanf(f, "%lf", &Input[i][j]);
        }
        for(k=1; k<=NumOutput; k++)
        {
            Target[0][k]=0;
            fscanf(f, "%lf", &Target[i][k]);
        }
    }
    
    for( epoch = 0 ; epoch < 100000 ; epoch++) {    /* iterate weight updates */
        for( p = 1 ; p <= NumPattern ; p++ ) {    /* randomize order of individuals */
            ranpat[p] = p ;
        }
        for( p = 1 ; p <= NumPattern ; p++) {
            np = p + rando() * ( NumPattern + 1 - p ) ;
            op = ranpat[p] ; ranpat[p] = ranpat[np] ; ranpat[np] = op ;
        }
        Error = 0.0 ;
        for( np = 1 ; np <= NumPattern ; np++ ) {    /* repeat for all the training patterns */
            p = ranpat[np];
            for( j = 1 ; j <= NumOutput ; j++ ) {    /* compute hidden unit activations */
                SumO[p][j] = WeightIO[0][j] ;
                for( i = 1 ; i <= NumInput ; i++ ) {
                    SumO[p][j] += Input[p][i] * WeightIO[i][j] ;
                }
                Output[p][j] = 1.0/(1.0 + exp(-SumO[p][j]));   /* Sigmoidal Outputs */
                Error += 0.5 * (Target[p][j] - Output[p][j]) * (Target[p][j] - Output[p][j]) ;
                DeltaO[j] = (Target[p][j] - Output[p][j]) * Output[p][j] * (1.0 - Output[p][j]) ;
            }
            for( j = 1 ; j <= NumOutput ; j++ ) {     /* update weights WeightIO */
                DeltaWeightIO[0][j] = eta * DeltaO[j] + alpha * DeltaWeightIO[0][j] ;
                WeightIO[0][j] += DeltaWeightIO[0][j] ;
                for( i = 1 ; i <= NumInput ; i++ ) { 
                    DeltaWeightIO[i][j] = eta * Input[p][i] * DeltaO[j] + alpha * DeltaWeightIO[i][j];
                    WeightIO[i][j] += DeltaWeightIO[i][j] ;
                }
            }
        }
        if( epoch%100 == 0 ) fprintf(stdout, "\nEpoch %-5d :   Error = %f", epoch, Error) ;
        if( Error < 0.0004 ) break ;  /* stop learning when 'near enough' */
    }

  /*printf("\n\nNETWORK DATA - EPOCH %d\n\nPat\t", epoch) ;
    for( p = 1 ; p <= NumPattern ; p++ ) {        
        printf("\n%d\t", p) ;
        for( i = 1 ; i <= NumInput ; i++ ) {
            printf("%f ", Input[p][i]);
        }
        printf("\t");
        for( k = 1 ; k <= NumOutput ; k++ ) {
            printf("%f %f\t", Target[p][k], Output[p][k]) ;
        }
    }*/
    
    /* This is code for taking test on how well your neural network has learned */
    /* This code is specific to this Neural Network, However one can edit it easily for their network */
    printf("\nTesting period now\n");
    int iput, test_input[NUMIN+1]={0};
    double test_sum[NumOutput+1], test_output[NumOutput+1];
    while (1) {
        scanf("%d", &iput);
        if(iput > 9 || iput < 1) break;
        test_input[iput]=1;
        for( j = 1 ; j <= NumOutput ; j++ ) {    /* compute hidden unit activations */
                test_sum[j] = WeightIO[0][j] ;
                for( i = 1 ; i <= NumInput ; i++ ) {
                    test_sum[j] += test_input[i] * WeightIO[i][j] ;
                }
                test_output[j] = 1.0/(1.0 + exp(-test_sum[j]));   /* Sigmoidal Outputs */
        }
        printf("Input:- ");
        for(i=1; i<=NumInput; i++)
        {
            printf("%d ", test_input[i]);
        }
        printf("\nOutput:- ");
        for(i=1; i<=NumOutput; i++)
        {
            printf("%0.4f ", test_output[i]);
        }
        test_input[iput]=0;
        printf("\n");
    }
    printf("\n\nGoodbye!\n\n") ;
    return 1 ;
}

/*******************************************************************************/
