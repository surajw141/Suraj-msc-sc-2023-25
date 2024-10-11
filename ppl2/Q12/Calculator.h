#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>



class Calculator{

	public:
		double calculate(double num1, char op, double num2);
	private:
		double add(double a, double b);
		double subtract(double a, double b);
		double multiply(double a, double b);
		double divide(double a, double b);
};

#endif // CALCULATOR_H