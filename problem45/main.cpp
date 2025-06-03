#include <cstdlib>
using namespace std;

// Common structure for both tasks
struct Point {
    double x, y;
};

// Function declarations
void interpolate();
void approximate();

int main() {
    // Run interpolation
    interpolate();
    
    // Run approximation
    approximate();
    
    // Run gnuplot
    system("gnuplot plot.plt");
    
    return 0;
}

// Include the implementations
#include "intrpl.cpp"
#include "apprxm.cpp"
