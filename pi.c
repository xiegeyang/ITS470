#include "mpi.h"
#include <stdio.h>
#include <math.h>

double f(a)
double a;
{
    return (4.0 / (1.0 + a*a));
}

int main(int argc,char *argv[])
{
    int i, n, myrank, nproc, done = 0;
    double PI25DT = 3.141592653589793238462643;
    double mypi, pi, h, sum, x;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&nproc);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);

    n = 0;
    while (!done)
    {
        if (myrank == 0)
        {
            printf("Enter the number of intervals: (0 quits)\n");
            scanf("%d",&n);
        }

        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
//	printf("I am process %d and value n is %d\n", myid, n);
        if (n == 0)
            done = 1;
        else
        {
            h   = 1.0 / (double) n;
            sum = 0.0;
            for (i = myrank + 1; i <= n; i += nproc)
            {
                x = h * ((double)i - 0.5);
                sum += f(x);
            }
            mypi = h * sum;

            MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

            if (myrank == 0)
                printf("\npi is approximately %.16f, Error is %.16f\n\n", pi, fabs(pi - PI25DT));
	}
    }

    MPI_Finalize();
    return 0;
}
