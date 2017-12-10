#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
        int rc;
        rc = MPI_Init(&argc, &argv);
        if (rc != MPI_SUCCESS)
        {
                printf("Error starting MPI program. Termiaating.\n");
                MPI_Abort(MPI_COMM_WORLD, rc);
        }

        int myrank, nproc, i, number;
        MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
        MPI_Comm_size(MPI_COMM_WORLD, &nproc);

        if (myrank != 0)
        {
                MPI_Recv(&number, 1, MPI_INT, myrank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                printf("Process %d received number %d from process %d\n", myrank, number, myrank-1);
        }
        else
        {
                number = 10;    //it will be set only at P0
                printf("I am process %d and number is set to %d\n", myrank, number);
        }

        MPI_Send(&number, 1, MPI_INT, (myrank+1)%nproc, 0, MPI_COMM_WORLD);

        if (myrank == 0)
        {
                MPI_Recv(&number, 1, MPI_INT, nproc - 1, 0, MPI_COMM_WORLD,
                MPI_STATUS_IGNORE);
                printf("Process %d received number %d from process %d\n", myrank, number, nproc-1);
        }

        MPI_Finalize();
        return 0;
}
