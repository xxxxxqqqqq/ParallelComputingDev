#include "omp.h"
#include "stdio.h"
int main()
{
    #pragma omp parallel
    {
        // Gets the thread (we dont know which one) -> It runs for each thread available
        int ID = omp_get_thread_num();
        printf("hello(%d)", ID);
        printf("world(%d)\n", ID);
    }
}