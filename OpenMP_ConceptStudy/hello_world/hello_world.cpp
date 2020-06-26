// Simple OpenMP Example with Hello World
#include "omp.h"
#include "stdio.h"
int main()
{
    // It runs for each thread available
    #pragma omp parallel
    {
        // Gets the thread ID or rank (we dont know which one -> pragma handles it)
        int ID = omp_get_thread_num();
        printf("hello(%d)", ID);
        printf("world(%d)\n", ID);
    }
}