
/* This is scanner algorithem.
   This helps to scan training data from a pregenerated file
   and use it in out Neural Network program.
   Prasanna K Patil
*/

#include<stdio.h>

int main()
{   
    int NumPattern=7, NumInput=9, NumOutput=100;
    int i, j, k;
    double Input[NumPattern+1][NumInput+1], Target[NumPattern+1][NumOutput+1];
    FILE *f;
    f = fopen("train_data.data", "r");
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
    
    for(i=1; i<=NumPattern; i++)
    {   
        printf("Input:- ");
        for(j=1; j<=NumInput; j++)
        {
            printf("%lf ", Input[i][j]);
        }
        printf("\nTarget:- ");
        for(k=1; k<=NumOutput; k++)
        {
            printf("%lf ", Target[i][k]);
        }
        printf("\n");
    }
}
