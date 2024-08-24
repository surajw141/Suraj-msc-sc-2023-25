#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <mpi.h>
#include <fstream>

using namespace std;

// Function prototypes
void timestamp();
void read_matrix(const char* filename, double*& matrix, int& m, int& n);
void read_vector(const char* filename, double*& vector, int& n);

int main(int argc, char* argv[]) {
    double* a = nullptr;
    double* a_row = nullptr;
    double ans;
    double* b = nullptr;
    double* x = nullptr;
    int dest;
    int dummy;
    int i;
    int id;
    int ierr;
    int j;
    int j_one;
    int k;
    int m;
    int n;
    int num_rows;
    int num_workers;
    int p;
    double r8_pi = 3.141592653589793;
    MPI_Status status;
    int tag;
    int tag_done;

    // Initialize MPI
    ierr = MPI_Init(&argc, &argv);
    if (ierr != 0) {
        cout << "\nMATVEC:\n";
        cout << "  MPI_Init returned ierr = " << ierr << "\n";
        exit(1);
    }

    // Get this processor's ID
    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &id);

    // Get the number of processors
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (id == 0) {
        timestamp();
        cout << "\nMATVEC - Master process:\n";
        cout << "  C++ version\n";
        cout << "  An MPI example program to compute\n";
        cout << "  a matrix-vector product b = A * x.\n";
        cout << "\n";
        cout << "  Compiled on " << __DATE__ " at " << __TIME__ << "\n";
        cout << "\n";
        cout << "  The number of processes is " << p << ".\n";
    }
    cout << "\nProcess " << id << " is active.\n";

    // Read matrix and vector from files
    if (id == 0) {
        read_matrix("matrix.txt", a, m, n);
        read_vector("vector.txt", x, n);

        b = new double[m];
        j_one = 17; // As specified in the problem

        // Initialize x with known values
        for (i = 0; i < n; i++) {
            x[i] = sqrt(2.0 / (double)(n + 1)) *
                   sin((double)((i + 1) * j_one) * r8_pi / (double)(n + 1));
        }

        cout << "\nMATVEC - Master process:\n";
        cout << "  Vector x\n";
        cout << "\n";
        for (i = 0; i < n; i++) {
            cout << setw(6) << i << "  "
                 << setw(10) << x[i] << "\n";
        }
    }

    // Broadcast vector x to all processes
    ierr = MPI_Bcast(x, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Worker processes set aside room for one row of A, and for the vector x
    if (id != 0) {
        a_row = new double[n];
        x = new double[n];
    }

    // Process 0 sends one row of A to all the other processes
    if (id == 0) {
        num_rows = 0;

        for (i = 1; i <= p - 1; i++) {
            dest = i;
            tag = num_rows;
            k = num_rows * n;

            ierr = MPI_Send(a + k, n, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);

            num_rows = num_rows + 1;
        }

        num_workers = p - 1;

        for (;;) {
            ierr = MPI_Recv(&ans, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            tag = status.MPI_TAG;
            b[tag] = ans;

            if (num_rows < m) {
                num_rows = num_rows + 1;
                dest = status.MPI_SOURCE;
                tag = num_rows;
                k = num_rows * n;

                ierr = MPI_Send(a + k, n, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
            } else {
                num_workers = num_workers - 1;
                dummy = 0;
                dest = status.MPI_SOURCE;
                tag = tag_done;

                ierr = MPI_Send(&dummy, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);

                if (num_workers == 0) {
                    cout << "  Process " << id << " shutting down.\n";
                    break;
                }
            }
        }

        delete[] a;
        delete[] x;
    } else {
        // Each worker process repeatedly receives rows of A (with TAG indicating which row it is)
        for (;;) {
            ierr = MPI_Recv(a_row, n, MPI_DOUBLE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            tag = status.MPI_TAG;

            if (tag == tag_done) {
                cout << "  Process " << id << " shutting down.\n";
                break;
            }

            ans = 0.0;
            for (i = 0; i < n; i++) {
                ans += a_row[i] * x[i];
            }

            ierr = MPI_Send(&ans, 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD);
        }

        delete[] a_row;
        delete[] x;
    }

    // Print out the answer
    if (id == 0) {
        cout << "\nMATVEC - Master process:\n";
        cout << "  Product vector b = A * x\n";
        cout << "  (Should be zero, except for a 1 in entry " << j_one - 1 << "\n";
        cout << "\n";
        for (i = 0; i < m; i++) {
            cout << setw(4) << i << "  "
                 << setw(10) << b[i] << "\n";
        }

        delete[] b;
    }

    // Terminate MPI
    MPI_Finalize();

    // Terminate
    if (id == 0) {
        cout << "\nMATVEC - Master process:\n";
        cout << "  Normal end of execution.\n";
        cout << "\n";
        timestamp();
    }

    return 0;
}

//****************************************************************************80
// Function to read matrix from file
void read_matrix(const char* filename, double*& matrix, int& m, int& n) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error opening matrix file." << endl;
        exit(1);
    }

    infile >> m >> n;
    matrix = new double[m * n];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            infile >> matrix[i * n + j];
        }
    }
    infile.close();
}

//****************************************************************************80
// Function to read vector from file
void read_vector(const char* filename, double*& vector, int& n) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error opening vector file." << endl;
        exit(1);
    }

    infile >> n;
    vector = new double[n];
    for (int i = 0; i < n; ++i) {
        infile >> vector[i];
    }
    infile.close();
}

//****************************************************************************80
// Function to print current date and time as a timestamp
void timestamp() {
#define TIME_SIZE 40
    static char time_buffer[TIME_SIZE];
    const struct std::tm* tm_ptr;
    std::time_t now;

    now = std::time(NULL);
    tm_ptr = std::localtime(&now);

    std::strftime(time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm_ptr);

    std::cout << time_buffer << "\n";
#undef TIME_SIZE
}
