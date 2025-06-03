#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// Linear least squares: f(x) = a1*x + a0
void linearLS(Point* pts, int n, double& a0, double& a1) {
    double sx = 0, sy = 0, sxy = 0, sx2 = 0;
    
    for (int i = 0; i < n; i++) {
        sx += pts[i].x;
        sy += pts[i].y;
        sxy += pts[i].x * pts[i].y;
        sx2 += pts[i].x * pts[i].x;
    }
    
    // Normal equations solution
    double det = n * sx2 - sx * sx;
    a0 = (sy * sx2 - sx * sxy) / det;
    a1 = (n * sxy - sx * sy) / det;
}

// Exponential least squares: f(x) = a + b*exp(c*x)
// Simple approach: linearize by taking log
void exponentialLS(Point* pts, int n, double& a, double& b, double& c) {
    // Initial guess: a = min(y) - 10
    a = pts[0].y;
    for (int i = 1; i < n; i++) {
        if (pts[i].y < a) a = pts[i].y;
    }
    a -= 10;
    
    // Transform to linear problem: ln(y-a) = ln(b) + c*x
    double sx = 0, slny = 0, sxlny = 0, sx2 = 0;
    
    for (int i = 0; i < n; i++) {
        double lny = log(pts[i].y - a);
        sx += pts[i].x;
        slny += lny;
        sxlny += pts[i].x * lny;
        sx2 += pts[i].x * pts[i].x;
    }
    
    // Solve for ln(b) and c
    double det = n * sx2 - sx * sx;
    double lnb = (slny * sx2 - sx * sxlny) / det;
    c = (n * sxlny - sx * slny) / det;
    b = exp(lnb);
}

void approximate() {
    // Read points from file
    ifstream fin("points.txt");
    Point pts[4];
    int n = 0;
    
    while (fin >> pts[n].x >> pts[n].y) {
        n++;
    }
    fin.close();
    
    // Linear approximation
    double a0, a1;
    linearLS(pts, n, a0, a1);
    
    cout << "\nLinear: f(x) = " << a1 << "*x + " << a0 << endl;
    
    // Calculate error for linear
    double linError = 0;
    for (int i = 0; i < n; i++) {
        double pred = a1 * pts[i].x + a0;
        linError += (pts[i].y - pred) * (pts[i].y - pred);
    }
    linError = sqrt(linError / (n - 2));
    cout << "Standard error: " << linError << endl;
    
    // Exponential approximation
    double a, b, c;
    exponentialLS(pts, n, a, b, c);
    
    cout << "\nExponential: f(x) = " << a << " + " << b << "*exp(" << c << "*x)" << endl;
    
    // Calculate error for exponential
    double expError = 0;
    for (int i = 0; i < n; i++) {
        double pred = a + b * exp(c * pts[i].x);
        expError += (pts[i].y - pred) * (pts[i].y - pred);
    }
    expError = sqrt(expError / (n - 3));
    cout << "Standard error: " << expError << endl;
    
    // Save approximations for plotting
    ofstream fout("approx.txt");
    
    // Extended range for visualization
    double xMin = pts[0].x - 0.5;
    double xMax = pts[n-1].x + 0.5;
    double dx = (xMax - xMin) / 100;
    
    for (int i = 0; i <= 100; i++) {
        double x = xMin + i * dx;
        double yLin = a1 * x + a0;
        double yExp = a + b * exp(c * x);
        fout << x << " " << yLin << " " << yExp << endl;
    }
    
    fout.close();
}
