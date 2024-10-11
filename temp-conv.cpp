#include<iostream>
using namespace std;

// create a class
class CelsiusToFahrenheit {
	// private data member
	private:
	float celsius;
	
	// public functions
	public:
	//getTemperature() function to get the tempreture
		void getTemperature() {
		cout << "Enter Temperature in celsius:";
		cin >> celsius;
		}
	double CToF() {
	float fahrenheit;
	fahrenheit = ((celsius * 9)/5) + 32;
	return fahrenheit;
	
}

int main()
{
cout << "shree \n";

	CelsiusToFahrenheit C;

	float temperature;

	C.getTemperature();
	
	temperature = C.CToF();
	
	cout << "Temperature in Fahrenheit :" << temperature;
	return 0;
}};