#pragma once
#include <map>

void RetriveData(std::vector<std::vector<double>>& values, int& line_count, std::string filename);

double f(std::map <char, double>& values, double x);

double calcEquation(double a, double b, double c, double x0, double y0, double x_min, double x_max, double eps);

double Interpolation(double x, const std::vector<double>& xValues, const std::vector<double>& yValues);