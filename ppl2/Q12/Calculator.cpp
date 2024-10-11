
#include "Calculator.h"

double Calculator::calculate(double num1, char op, double num2){
	switch (op){
		case '+':
    			return add(num1, num2);
		case '-':
			return subtract(num1, num2);
		case '*':
			return multiply(num1, num2);
		case '/':
			return divide(num1, num2);
		default:
    			throw std::invalid_argument("ERROR: unknown operator!!!");
	}
}


double Calculator::add(double a, double b){
	return a + b;
}

double Calculator::subtract(double a, double b){
	return a - b;
}

double Calculator::multiply(double a, double b){
	return a * b;
}

double Calculator::divide(double a, double b){
	if (b == 0){
	throw std::runtime_error("divide by zero exception!!!");
	}
	return a / b;    
};