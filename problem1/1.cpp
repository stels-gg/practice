#include <iomanip>
#include <iostream>
#include <cmath>
#include "../modules/helper.hpp"
using namespace std;

// Constants
const unsigned int STARTING_POINT = 15;
const unsigned int INCREMENT = 2;
const unsigned int MAX_ITERATIONS = 1000000;
const int PRECISION = 4;

// Function to integrate
double f(double x) {
	return x * sin(x) / sqrt(1 + x * x);
}

// Left rectangle method
double leftRectangle(double a, double b, unsigned int steps) {
	double h = (b - a) / steps;
	double sum = 0;
	for (int i = 0; i < steps; i++)
	{
		double x = a + i * h;
		sum += f(x);
	}
	return sum * h;
}


int main() {
	// User's input
	double a, b;
    a = getDouble("Enter bound a: ");
    b = getDouble("Enter bound b: ");

	// Newton-Simpson formula
	double integralNS = (b - a) / 6 * (f(a) + 4 * f((a + b) / 2) + f(b));
	cout << "Simpson: " << integralNS << endl;

	// Left Rectangle method
    unsigned int steps = STARTING_POINT;
    unsigned long iteration = 0;
    double delta = 100.0;
    // integral Left Rectangle method
    double currLR, prevLR = 0;

	while ((iteration < MAX_ITERATIONS) && (delta > 1.0))  {
        ++iteration;
        prevLR = currLR;
		currLR = leftRectangle(a, b, steps);
        if (iteration > 1) {
            // Relative error
            delta = abs((currLR - prevLR) / currLR * 100);
        }
        steps *= INCREMENT;
	}

	cout << "Left Rectangle: " << currLR << endl;
	cout << "Total steps for precise accuracy: " << steps / INCREMENT << endl;
    cout << fixed << setprecision(PRECISION);
    cout << "Accuracy: " << delta << endl;

	return 0;
}

