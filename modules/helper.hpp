// helper.hpp

#ifndef HELPER_HPP
#define HELPER_HPP
#include <string>
using namespace std;

void makeSwap(double& a, double& b);

template <typename T> int sign(T val);

double getDouble(string prompt = "");

void checkBounds(double& a, double& b);

bool isZero(double x);

bool isOutBound(double dx, double upper_bound);
#endif

