#include "../modules/helper.hpp"
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

// presicion for x, y
const unsigned int PRESICE = 4;

// struct for points -> x_k, y_k, f_k
struct point {
    double x, y, f;
};

// bounds, delta x, x0, y0, f0, N (amount of steps)
struct inputData {
    double a, b, dx, x, y, f;
    int N;
};

// Function f(x, y) = x + y
double mainFn(double x, double y) { return x + y; }

// Euler function
double eulerFn(double y_k, double fn_k, double delta_x) {
    return y_k + fn_k * delta_x;
}

// Prototypes
// getter for delta x
double getdx(double upperBound);

// Numeric methods and presice method
point* calcAdamsBashforth(inputData info);
point* calcEuler(inputData info);
point* calcPrecise(inputData info);


// Init function for struct points
void initPoints(point* &points, inputData data, bool isPrecise);

// Write to disk data points 
int writeInfo(point* values, string filename, const int N);

// Execute function for gnuplot
int runGnuplot();

int main() {
    inputData data;

    // User input
    data.a = getDouble("a => ");
    data.b = getDouble("b => ");
    checkBounds(data.a, data.b);

    data.x = getDouble("x0 => ");
    while ((data.x < data.a) || (data.x > data.b)) {
        cout << "Warning: ";
        cout << data.x << " not in range [" << data.a << ", " << data.b << "]";
        cout << ". Please re-enter x0 which in correct range." << endl;
        data.x = getDouble("x0 => ");
    }
    data.y = getDouble("y0 => ");
    data.f = mainFn(data.x, data.y);

    data.dx = getdx(data.b);
    data.N = ceil((data.b - data.a) / data.dx) + 1;

    // Calculating points for each method
    point* ABM = calcAdamsBashforth(data);
    point* EM = calcEuler(data);
    point* PM = calcPrecise(data);

    // Write to .plt format
    writeInfo(ABM, "adams_bashforth.plt", data.N);
    writeInfo(EM, "euler.plt", data.N);
    writeInfo(PM, "presice.plt", data.N);

    delete [] ABM;
    delete [] EM;
    delete [] PM;

    // Init gnuplot
    runGnuplot();

    return 0;
}

double getdx(double upperBound) {
    double dx = getDouble("dx => ");
    while (isZero(dx) || isOutBound(dx, upperBound)) {
        if (isZero(dx)) {
            cout << "Warning: ";
            cout << "dx can't be zero." << endl;
            cout << "Please re-enter dx." << endl;
            dx = getDouble("dx => ");
        } else {
            cout << "Warning: ";
            cout << dx << " greater then " << upperBound << endl;
            cout << "Please re-enter dx." << endl;
            dx = getDouble("dx => ");
        }
    }
    return dx;
}

point* calcAdamsBashforth(inputData data) {
    // ABM -> Adams-Bashforth method points
    point* ABM = nullptr;
    initPoints(ABM, data, false);

    for (int i = 2; i < data.N; i++) {
        // y_k = y_{k-1} + dx/2 * (3*f_{k-1} - f_{k-2})
        ABM[i].y = ABM[i-1].y + data.dx/2 * (3*ABM[i-1].f - ABM[i-2].f);
        ABM[i].x = ABM[i-1].x + data.dx;
        ABM[i].f = mainFn(ABM[i].x, ABM[i].y);
    } 
    return ABM; 
}

point* calcEuler(inputData data) {
    // EM -> Euler method points
    point* EM = nullptr;
    initPoints(EM, data, false);

    for (int i = 1; i < data.N; i++) {
        EM[i].y = eulerFn(EM[i-1].y, EM[i-1].f, data.dx);
        EM[i].x = EM[i-1].x + data.dx;
        EM[i].f = mainFn(EM[i].x, EM[i].y);
    } 
    return EM;
}

point* calcPrecise(inputData data) {
    // PM -> Presice method (analytical solution) points
    point* PM = nullptr;
    initPoints(PM, data, true);

    const double C = (PM[0].x + PM[0].y + 1) / exp(PM[0].x);

    for (int i = 1; i < data.N; i++) {
        PM[i].x = PM[i-1].x + data.dx;
        PM[i].y = C * exp(PM[i].x) - PM[i].x - 1;
        PM[i].f = mainFn(PM[i].x, PM[i].y);
    } 
    return PM;
}

void initPoints(point*& points, inputData data, bool isPrecise) {
    points = new point[data.N];
    points[0].x = data.x;
    points[0].y = data.y;
    points[0].f = data.f;

    if (!isPrecise) {
        points[1].y = eulerFn(points[0].y, points[0].f, data.dx);
        points[1].x = points[0].x + data.dx;
        points[1].f = mainFn(points[1].x, points[1].y);
    }
}

int writeInfo(point* values, string filename, const int N) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Error: can't open file." << endl;
        return 1;
    }

    outFile << fixed << setprecision(PRESICE);
    for (int i = 0; i < N; i++) {
        outFile << values[i].x << " " << values[i].y << endl;
    }

    outFile.close();
    return 0;
}

int runGnuplot() {
    return system("gnuplot problem3.plt");
}

