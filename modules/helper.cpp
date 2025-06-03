// helper.cpp

#include "helper.hpp"
#include <iostream>
#include <limits>
#include <string>
using namespace std;

void makeSwap(double& a, double& b) {
    double tmp = a;
    a = b;
    b = tmp;
    return;
}

template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

double getDouble(string prompt) {
    double val;
    if (!prompt.empty()) {
        cout << prompt;
    }
    cin >> val;
    while (cin.fail()) {
        cout << "Invalid input. Please enter the number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> val;
    }
    return val;
}

void checkBounds(double& a, double& b) {
    if (a > b) {
        cout << "Warning: ";
        cout << a << " greater then " << b << endl;
        cout << "Bounds will be replaced." << endl;
        makeSwap(a, b);
    } else if (a == b) {
        while (a == b) {
            cout << "Warning: ";
            cout << a << " can't be equal " << b << endl;
            cout << "Please re-enter bounds." << endl;
            a = getDouble("a: ");
            b = getDouble("b: ");
        }
    }
    return;
}

bool isZero(double x) {
    return sign(x) == 0;
}

bool isOutBound(double dx, double upper_bound) {
    return dx > upper_bound;
}

