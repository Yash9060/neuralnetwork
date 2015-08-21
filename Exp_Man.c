/* This is 2 Layer Neural Network
 * This network has 9 -> 20 relation ship
 * This network is very basic and created for teaching computer Table of 2
 * This network has a scanning algorithm, learning algorithm, and testing algorithm.
 */

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define NUMIN 9
#define NUMOUT 20
#define NUMPAT 7
#define MAX_EPOCH 100000

#define rando() ((double)rand()/(RAND_MAX+1L))
int main()
{
    int p, i, j, k, np, op, epoch, ranpat[NUMPAT+1];
    int NumPattern=NUMPAT, NumInput=NUMIN, NumOutput=NUMOUT;
    double Input[NumPattern+1][NumInput+1], Target[NumPattern+1][NumOutput+1];
    double SumO[NumOutput+1];
    double WeightIO[NumInput+1][NumOutput+1], DeltaWeightIO[NumInput+1][NumOutput+1];
    double DeltaO[NumOutput+1], Output[NumOutput+1];
    double Error, eta=1.5, alpha=0.9, smallwt=0.4;

    /* Scanning Algorithm for scanning inputs and desired output from training_data file */
    FILE *f;
    f = fopen("train_data_9->20.data", "r");
    Input[0][0]=0.0;
    Target[0][0]=0.0;
    for(p=1; p<=NumPattern; p++)
    {
        Input[p][0]=0.0;
        for(i=1; i<=NumInput; i++)
        {
            Input[0][i]=0.0;
            fscanf(f, "%lf", &Input[p][i]);
        }
        Target[p][0]=0.0;
        for(j=1; j<=NumOutput; j++)
        {
            Target[0][j]=0.0;
            fscanf(f, "%lf", &Target[p][j]);
        }
    }
    printf("Input Scanning is done.");
    
    /* Initializing Weights to random values */
    for(j=1; j<=NumOutput; j++)
    {
        for(i=0; i<=NumInput; i++)
        {
            DeltaWeightIO[i][j]=0.0;
            WeightIO[i][j] = 2.0 * ( rando() - 0.5 ) * smallwt;
        }
    }

    /* Running Our training Algorithm */
    for(epoch=0; epoch<MAX_EPOCH; epoch++)
    {
        /* Randomizing Patterns So Error does not oscillate */
        for(p=1; p<=NumPattern; p++)
        {
            ranpat[p] = p;
        }
        for(p=1; p<=NumPattern; p++)
        {
            np = p + rando() * (NumPattern +1 -p);
            op = ranpat[p]; ranpat[p] = ranpat[np] ; ranpat[np] = op;
        }
        /* Randomizing is done */
        Error=0.0; /* Reset Error to 0.0 at every epoch section */
        for(np=1; np<=NumPattern; np++)
        {
            p = ranpat[np]; /* Selecting a random Pattern */
            /* Calculation Output */
            for(j=1; j<=NumOutput; j++)
            {
                SumO[j]=WeightIO[0][j];
                for(i=1; i<=NumInput; i++)
                {
                    SumO[j]+=Input[p][i] * WeightIO[i][j];
                }
                Output[j] = 1.0/(1.0 + exp(-SumO[j]));
                Error+=0.5 * (Target[p][j] - Output[j]) * (Target[p][j] - Output[j]); /* Error Approximation */
                DeltaO[j]=(Target[p][j] - Output[j]) * Output[j] * (1.0 - Output[j]); /* Delta (difference) in desired Output and out Output */
            }
            /* Updating Weights of input neurons to output neurons */
            for(j=1; j<=NumOutput; j++)
            {
                DeltaWeightIO[0][j] = eta * DeltaO[j] + alpha * DeltaWeightIO[0][j];
                WeightIO[0][j] += DeltaWeightIO[0][j];
                for(i=1; i<=NumInput; i++)
                {
                    DeltaWeightIO[i][j] = eta * Input[p][i] * DeltaO[j] + alpha * DeltaWeightIO[i][j];
                    WeightIO[i][j]+=DeltaWeightIO[i][j];
                }
            }
        }
        if( epoch%100 == 0 ) printf("\nEpoch %-5d :   Error = %f", epoch, Error) ;
        if( Error < 0.0004 ){ printf("\nEpoch %-5d :   Error = %f", epoch, Error); break ;}  /* stop learning when Error is too small */
    }

    /* Beginning of Testing Period */
    int iput;
    double test_input[NUMIN+1] = {0.0};
    double test_output[NUMOUT+1] = {0.0};
    double test_sum[NUMOUT+1];
    printf("\nEnter a test case:- ");
    scanf("%d", &iput);
    test_input[iput] = 1.0;
    for(j=1; j<=NumOutput; j++)
    {
        test_sum[j] = WeightIO[0][j];
        for(i=1; i<=NumInput; i++)
        {
            test_sum[j]+=WeightIO[i][j] * test_input[i];
        }
        test_output[j] = 1.0/(1.0 + exp(-test_sum[j]));
    }
    printf("Input:- ");
    for(i=1; i<=NumInput; i++)
    {
        printf("%0.1lf ", test_input[i]);
    }
    printf("\n");
    for(j=1; j<=NumOutput; j++)
    {
        printf("%0.5lf ", test_output[j]);
    }
    return 0;
}
