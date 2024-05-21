#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;
float f(float x);
float f(float x)
{
	float a=x*x-4.0;
	return a;
}
int main()
{
	cout.precision(5);
	cout.setf(ios::fixed);
	float a,b,c,fa,fb,fc,e;
	cout<<"Enter the initial guesses\n a=";
	cin>>a;
	cout<<"b=";
	cin>>b;
	cout<<"\nenter the accuracy\n";
	cin>>e;
	int iter=0;
	if (f(a)*f(b)<0)
	{
	cout<<"Iter"<<setw(14)<<"a"<<setw(14)<<"b"<<setw(14)<<"c"<<setw(14)<<"f(c)"<<setw(14)<<"|a-b|"<<endl;
	cout<<"\n----------------------------------------------------------------------\n";
	while(fabs(a-b)>=e)
	{
		c=(a+b)/2.0;
		fa=f(a);
		fb=f(b);
		fc=f(c);
		iter++;
		cout<<iter<<setw(14)<<a<<setw(14)<<b<<setw(14)<<c<<setw(14)<<fc<<setw(14)<<fabs(a-b)<<endl;
		if(fc==0)
		{
			cout<<"Root of equation is "<<c<<endl;
			return 0;
		}
		if(fa*fc>0)
		{
			a=c;
		}
		else if(fa*fc<0)
		{
			b=c;
		}
	}
	
	cout<<"/nRoot is "<<c;
	return 0;
	}
	else
	cout<<"Enter the different initials";
}
