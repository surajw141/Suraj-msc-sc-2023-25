#include "MyMPI.h"

// Reads a column-striped matrix from a file
void read_col_striped_matrix(const char *filename, void ***matrix, void **storage, MPI_Datatype datatype, int *rows, int *cols, MPI_Comm comm) {
    int id, p;
    MPI_Comm_rank(comm, &id);
    MPI_Comm_size(comm, &p);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open matrix file");
        MPI_Abort(comm, 1);
    }

    // Read matrix dimensions
    fscanf(file, "%d %d", rows, cols);

    // Allocate memory for the matrix
    *matrix = (void **)malloc(*rows * sizeof(void *));
    *storage = (dtype *)malloc(*rows * (*cols) * sizeof(dtype));

    if (*matrix == NULL || *storage == NULL) {
        perror("Failed to allocate memory");
        MPI_Abort(comm, 1);
    }

    // Scatter matrix columns to different processes
    int col_per_proc = (*cols + p - 1) / p; // Columns per process, considering rounding up

    for (int i = 0; i < *rows; i++) {
        (*matrix)[i] = (dtype *)*storage + i * col_per_proc;
    }

    // Read matrix data
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < col_per_proc; j++) {
            if (i < *cols) {
                fscanf(file, "%lf", &((dtype *)*storage)[i * col_per_proc + j]);
            }
        }
    }

    fclose(file);
}

// Prints a column-striped matrix
void print_col_striped_matrix(void **matrix, MPI_Datatype datatype, int rows, int cols, MPI_Comm comm) {
    int id;
    MPI_Comm_rank(comm, &id);

    if (id == 0) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("%lf ", ((dtype *)matrix[i])[j]);
            }
            printf("\n");
        }
    }
}

// Reads a block vector from a file
void read_block_vector(const char *filename, void **vector, MPI_Datatype datatype, int *length, MPI_Comm comm) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open vector file");
        MPI_Abort(comm, 1);
    }

    fscanf(file, "%d", length);
    *vector = (dtype *)malloc(*length * sizeof(dtype));

    if (*vector == NULL) {
        perror("Failed to allocate memory");
        MPI_Abort(comm, 1);
    }

    for (int i = 0; i < *length; i++) {
        fscanf(file, "%lf", &((dtype *)*vector)[i]);
    }

    fclose(file);
}

// Prints a block vector
void print_block_vector(void *vector, MPI_Datatype datatype, int length, MPI_Comm comm) {
    int id;
    MPI_Comm_rank(comm, &id);

    if (id == 0) {
        for (int i = 0; i < length; i++) {
            printf("%lf ", ((dtype *)vector)[i]);
        }
        printf("\n");
    }
}

// Memory allocation wrapper for MPI
void* my_malloc(int id, size_t size) {
    return malloc(size);
}

// Creates mixed transfer arrays for MPI_Alltoallv
void create_mixed_xfer_arrays(int id, int p, int n, int **cnt, int **disp) {
    *cnt = (int *)malloc(p * sizeof(int));
    *disp = (int *)malloc(p * sizeof(int));

    if (*cnt == NULL || *disp == NULL) {
        perror("Failed to allocate memory for mixed transfer arrays");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int block_size = (n + p - 1) / p; // Block size per processor

    for (int i = 0; i < p; i++) {
        (*cnt)[i] = block_size;
        (*disp)[i] = i * block_size;
    }
}

// Creates uniform transfer arrays for MPI_Alltoallv
void create_uniform_xfer_arrays(int id, int p, int n, int **cnt, int **disp) {
    *cnt = (int *)malloc(p * sizeof(int));
    *disp = (int *)malloc(p * sizeof(int));

    if (*cnt == NULL || *disp == NULL) {
        perror("Failed to allocate memory for uniform transfer arrays");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int block_size = (n + p - 1) / p; // Block size per processor

    for (int i = 0; i < p; i++) {
        (*cnt)[i] = block_size;
        (*disp)[i] = i * block_size;
    }
}

// Calculate block size
int BLOCK_SIZE(int id, int p, int n) {
    return (n + p - 1) / p; // Block size per processor
}
