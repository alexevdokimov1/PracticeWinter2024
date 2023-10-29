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
    return;
}

// f - функция
// принимает ссылку на std::map values и double x
// возвращает значение y=(2*a*x+b)*(a*x^2+b*x+c-y0)+x-x0, где a,b,c,x0,y0 - аргументы из std::map

double f(std::map <char, double>& values, double x) {
    return (2 * values['a'] * x + values['b']) * (values['a'] * x * x + values['b'] * x + values['c'] - values['y']) + x - values['x'];
}

// derivative - функция нахождения производной от функции
// принимает ссылку на std::map values, double x и double eps(точность)
// возвращает производную от функции f
double derivative(std::map <char, double>& values, double x, double eps) {
    return (f(values, x + eps) - f(values, x)) / eps;
}

double secondDerivative(std::map <char, double>& values, double x, double eps) {
    return (f(values, x + eps) - 2 * f(values, x) + f(values, x - eps)) / (eps * eps);
}

// calcEquation - функция нахождения значения x методом Ньютона(не гарантируется сходисость)
// принимает double a, double b, double c,double x0, double y0, double x_assumed(предположительное значение)  и double eps(точность)
// возвращает корень f(x)
double calcEquation(double a, double b, double c, double x0_param, double y0_param, double x_min, double x_max, double eps)
{
    std::map <char, double> values{
        {'a', a},
        {'b', b},
        {'c', c},
        {'x', x0_param},
        {'y', y0_param}
    };

    double x0;

    if (f(values, x_min) * secondDerivative(values, x_min, eps) > 0)
        x0 = x_min;
    else if (f(values, x_max) * secondDerivative(values, x_max, eps) > 0)
        x0 = x_max;
    else {
        throw std::exception("CalcEquation: Newton func can't be found\n");
        return 0;
    }

    double x_start = x0;

    double x = x0 - f(values, x0) / derivative(values, x0, eps);
    while (std::abs(x - x0) > eps)
    {
        x0 = x;
        if (f(values, x0) * secondDerivative(values, x0, eps) <= 0)
        {
            throw std::exception("CalcEquation: Newton func can't be found\n");
            return 0;
        }
        x = x0 - f(values, x0) / derivative(values, x_start, eps);
    }
    return x;
}


//Interpolation
double Interpolation(double x, const std::vector<double>& xValues, const std::vector<double>& yValues) {
    int n = xValues.size();

    if (n != yValues.size()) {
        throw std::exception("Interpolation: Lack of data\n");
        return 0.0;
    }

    for (int i = 0; i < n - 2; i++) {
        if (x >= xValues[i] && x <= xValues[i + 2]) {
            double x0 = xValues[i];
            double x1 = xValues[i + 1];
            double x2 = xValues[i + 2];

            double y0 = yValues[i];
            double y1 = yValues[i + 1];
            double y2 = yValues[i + 2];

            double L0 = (x - x1) * (x - x2) / ((x0 - x1) * (x0 - x2));
            double L1 = (x - x0) * (x - x2) / ((x1 - x0) * (x1 - x2));
            double L2 = (x - x0) * (x - x1) / ((x2 - x0) * (x2 - x1));

            return y0 * L0 + y1 * L1 + y2 * L2;
        }
    }
    throw std::exception("Interpolation: x is out of range\n");
    return 0.0;
}