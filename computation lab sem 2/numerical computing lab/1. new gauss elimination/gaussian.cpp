#include<iostream>
#include<iomanip>
#include<cmath>
#define N 4
using namespace std;
int main()
{
	float Matrix[N][N+1],x[N];	
	float temp,s;
	int i,j,k;

	cout<<"Enter Elements of "<<N<<" Rows & "<<N+1<<" Columns\n";
	cout<<fixed;

	for(i=0; i<N; i++)
	{
		cout<<"\tEnter Row  "<<i+1<<" & Press Enter\n";
		for(j=0; j<N+1; j++)
		cin>>Matrix[i][j];
	}
	for(j=0; j<N-1; j++)
	{
		for(i=j+1; i<N; i++)
		{
			temp=Matrix[i][j]/Matrix[j][j];

			for(k=0; k<N+1; k++)
				Matrix[i][k]-=Matrix[j][k]*temp;
		}
	}	
	cout<<"\n ---------------------------------\n";
	cout<<"\n Upper Triangular Matrix is:\n";
	for(i=0; i<N; i++)
	{
		for(j=0; j<N+1; j++)
		cout<<setw(8)<<setprecision(4)<<Matrix[i][j];
		cout<<endl;
	}
	cout<<"\n ---------------------------------\n";

	for(i=N-1; i>=0; i--)
	{
		s=0;
		for(j=i+1; j<N; j++)
		s += Matrix[i][j]*x[j];
		x[i]=(Matrix[i][N]-s)/Matrix[i][i];
	}
	cout<<"\n The Solution is:\n";
	for(i=0; i<N; i++)
	 cout<<"x["<<setw(3)<<i+1<<"]="<<setw(7)<<setprecision(4)<<x[i]<<endl;
return 0;
}
