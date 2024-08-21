#include <bits/stdc++.h>
#include <mpi.h>
using namespace std;

double f_x(double x) {
    return sin(x); 
}

double* partition(int a, int b, int n) {
    double h = (double)(b - a) / n;
    double* A = new double[n + 1];
    A[0] = a;
    for (int i = 1; i <= n; i++) {
        A[i] = A[i - 1] + h; // size of A is n+1
    }
    return A;
}

double boolesInt(int a, int b, int n){
   double h = (double)(b - a) / n;
int k = n/4;
 double* A = partition(a, b, n);
int sum = 0 ;
for ( int i = 0 ; i < k ; i++){
sum = sum + (7*f_x(A[4*i]) + 32 * f_x(A[4*i+1]) + 12 * f_x(A[4*i+2]) + 32 * f_x(A[4*i + 3]) + 7 * f_x(A[4*i+4]));

}
return sum; 
}

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Define the domain of the function
    int a = 0, b = 1;
    int n = 100; // Number of partitions input
    double h = (double)(b - a) / n;

    int k = n/4;

   

    // Parallel implementation
    double local_ans = 0.0;
    if (rank == 0) 
	{

	 double* A = partition(a, b, n);
	for(int i=0;i<size;i++)
	{
		MPI_Send(&A[i*n/size],n/size+1,MPI_DOUBLE,i,0,MPI_COMM_WORLD);
	}	

        vector<double> f_xs;
        for (int i = 0; i <= n/size; i++)
	{  // Only use first 5 points
            f_xs.push_back(f_x(A[i]));
        }
		
	for(int i=0;i<k/size;i++)
        {local_ans = local_ans + (7 * f_xs[i] + 32 * f_xs[i+1] + 12 * f_xs[i+2] + 32 * f_xs[i+3] + 7 * f_xs[i+4]);}

        // Receive results from other processes
        for (int i = 1; i < size; i++) {
            double temp;
            MPI_Recv(&temp, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            local_ans += temp;
        }
        local_ans = ((2 * h) / 45) * local_ans;
        cout << endl << "Final result :: " << local_ans << endl;
        } 
       else 
	{
		double B[n/size+1];
		MPI_Recv(&B,n/size+1,MPI_DOUBLE,0,0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
         	vector<double> f_xs;
           	for (int i = 0; i <= n/size+1; i++)
		 {
              	  f_xs.push_back(f_x(B[i]));
           	 }

        	for(int i=0;i<k/size;i++)
        	{local_ans = local_ans + (7 * f_xs[i] + 32 * f_xs[i+1] + 12 * f_xs[i+2] + 32 * f_xs[i+3] + 7 * f_xs[i+4]);}
        	MPI_Send(&local_ans, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    //delete[] A; // Free allocated memory
    MPI_Finalize();
    return 0;
}
