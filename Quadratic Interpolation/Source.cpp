#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm> 
#include "Header.h"


// RetriveData - метод
// принимает ссылку на массив (std::vector<std::vector<double>>) и std::string filename - имя файла
// обрабатывает файл и возвращает данные из него
void RetriveData(std::vector<std::vector<double>>& values, int& line_count, std::string filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        throw std::exception(("Retriving Data: File " + filename + " doesn't exist\n").c_str());
        return;
    }
    line_count = std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n') + 1;
    file.seekg(0, std::ios::beg);
    values.resize(4);
    for (int i = 0; i < 4; i++)
        values[i].resize(line_count);

    for (int j = 0; j < line_count; j++)
        for (int i = 0; i < 4; i++)
            file >> values[i][j];
        
    file.close();
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

void SwapToMax(std::vector<std::vector<double>>& matrix, std::vector<double>& b, int k, const int& n)
{
    int max_index = k;
    for (int i = k + 1; i < n; i++)
        if (std::abs(matrix[i][k]) > std::abs(matrix[max_index][k])) max_index = i;

    std::swap(matrix[k], matrix[max_index]);
    std::swap(b[k], b[max_index]);
}

std::vector<double> Gaus(std::vector<std::vector<double>> matrix, std::vector<double> b, const int n)
{
    double a_first;
    for (int k = 0; k < n; k++)
    {
        //обмен местами строк
        SwapToMax(matrix, b, k, n);

        //деление строки
        b[k] /= matrix[k][k];
        for (int i = n - 1; i >= 0; i--)
            matrix[k][i] /= matrix[k][k];

        //вычитание из каждой строки поделенной строки
        for (int i = k + 1; i < n; i++) {
            a_first = matrix[i][k];
            b[i] = b[i] - b[k] * a_first;
            for (int j = k; j < n; j++)
                matrix[i][j] = matrix[i][j] - matrix[k][j] * a_first;
        }
    }
    std::vector<double> x(n);
    x[n - 1] = b[n - 1] / matrix[n - 1][n - 1];

    double s;

    for (int i = n - 2; i >= 0; i--)
    {
        s = 0;
        for (int j = i + 1; j < n; j++)
            s += matrix[i][j] * x[j];
        x[i] = b[i] - s;
    }
    return x;
}

std::vector <double> Aproximate(const std::vector<double>& x, const std::vector<double>& y) {
    std::vector<double> x_coef(5, 0);
    std::vector<double> y_coef(3, 0);

    for (int k = 0; k < 5; k++)
        for (int i = 0; i < x.size(); i++)
            x_coef[k] += pow(x[i], k);

    for (int k = 0; k <= 2; k++)
        for (int i = 0; i < x.size(); i++)
            y_coef[k] += y[i] * pow(x[i], k);

    const int n = 3;

    std::vector<std::vector<double>> matrix(n, std::vector<double>(n));

    for (int i = 0; i < n; i++)
        matrix[i][n - i - 1] = x_coef[2];

    for (int i = 0; i < n - 1; i++)
        matrix[i][n - i - 2] = x_coef[1];

    for (int i = 0; i < n - 2; i++)
        matrix[i][n - i - 3] = x_coef[0];

    for (int i = n - 1; i > 0; i--)
        matrix[i][n - i] = x_coef[3];

    for (int i = n - 1; i > 1; i--)
        matrix[i][n - i + 1] = x_coef[4];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            std::cout << matrix[i][j] << "\t";
        std::cout << "\n";
    }

    std::vector<double> x_sol = Gaus(matrix, y_coef, n);

    std::reverse(x_sol.begin(), x_sol.end());
    return x_sol;
}