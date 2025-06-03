#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// Nearest neighbor - finds closest point and returns its y value
double nearestNeighbor(Point* pts, int n, double x) {
    int nearest = 0;
    double minDist = fabs(x - pts[0].x);
    
    for (int i = 1; i < n; i++) {
        double dist = fabs(x - pts[i].x);
        if (dist < minDist) {
            minDist = dist;
            nearest = i;
        }
    }
    return pts[nearest].y;
}

// Lagrange polynomial interpolation
double lagrange(Point* pts, int n, double x) {
    double result = 0;
    
    for (int i = 0; i < n; i++) {
        double term = pts[i].y;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term *= (x - pts[j].x) / (pts[i].x - pts[j].x);
            }
        }
        result += term;
    }
    return result;
}

void interpolate() {
    // Read points from file
    ifstream fin("points.txt");
    Point pts[4];
    int n = 0;
    
    while (fin >> pts[n].x >> pts[n].y) {
        n++;
    }
    fin.close();
    
    // Find min and max x
    double xMin = pts[0].x, xMax = pts[0].x;
    for (int i = 1; i < n; i++) {
        if (pts[i].x < xMin) xMin = pts[i].x;
        if (pts[i].x > xMax) xMax = pts[i].x;
    }
    
    // Calculate step
    const double dx = fabs(xMax - xMin) / (10.0 * (n - 1));
    const int steps = (int)((xMax - xMin) / dx) + 1;
    
    cout << "Range: [" << xMin << ", " << xMax << "]" << endl;
    cout << "Step: " << dx << endl;
    
    // Save to fixed filename for plotting
    const char* filename = "interp.txt";
    ofstream fout(filename);
    
    // Generate interpolated values
    cout << "\nFirst 5 values:" << endl;
    cout << "x\tNearest\tLagrange" << endl;
    
    for (int i = 0; i < steps; i++) {
        double x = xMin + i * dx;
        double yNN = nearestNeighbor(pts, n, x);
        double yL = lagrange(pts, n, x);
        
        fout << x << " " << yNN << " " << yL << endl;
        
        if (i < 5) {
            cout << x << "\t" << yNN << "\t" << yL << endl;
        }
    }
    
    fout.close();
    cout << "Saved to " << filename << endl;
    
    // Save original points for plotting
    ofstream orig("original.txt");
    for (int i = 0; i < n; i++) {
        orig << pts[i].x << " " << pts[i].y << endl;
    }
    orig.close();
}
