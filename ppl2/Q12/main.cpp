#include "Calculator.h"

void getInput(double &num1, char &op, double &num2){
	std::string input;
	std::getline(std::cin, input);
	std::istringstream iss(input);
	iss >> num1 >> op >> num2;
	if (iss.fail() || !iss.eof()){
		throw std::invalid_argument("ERROR: Invalid input format!!!");
	}
}
int main(){
	Calculator calculator;
	double num1, num2;
	char op;

	std::cout << "Enter calculation (e.g., 50.7 + 1.2): ";

	try{
		getInput(num1, op, num2);
		double result = calculator.calculate(num1, op, num2);
		std::cout << "Output: " << result << std::endl;
	}
	catch (const std::exception &e){
		std::cerr << e.what() << std::endl;
	}

return 0;
}