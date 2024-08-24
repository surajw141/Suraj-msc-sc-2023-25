#ifndef MYMPI_H
#define MYMPI_H

#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

typedef double dtype;
#define mpitype MPI_DOUBLE

// Macro for block size
#define BLOCK_SIZE(id, p, n) ((n + p - 1) / p)

// Function prototypes
void read_col_striped_matrix(const char *filename, void ***matrix, void **storage, MPI_Datatype datatype, int *rows, int *cols, MPI_Comm comm);
void print_col_striped_matrix(void **matrix, MPI_Datatype datatype, int rows, int cols, MPI_Comm comm);
void read_block_vector(const char *filename, void **vector, MPI_Datatype datatype, int *length, MPI_Comm comm);
void print_block_vector(void *vector, MPI_Datatype datatype, int length, MPI_Comm comm);
void* my_malloc(int id, size_t size);
void create_mixed_xfer_arrays(int id, int p, int n, int **cnt, int **disp);
void create_uniform_xfer_arrays(int id, int p, int n, int **cnt, int **disp);

#endif // MYMPI_H
