#include <stdio.h>
#include <assert.h>
#include <mpi.h>
#include <stdlib.h>

#define MAX_ITERATIONS 100
#define N 4  // Define the size of the matrix and vectors

double Distance(double *X_Old, double *X_New, int n_size);

int main(int argc, char** argv) {

    /* .......Variables Initialisation ......*/
    MPI_Status status;
    int NoofRows, NoofCols;
    int Numprocs, MyRank, Root = 0;
    int irow, icol, index, Iteration, GlobalRowNo;

    double Mat_a[N][N];
    double Vec_b[N];
    double x_Old[N], x_New[N];
    double ARecv[N / Numprocs][N];
    double BRecv[N / Numprocs];
    double Bloc_X[N / Numprocs];

    FILE *fp;

    /* ........MPI Initialisation .......*/
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &MyRank);
    MPI_Comm_size(MPI_COMM_WORLD, &Numprocs);

    /* .......Read the Input file ......*/
    if (MyRank == Root) {
        if ((fp = fopen("mdatjac.inp", "r")) == NULL) {
            printf("Can't open input matrix file");
            exit(-1);
        }
        fscanf(fp, "%d %d", &NoofRows, &NoofCols);
        if (NoofRows != N || NoofCols != N) {
            printf("Matrix size in file does not match predefined N\n");
            exit(-1);
        }

        /* Read data */
        for (irow = 0; irow < N; irow++) {
            for (icol = 0; icol < N; icol++)
                fscanf(fp, "%lf", &Mat_a[irow][icol]);
        }
        fclose(fp);

        if ((fp = fopen("vdatjac.inp", "r")) == NULL) {
            printf("Can't open input vector file");
            exit(-1);
        }

        fscanf(fp, "%d", &NoofRows);
        if (NoofRows != N) {
            printf("Vector size in file does not match predefined N\n");
            exit(-1);
        }

        for (irow = 0; irow < N; irow++)
            fscanf(fp, "%lf", &Vec_b[irow]);
        fclose(fp);

        /* Convert Mat_a into 1-D array Input_A */
        double Input_A[N * N];
        index = 0;
        for (irow = 0; irow < N; irow++)
            for (icol = 0; icol < N; icol++)
                Input_A[index++] = Mat_a[irow][icol];
    }

    /* Broadcast matrix and vector size (N) and verify matrix properties */
    MPI_Bcast(&NoofRows, 1, MPI_INT, Root, MPI_COMM_WORLD);
    MPI_Bcast(&NoofCols, 1, MPI_INT, Root, MPI_COMM_WORLD);

    if (NoofRows != NoofCols || NoofRows != N) {
        MPI_Finalize();
        if (MyRank == 0) {
            printf("Input Matrix Should Be Square Matrix and match predefined N ..... \n");
        }
        exit(-1);
    }

    /* Broad cast the size of the matrix to all ....*/
    // No need to broadcast N because it's already consistent across all processes

    if (N % Numprocs != 0) {
        MPI_Finalize();
        if (MyRank == 0) {
            printf("Matrix Can not be Striped Evenly ..... \n");
        }
        exit(-1);
    }

    int NoofRows_Bloc = N / Numprocs;

    /* Scatter the Input Data to all processes */
    MPI_Scatter(Mat_a, NoofRows_Bloc * N, MPI_DOUBLE, ARecv, NoofRows_Bloc * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(Vec_b, NoofRows_Bloc, MPI_DOUBLE, BRecv, NoofRows_Bloc, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    /* Initialize X[i] = B[i] */
    for (irow = 0; irow < NoofRows_Bloc; irow++)
        Bloc_X[irow] = BRecv[irow];

    MPI_Allgather(Bloc_X, NoofRows_Bloc, MPI_DOUBLE, x_New, NoofRows_Bloc, MPI_DOUBLE, MPI_COMM_WORLD);

    Iteration = 0;
    do {
        for (irow = 0; irow < N; irow++)
            x_Old[irow] = x_New[irow];

        for (irow = 0; irow < NoofRows_Bloc; irow++) {
            GlobalRowNo = (MyRank * NoofRows_Bloc) + irow;
            Bloc_X[irow] = BRecv[irow];
            index = irow * N;

            for (icol = 0; icol < GlobalRowNo; icol++) {
                Bloc_X[irow] -= x_Old[icol] * ARecv[irow][icol];
            }
            for (icol = GlobalRowNo + 1; icol < N; icol++) {
                Bloc_X[irow] -= x_Old[icol] * ARecv[irow][icol];
            }
            Bloc_X[irow] = Bloc_X[irow] / ARecv[irow][GlobalRowNo];
        }

        MPI_Allgather(Bloc_X, NoofRows_Bloc, MPI_DOUBLE, x_New, NoofRows_Bloc, MPI_DOUBLE, MPI_COMM_WORLD);
        Iteration++;
    } while ((Iteration < MAX_ITERATIONS) && (Distance(x_Old, x_New, N) >= 1.0E-24));

    /* .......Output vector .....*/
    if (MyRank == 0) {
        printf("\n");
        printf(" ------------------------------------------- \n");
        printf("Results of Jacobi Method on processor %d: \n", MyRank);
        printf("\n");

        printf("Matrix Input_A \n");
        printf("\n");
        for (irow = 0; irow < N; irow++) {
            for (icol = 0; icol < N; icol++)
                printf("%.3lf  ", Mat_a[irow][icol]);
            printf("\n");
        }
        printf("\n");
        printf("Matrix Input_B \n");
        printf("\n");
        for (irow = 0; irow < N; irow++) {
            printf("%.3lf\n", Vec_b[irow]);
        }
        printf("\n");
        printf("Solution vector \n");
        printf("Number of iterations = %d\n", Iteration);
        printf("\n");
        for (irow = 0; irow < N; irow++)
            printf("%.12lf\n", x_New[irow]);
        printf(" --------------------------------------------------- \n");
    }

    MPI_Finalize();
}

double Distance(double *X_Old, double *X_New, int n_size) {
    int index;
    double Sum;

    Sum = 0.0;
    for (index = 0; index < n_size; index++)
        Sum += (X_New[index] - X_Old[index]) * (X_New[index] - X_Old[index]);

    return(Sum);
}
