// Simple OPENMP Example solving a basic numerical integration using loop constructs
// Much easier compared to SPMD.
// Now there is no more cyclic distributions or thread IDs etc. 
// Now there is a loop construct, using reduction method on a variable with loop carry dependency.
// In this example, we dont use any schedule method which means we are saying that we are happy with what the compiler chooses
// If you wanna use different schedule methods just to see which one performs better for this application, simply add schedule keyword to your paralel program
// Until now, all the other methods we learned was for us to understand what was happening in the lower level.

#include "omp.h"
#include "stdio.h"

static long num_steps = 100000000;
double step;
double time_start;
double time_end;

// This is solving -> f(x) = Integral(from 0 to 1) 4.0/(1+x^2) dx -> The answer should be "pi"
int main()
{
    int i;
    double x = 0.0;
    double pi = 0.0;
    double sum = 0.0;

    step = 1.0/(double) num_steps;

    // Requesting the number of threads given
    omp_set_num_threads(4);

    time_start = omp_get_wtime();
    #pragma omp parallel
    {
        double x;
        #pragma omp for reduction(+:sum)
            for(i=0; i<num_steps; i++)
            {
                x = (i + 0.5)*step;
                sum = sum + 4.0/(1.0+x*x);
            }
    }
    time_end = omp_get_wtime();
    printf("%f seconds have elapsed.\n", time_end-time_start);

    pi = step*sum;
    printf("The value is: %f \n", pi);
}