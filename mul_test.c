#include <stdio.h>
#include "floatfann.h"

int main()
{
    fann_type *calc_out;
    fann_type input[]={0,0,0,0,0,0,0,0,0};
    int i, in1, max;
    double max_val;
    struct fann *ann = fann_create_from_file("fann_output_data.data");
    while (1) 
    {
        scanf("%d", &in1);
        if(in1 == -1) break;
        input[in1-1]=1;
        calc_out = fann_run(ann, input);
        printf("multiplication test -> ");
        max_val = calc_out[0];
        max=0;
        //printf("%f\n",(max_val*1000));
        for (i=0; i<20; i++)
        {
            if(max_val < *(calc_out+i))
            {
                max = i;
                max_val=*(calc_out+i);
            }
            //printf("%0.3f ", *(calc_out+i));
        }
        printf("\n%d\n\n", max+1);
        input[in1-1]=0;
    }
    fann_destroy(ann);
    return 0;
}
