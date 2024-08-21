#include <mpi.h>
#include <stdio.h>

void main(int argc, char** argv)
{
    int myrank, nprocs;
    int A[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int sum = 0, global_sum = 0;
    
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	int n = 12/nprocs;
	int offset;
	int B[n];

if(myrank==0)
{
	for (int i=1;i<nprocs;i++)
	{
		offset = n*i;
		MPI_Send(&A[offset],n,MPI_INT, i, 0, MPI_COMM_WORLD);
	}
	for (int i=0; i < n; i++)
		{
			sum+=A[i];
		}
         
	global_sum = sum;
	for(int i = 1; i < nprocs;i++)
	{
		int temp = 0;
		MPI_Recv(&temp, 1, MPI_INT, i, 1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		global_sum = global_sum + temp;
	}
	printf("global_sum is = %d \n", global_sum);
}

else
{	
	MPI_Recv(&B, n,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	for(int i=0;i<n;i++)
	{
		sum = sum + B[i];
	}
	MPI_Send(&sum,1,MPI_INT,0,1,MPI_COMM_WORLD);
}


printf("sum from process %d is this %d\n",myrank,sum);
MPI_Finalize();

};

