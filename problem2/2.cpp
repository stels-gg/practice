#include <iostream>
#include <cmath>
#include <iomanip>
#include "../modules/helper.hpp"
using namespace std;

// Computation limits
const int MAX_ITERATIONS = 500;
const int EPSILON_LIMIT = 15;

// Main function
double f(double x) {
    return x * x - sin(x);
}

int main() {
    // Initialization variables
    double epsilon;         // accuracy
    double x0, x1, x2, x3;  // points for interpolation
    double f0, f1, f2;      // function values
    double h0, h1;          // step sizes
    double delta0, delta1;  // divided diffs
    double a, b, c;         // quadratic coeffs

    bool solutionFound = false;
    int iterCount = 0;

    // Ask user for accuracy
    epsilon = getDouble("Accuracy: ");
    while (epsilon > EPSILON_LIMIT) {
        cout << "Too high accuracy. Current limit: " << EPSILON_LIMIT << endl;
        cout << "Please enter accuracy number, less then " << EPSILON_LIMIT;
        cout << endl;
        epsilon = getDouble("Accuracy: ");
    }

    // Basic points
    x0 = 0.8;
    x1 = 0.85;
    x2 = 0.9;

    while (!solutionFound && iterCount < MAX_ITERATIONS) {
        iterCount++;

        // Find basic solution
        f0 = f(x0);
        f1 = f(x1);
        f2 = f(x2);

        // Find coefs
        h0 = x1 - x0; 
        h1 = x2 - x1;

        delta0 = (f1 - f0) / h0;
        delta1 = (f2 - f1) / h1;

        a = (delta1 - delta0) / (h1 + h0);
        b = a * h1 + delta1;
        c = f2;

        // Find x3
        x3 = x2 - 2 * c / (b + sign(b)*sqrt(b*b - 4*a*c));

        // Rewrite vars x
        x0 = x1;
        x1 = x2;
        x2 = x3;

        // Check criterion
        solutionFound = abs(f(x3)) < pow(10, -epsilon);
    }

    cout << setprecision(epsilon);

    if (solutionFound) {
        cout << fixed;
        cout << "Solution found: " << x3 << endl;
    } else {
        cout << "No solution found." << endl;
    }

    return 0;
}

