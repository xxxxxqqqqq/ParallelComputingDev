// Simple OPENMP Example solving a basic numerical integration using given number of threads
// SPMD algorithm strategy is used in this example.
// In the loop iterations, the method called cyclic distribution/iteration for loop iterations is used
// Here we are using "atomic" method just like "critical" but with potential utlization of special hardware constructs
// Remember to use as small as possible inside the atomic. Even smaller than "critical" (increments, decrements, etc)

#include "omp.h"
#include "stdio.h"

static long num_steps = 100000000;
double step;
#define NUM_THREADS 8

// This is solving -> f(x) = Integral(from 0 to 1) 4.0/(1+x^2) dx -> The answer should be "pi"
int main()
{
    int nthreads;
    double pi = 0.0;
    double time_start;
    double time_end;

    step = 1.0/(double) num_steps; 

    // Requesting the number of threads given
    omp_set_num_threads(NUM_THREADS);

    time_start = omp_get_wtime();
    #pragma omp parallel
    {
        int i;
        int id;
        int nthrds;
        double x;
        double sum;

        // Gets the thread ID or rank (we dont know which one -> pragma handles it)
        id = omp_get_thread_num();
        printf("ID: %d \n", id);

        // Gets the number of threads
        nthrds = omp_get_num_threads();
        printf("Number of threads: %d \n", nthrds);

        if (id == 0)
        {
            nthreads = nthrds;
        }

        for(i=id, sum=0.0; i<num_steps; i=i+nthrds)
        {
            x = (i + 0.5)*step;
            sum = sum + 4.0/(1.0+x*x);
        }
        sum = sum*step;

        #pragma omp atomic
            pi = pi + sum;
        
    }
    time_end = omp_get_wtime();
    printf("%f seconds have elapsed.\n", time_end-time_start);
    printf("The value is: %f \n", pi);
}