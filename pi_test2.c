#include "mpi.h"
#include <stdio.h>
#include <math.h>
double f(a)
double a; {
    return (4.0 / (1.0 + a*a));
}
int main(int argc,char *argv[]) {
    int i, n, myrank, nproc, done = 0;
    double PI25DT = 3.141592653589793238462643;
    double mypi, pi, h, sum, x, bufferzone;
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
        //send n from 0 to all other processes
        for(i = 1; i < nproc; i++){
                if(myrank == 0)
                        MPI_Send(&n, 1, MPI_INT, i, i, MPI_COMM_WORLD);
        }
        //recieve n on all other processors from processor 0
        if (myrank != 0)
                MPI_Recv(&n, 1, MPI_INT, 0, myrank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("My rank is %d, and my value for n is %d\n", myrank, n);

        //MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
        if (n == 0)
            done = 1;
        else
        {
            h = 1.0 / (double) n;
            sum = 0.0;
            for (i = myrank + 1; i <= n; i += nproc)
            {
                x = h * ((double)i - 0.5);
                sum += f(x);
            }
            mypi = h * sum;
                //printf("My rank is %d and mypi is %f and pi is %f\n", myrank, mypi, pi);
            //MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
                //send mypi to processor 0 from all other processors
                if (myrank != 0)
                        MPI_Send(&mypi, 1, MPI_DOUBLE, 0, nproc+myrank, MPI_COMM_WORLD);

            if (myrank == 0){
//loop through and recieve from all other processors their mypi value and store it in a buffer, if not a different variable it deadlocks
                for(i = 1; i < nproc; i++){
                                if(i == 1)
                                        pi = mypi;
                                //printf("processor %d recieving on channel %d from processor %d \n", myrank, nproc+i, i);
                                MPI_Recv(&bufferzone, 1, MPI_DOUBLE, i, nproc+i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                                //printf("Adding %f to %f\n", bufferzone, pi);
                                pi += bufferzone;                        }

                printf("\npi is approximately %.16f, Error is %.16f\n\n", pi, fabs(pi
- PI25DT));
}
        }
    }
    MPI_Finalize();
    return 0;
}
