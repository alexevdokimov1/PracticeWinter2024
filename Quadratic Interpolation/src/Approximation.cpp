#include <map>
#include <vector>
#include "Approximation.h"
#include "Gaus.h"

std::vector <double> Aproximate(const std::vector<double>& x, const std::vector<double>& y, const int order) {

    std::vector<double> x_coef(2 * order - 1, 0);
    std::vector<double> y_coef(order, 0);

    for (int k = 0; k < 2 * order - 1; k++)
        for (int i = 0; i < x.size(); i++)
            x_coef[k] += pow(x[i], k);

    for (int k = 0; k < order; k++)
        for (int i = 0; i < x.size(); i++)
            y_coef[k] += y[i] * pow(x[i], k);

    //создание матрицы
    std::vector<std::vector<double>> matrix(order, std::vector<double>(order));

    //вывод матрицы//
    for (int k = 1; k < 2 * order; k++)
        for (int i = 0; i < k; i++)
            if (i < order && k - i - 1 < order)
                matrix[i][k - i - 1] = x_coef[k - 1];

    std::vector<double> x_sol = Gaus(matrix, y_coef, order);

    std::reverse(x_sol.begin(), x_sol.end());
    return x_sol;
}