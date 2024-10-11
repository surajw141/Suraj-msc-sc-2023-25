#include "TriangleProp.h"
#include <iostream>
#include <cmath>

TriangleProp::TriangleProp(double a, double b, double c) : side1(a), side2(b), side3(c) {}

bool TriangleProp::isTriangle() const {
    return (side1 + side2 > side3) && (side1 + side3 > side2) && (side2 + side3 > side1);
}

void TriangleProp::printAngles() const {
    if (!isTriangle()) {
        std::cout << "The given sides do not form a triangle.\n";
        return;
    }

    double angleA = std::acos((side2 * side2 + side3 * side3 - side1 * side1) / (2 * side2 * side3));
    double angleB = std::acos((side1 * side1 + side3 * side3 - side2 * side2) / (2 * side1 * side3));
    double angleC = std::acos((side1 * side1 + side2 * side2 - side3 * side3) / (2 * side1 * side2));

    std::cout << "Internal angles of the triangle:\n";
    std::cout << "Angle A: " << angleA << " radians (" << angleA * 180 / M_PI << " degrees)\n";
    std::cout << "Angle B: " << angleB << " radians (" << angleB * 180 / M_PI << " degrees)\n";
    std::cout << "Angle C: " << angleC << " radians (" << angleC * 180 / M_PI << " degrees)\n";
}

void TriangleProp::printProperties() const {
    if (!isTriangle()) {
        std::cout << "The given sides do not form a triangle.\n";
        return;
    }

    std::cout << "Properties of the triangle:\n";

    if (side1 == side2 && side2 == side3) {
        std::cout << "It is an equilateral triangle.\n";
    } else if (side1 == side2 || side1 == side3 || side2 == side3) {
        std::cout << "It is an isosceles triangle.\n";
    } else {
        std::cout << "It is a scalene triangle.\n";
    }

    double angleA = std::acos((side2 * side2 + side3 * side3 - side1 * side1) / (2 * side2 * side3));
    double angleB = std::acos((side1 * side1 + side3 * side3 - side2 * side2) / (2 * side1 * side3));
    double angleC = std::acos((side1 * side1 + side2 * side2 - side3 * side3) / (2 * side1 * side2));

    if (angleA == M_PI / 2 || angleB == M_PI / 2 || angleC == M_PI / 2) {
        std::cout << "It is a right-angled triangle.\n";
    }
}

