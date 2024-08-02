#include<mpi.h>
#include <stdio.h>

void main(int argc, char** argv)
{
    int myrank, nprocs;
    int a[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int i;
    int sum = 0, global_sum = 0;
    
MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
if(myrank==0){
for (i=0; i < 3; i++)
{sum+=a[i];
}

for(i = 1; i < nprocs;i++){
int temp = 0;
MPI_Recv(&temp, 1, MPI_INT, i, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
global_sum = global_sum + temp;
}
global_sum = global_sum + sum;
printf("global_sum is %d = \n", global_sum);
}

if(myrank==1){
for (i=3; i < 6; i++)
{sum+=a[i];
}
MPI_Send(&sum, 1, MPI_INT,0, 0,MPI_COMM_WORLD);
}


if(myrank==2){
for (i=6; i < 9; i++)
{sum+=a[i];
}
MPI_Send(&sum, 1, MPI_INT,0, 0,MPI_COMM_WORLD);
}

if(myrank==3){
for (i=9; i < 12; i++)
{sum+=a[i];
}
MPI_Send(&sum, 1, MPI_INT,0, 0,MPI_COMM_WORLD);
}

printf("sum from process %d is this %d\n",myrank,sum);
MPI_Finalize();

};

