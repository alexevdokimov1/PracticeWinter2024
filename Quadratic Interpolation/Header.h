#pragma once
#include <map>

void RetriveData(std::vector<std::vector<double>>& values, int& line_count, std::string filename);

double f(std::map <char, double>& values, double x);

double calcEquation(double a, double b, double c, double x0, double y0, double x_min, double x_max, double eps);

std::vector<double> Gaus(std::vector<std::vector<double>> matrix, std::vector<double> b, const int n);

std::vector <double> Aproximate(const std::vector<double>& x, const std::vector<double>& y);