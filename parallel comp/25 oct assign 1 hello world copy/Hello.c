#include <mpi.h>
#include <stdio.h>

void main(int argc, char **argv)
{

    int myrank, nprocs;
    MPI_Init(&argc, &argv);

    int d = 2;
    int periods[2] = {1, 1};
    int dims[2] = {3, 2};
    int reorder = 1;
    int coords[2] = {0, 0};
    int newrank;
    int left, right, up, down;
    int shift_change = 1;
    int change = 0;

    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    //    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    MPI_Comm cart_topo;
    MPI_Cart_create(MPI_COMM_WORLD, d, dims, periods, reorder, &cart_topo);
    //    MPI_Cart_create(MPI_COMM_WORLD, int d, int(2, 3), int(1, 1), 1, &cart_topo);

    MPI_Comm_rank(cart_topo, &newrank);

    MPI_Cart_coords(cart_topo, newrank, d, coords);
    printf("rank %d coords: (%d, %d)\n", newrank, coords[0], coords[1]);

    MPI_Cart_shift(cart_topo, 0, shift_change, &left, &right);
    printf("rank %d up: %d down: %d\n", newrank, left, right);

    //    printf("I Am printing on %d out of %d \n", myrank, nprocs);
    //  printf("Hello world \n ");
    MPI_Finalize();
};