// This is the fixed version of mandel program -> Check the wrong version to see the problems

#include "omp.h"
#include "stdio.h"

#define NPOINTS 1000
#define MXITR 1000

void testpoint(struct d_complex);

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

    #pragma omp parallel for default(shared) private(c, j) firstprivate(eps)
        for(i=0; i<NPOINTS; i++)
        {
            for(j=0; j<NPOINTS; j++)
            {
                c.r = -2.0 + 2.5*(double)(i)/(double)(NPOINTS)+eps;
                c.i = 1.125*(double)(j)/(double)(NPOINTS)+eps;
                testpoint(c);
            }
        }
    area = 2.0*2.5*1.125*(double)(NPOINTS*NPOINTS-numoutside)/(double)(NPOINTS*NPOINTS);
    printf("The area is: %f \n", area);
    error = area/(double)NPOINTS;
    printf("The error is: %f \n", error);
}

void testpoint(struct d_complex c)
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
            #pragma omp atomic
                numoutside++;
                break;
        }
    }
}
