// Simple Example solving a basic numerical integration problem
#include "omp.h"
#include "stdio.h"

static long num_steps = 100000;
double step;

// This is solving -> f(x) = Integral(from 0 to 1) 4.0/(1+x^2) dx -> The answer should be "pi"
int main()
{
    int i;
    double x = 0.0;
    double pi = 0.0;
    double sum = 0.0;

    step = 1.0/(double) num_steps;

    for(i=0; i<num_steps; i++)
    {
        x = (i + 0.5)*step;
        sum = sum + 4.0/(1.0+x*x);
    }
    pi = step*sum;
    printf("The value is: %f \n", pi);
}