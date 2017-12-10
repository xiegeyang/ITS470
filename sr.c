#include "mpi.h"
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

	int myrank, nproc, number, numb;

	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);

	if (myrank == 0)
	{
		printf("My rank is %d\n", myrank);
		number = -1;
		printf("Sending: P0 sends number %d to P1\n", number);
		MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	} else if (myrank == 1)
	{
		printf("My rank is %d\n", myrank);
		MPI_Recv(&numb, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Receiving: P1 receives number %d from P0\n", numb);
	}

	MPI_Finalize();
}
