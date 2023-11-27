#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include "Header.h"


// RetriveData - метод
// принимает ссылку на массив (std::vector<std::vector<double>>) и std::string filename - имя файла
// обрабатывает файл и возвращает данные из него
void RetriveData(std::vector<std::vector<double>>& values, std::string filename)
{
    std::ifstream f(filename);
    if (!f)
    {
        throw std::exception(("Retriving Data: File " + filename + " doesn't exist\n").c_str());
        return;
    }
    std::vector<double> single;
    while (!f.eof())
    {
        single.clear();
        single.resize(4);
        for (int i = 0; i < 4; i++)
            f >> single[i];
        values.push_back(single);
    }
    f.close();
    return;
}

// f - функция
// принимает ссылку на std::map values и double x
// возвращает значение y=(2*a*x+b)*(a*x^2+b*x+c-y0)+x-x0, где a,b,c,x0,y0 - аргументы из std::map

double f(std::map <char, double>& values, double x) {
    return (2 * values['a'] * x + values['b']) * (values['a'] * x * x + values['b'] * x + values['c'] - values['y']) + x - values['x'];
}

// calcEquation - функция нахождения значения x методом средней линии
// принимает double a, double b, double c,double x0, double y0, double x_assumed(предположительное значение)  и double eps(точность)
// возвращает корень f(x)
double calcEquation(double a, double b, double c, double x0_param, double y0_param, double left, double right, double eps)
{
    std::map <char, double> values{
        {'a', a},
        {'b', b},
        {'c', c},
        {'x', x0_param},
        {'y', y0_param}
    };

    if (std::abs(f(values, left)) < eps) return left;
    if (std::abs(f(values, right)) < eps) return right;
    while (std::abs(right - left) > 2 * eps) {
        double c = (left + right) / 2;
        if (std::abs(f(values, c)) < eps) return c;
        else if (f(values, left) * f(values, c) < 0) right = c;
        else left = c;
    }
    return (left + right) / 2;
}

//Interpolation
double Interpolation(double x, const std::vector<double>& xValues, const std::vector<double>& yValues) {
    int n = xValues.size();

    for (int i = 0; i <= n - 4; i++) {
        if (x >= xValues[i+1] && x <= xValues[i + 2]) {
            double x0 = xValues[i];
            double x1 = xValues[i + 1];
            double x2 = xValues[i + 2];
            double x3 = xValues[i + 3];

            double y0 = yValues[i];
            double y1 = yValues[i + 1];
            double y2 = yValues[i + 2];
            double y3 = yValues[i + 3];

            double L0 = (x - x1) * (x - x2) * (x - x3) / ((x0 - x1) * (x0 - x2) * (x0 - x3));
            double L1 = (x - x0) * (x - x2) * (x - x3) / ((x1 - x0) * (x1 - x2) * (x1 - x3));
            double L2 = (x - x0) * (x - x1) * (x - x3) / ((x2 - x0) * (x2 - x1) * (x2 - x3));
            double L3 = (x - x0) * (x - x1) * (x - x2) / ((x3 - x0) * (x3 - x1) * (x3 - x2));

            return y0 * L0 + y1 * L1 + y2 * L2 + y3 * L3;
        }
    }
    throw std::exception("Interpolation: x is out of range\n");
    return 0.0;
}