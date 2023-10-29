#pragma once
#include <map>

void RetriveData(std::vector<std::vector<double>>& values, std::string filename);

double f(std::map <char, double>& values, double x);

double derivative(std::map <char, double>& values, double x, double eps);

double secondDerivative(std::map <char, double>& values, double x, double eps);

double calcEquation(double a, double b, double c, double x0, double y0, double x_min, double x_max, double eps);

double Interpolation(double x, const std::vector<double>& xValues, const std::vector<double>& yValues);