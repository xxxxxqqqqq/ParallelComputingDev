// Here is a simple example which is intentionally created wrong to fix it and understand why it is wrong.
// Each time the program runs, you get a wrong answer and you get a different wrong answer -> Race condition
// Threads are screwing with each other and we need to fix it. So we need to debug this to fix it but how to debug an OPENMP program?
// You need to have a parallel debugger for that.

// 1. In this code, since we write this for loop "for(i=0; i<NPOINTS; i++)" under the  "pragma" then
//    "i" variable is automatically taken as private because pragma omp parallel for handle it. However,
//    it is not valid for variable "j". -> First fix -> we need to say that "j" is private.

// 2. We defined "c" as private which means inside parallel loop, it is taken as uninitialized but we initialize
//    "c" inside anyway with the formula. But, we also defined "eps" as private which normally has a initial global value.
//    Since, we made "eps" as private, we cannot get eps=1.0e-5 as an initialized value inside parallel region. 
//    -> Second fix -> Inside, we need to make "eps" "firstprivate" so we can use eps=1.0e-5 inside parallel region.

// 3. The testpoint function is defined as void and called with no inputs. But then within the testpoing function
//    which is inside parallel region, each thread will use the global copy "c" which is not a good idea. Because, one
//    of the important things in parallel programming is that you tend to not use global scopes for each thread. So:
//    -> Third  fix -> Lets change the function declaration from void input to struct d_complex type input

// 4. Within the testpoint function, there is a variable called "numoutside" which will be needed later outside
//    the parallel region. We are incrementing that numoutside but we need to make it one at a time to protect numoutside
//    Otherwise, the threads are gonna screw the numoutside and lead to wrong answer. So,
//    -> Fourth fix -> Lets protect the numoutside with "omp critical" or "omp atomic"

// ALL the fixes are handled inside the fixed version of this program. Check that

#include "omp.h"
#include "stdio.h"

#define NPOINTS 1000
#define MXITR 1000

void testpoint(void);

struct d_complex
{
    double r;
    double i;
};

struct d_complex c;
int numoutside = 0;

int main()
{
    int i;
    int j;
    double area;
    double error;
    double eps = 1.0e-5;

    #pragma omp parallel for default(shared) private(c, eps)
        for(i=0; i<NPOINTS; i++)
        {
            for(j=0; j<NPOINTS; j++)
            {
                c.r = -2.0 + 2.5*(double)(i)/(double)(NPOINTS)+eps;
                c.i = 1.125*(double)(j)/(double)(NPOINTS)+eps;
                testpoint();
            }
        }
    area = 2.0*2.5*1.125*(double)(NPOINTS*NPOINTS-numoutside)/(double)(NPOINTS*NPOINTS);
    printf("The area is: %f \n", area);
    error = area/(double)NPOINTS;
    printf("The error is: %f \n", error);
}

void testpoint(void)
{
    struct d_complex z;
    int iter;
    double temp;

    z = c;
    for(iter=0; iter<MXITR; iter++)
    {
        temp = (z.r*z.r)-(z.i*z.i)+c.r;
        z.i = z.r*z.i*2+c.i;
        z.r = temp;
        if ((z.r*z.r+z.i*z.i) > 4.0)
        {
            numoutside++;
            break;
        }
    }
}
