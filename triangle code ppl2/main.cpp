#include "TriangleProp.h"
#include <iostream>

int main() {
    double a, b, c;
    std::cout << "Enter the lengths of the three sides of the triangle: ";
    std::cin >> a >> b >> c;

    TriangleProp triangle(a, b, c);

    if (triangle.isTriangle()) {
        triangle.printAngles();
        triangle.printProperties();
    } else {
        std::cout << "The given sides do not form a triangle.\n";
    }

    return 0;
}

