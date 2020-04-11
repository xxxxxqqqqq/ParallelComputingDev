// Simple OPENMP Example solving a basic numerical integration using given number of threads
// SPMD algorithm strategy is used in this example.
// In the loop iterations, the method called cyclic distribution/iteration for loop iterations is used
// Here we are using "critical" method for syncronizing our program to avoid false sharing (more elegant than padding)
// Padding was not elegant since it was requiring us to know about our L1 cache line size
// Remember to use as small as possible inside the critical. We dont want to utilize "critical for many operations"

#include "omp.h"
#include "stdio.h"

static long num_steps = 100000000;
double step;
#define NUM_THREADS 4

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
        #pragma omp critical
            pi = pi + (sum*step);
        
    }
    time_end = omp_get_wtime();
    printf("%f seconds have elapsed.\n", time_end-time_start);
    printf("The value is: %f \n", pi);
}