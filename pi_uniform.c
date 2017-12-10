#include "mpi.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning (disable : 4996)
#define nums_LIST_MAX      1000
#define nums_FILE          "input1.dat"

int main(int argc,char *argv[]) {
  int target = 1;
  sscanf(argv[1], "%d", &target);


    int i, n, myrank, nproc, done = 0;
    double h, x;
    int sum, total, realTotal;
        int tasks = 0;
        int startAt = 0;
        int stopAt = 0;


/*
 *  Read the .dat file to the array nums.
 */
      int nums[nums_LIST_MAX];
    	int count = 0;
    	int j = 0;

    	FILE *file;
    	file = fopen(nums_FILE, "r");
    	if (!file)
    	{
    		perror("Error opening file");
    		return -1;
    	}

    	memset(nums, 0, sizeof(nums));
    	while (!feof(file)               /* Check for the end of file*/
    		&& (count < nums_LIST_MAX)) /* To avoid memory corruption */
    	{
    		fscanf(file, "%d", &(nums[count++]));
    	}
    	fclose(file);


/*
 *  MPI caculation
 */
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&nproc);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    n = 1000;
        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
        if (n == 0)
            done = 1;
        else
        {
          if(myrank == 0)
          {
            printf("number to find is %d\n", target);
          }
          else
          {
            //get how many tasks each processors does
            tasks = n / (nproc-1);
            //calculate where to start and stop at
            startAt = ((myrank-1) * tasks) + 1;
            stopAt = myrank * tasks;

            h = 1.0 / (double) n;
            sum = 0;
                        //printf("This processor %d is doing %d jobs and starts at %d and ends at %d\n",myrank, tasks, startAt, stopAt );
                        for (i = startAt; i <= stopAt; i++)
                        {
                                if(nums[i] == target)
                                {
                                  sum++;
                                }
                        }

            printf("My id is %d and the frequency of %d is %d\n", myrank, target, sum);
          }
          MPI_Reduce(&sum, &realTotal, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
          if(myrank == 0){
              printf("-------------------------------\n");
              printf("The total frequency of %d is %d\n",target, realTotal);
          }
        }

    MPI_Finalize();
    return 0;
}
