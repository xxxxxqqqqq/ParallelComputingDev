// Simple OPENMP Example solving a basic numerical integration using given number of threads
// SPMD algorithm strategy is used in this example.
// In the loop iterations, the method called cyclic distribution/iteration for loop iterations is used
// False sharing is eliminated in this example with padding method.
// Here now we create a PAD and we always set to 0 in this example and with different ID.
// Via this way, we gurantee that each "sum" sits on different cache line which means we avoid false sharing.
#include "omp.h"
#include "stdio.h"

static long num_steps = 100000000;
double step;
#define NUM_THREADS 4
#define PAD 8 // assume 64 byte L1 cache line size

// This is solving -> f(x) = Integral(from 0 to 1) 4.0/(1+x^2) dx -> The answer should be "pi"
int main()
{
    int i;
    int nthreads;
    double pi = 0.0;
    double sum[NUM_THREADS][PAD];
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

        for(i=id, sum[id][0]=0.0; i<num_steps; i=i+nthrds)
        {
            x = (i + 0.5)*step;
            sum[id][0] = sum[id][0] + 4.0/(1.0+x*x);
        }
    }
    time_end = omp_get_wtime();
    printf("%f seconds have elapsed.\n", time_end-time_start);

    for(i=0, pi=0.0; i<nthreads; i++)
    {
        pi = pi + sum[i][0]*step;
    }
    printf("The value is: %f \n", pi);
}