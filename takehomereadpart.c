#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
  int myid, nprocs;
  int *array;
  int size, i;
  int ierr;
  FILE *fp;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

  if(myid ==0)
    {
     /*MPI_File_open (MPI_COMM_WORLD, "input1.dat", MPI_MODE_RDONLY, MPI_INFO_NULL, &fp);*/



      /* Get the size of the file */
      /*MPI_File_get_size(fp, &size);*/
      /* Calculate how many elements that is */
      /*filesize = filesize/sizeof(char);*/

      /* Calculate how many elements each processor gets */
      /*bufsize = filesize/np;*/
      /* Allocate the buffer to read to, one extra for terminating null char */
      /*buf = (char *) malloc((bufsize+1)*sizeof(char));*/


      /* Set the file view */
      /*MPI_File_set_view(fp, myid*bufsize*sizeof(char), MPI_CHAR, MPI_CHAR,"native",MPI_INFO_NULL);*/


      /*MPI_File_get_size(myfile, &filesize);*/
      /*filesize = filesize/sizeof(char);*/
      fp = fopen("input1.dat", "r");
      MPI_Comm_size(MPI_COMM_WORLD, &size);
      /*int MPI_File_get_size(fp, size);*/
      fscanf(fp, "%d", &size);
    }

  /* MPI_Bcast(void *buffer,
               int count,
               MPI_Datatype datatype,
               int root,
               MPI_Comm comm) */
  MPI_Bcast(&size,1, MPI_INT, 0, MPI_COMM_WORLD);
  array = (int *) malloc(size* sizeof(int));

  if(myid ==0)
    {
      for(i = 0; i < size-1; i++)
        {
          fscanf(fp, "%d", &array[i]);
          printf("%d     =      %d\n", i, array[i]);
        }
    }
  MPI_Bcast(array, size, MPI_INT, 0, MPI_COMM_WORLD);

  MPI_Finalize();
}


