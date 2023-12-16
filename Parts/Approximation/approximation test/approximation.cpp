#include <iostream>
#include <vector>
#include <cstdlib> 
#include <cmath> 
#include <algorithm>
#include <fstream>

typedef std::vector<double> dVect;

void PrintMatrix(std::vector<dVect>& matrix, const int& n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            std::cout << matrix[i][j] << "\t";
        std::cout << "\n";
    }
}

void SwapToMaxElement(std::vector<dVect>& matrix, std::vector<double>& b, int k, const int& n) {
    int max_index = k;
    for (int i = k + 1; i < n; i++)
        if (std::abs(matrix[i][k]) > std::abs(matrix[max_index][k])) max_index = i;

    std::swap(matrix[k], matrix[max_index]);
    std::swap(b[k], b[max_index]);
}

//нахождение корней матрицы матодом Гаусса
std::vector<double> Gaus(std::vector<dVect> matrix, std::vector<double> b, const int n) {
    double a_first;
    for (int k = 0; k < n; k++)
    {
        //обмен местами строк
        SwapToMaxElement(matrix, b, k, n);

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

int main() {

    std::cout << "Enter approximation order:\n";
    int n;
    std::cin >> n;

    std::ifstream file("vector.txt");
    int count;
    file >> count;

    std::vector<double> x(count);
    std::vector<double> y(count);

    /*
        std::vector<double> x = { 0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9 };
        std::vector<double> y = { 0.21, 0.23, 0.31, 0.29, 0.42, 0.35,0.58,0.61, 0.59, 0.66 };
    */

    for (int i = 0; i < count; i++)
        file >> x[i] >> y[i];

    std::vector<double> x_coef(2 * n - 1, 0);
    std::vector<double> y_coef(n, 0);

    for (int k = 0; k < 2 * n - 1; k++)
        for (int i = 0; i < x.size(); i++)
            x_coef[k] += pow(x[i], k);

    for (int k = 0; k < n; k++)
        for (int i = 0; i < x.size(); i++)
            y_coef[k] += y[i] * pow(x[i], k);

    //создание матрицы
    std::vector<dVect> matrix(n, dVect(n));

    //вывод матрицы//
    for (int k = 1; k < 2 * n; k++)
        for (int i = 0; i < k; i++)
            if (i < n && k - i - 1 < n)
                matrix[i][k - i - 1] = x_coef[k - 1];

    //PrintMatrix(matrix, n);

    dVect x_sol = Gaus(matrix, y_coef, n);

    std::reverse(x_sol.begin(), x_sol.end());

    for (int i = 0; i < x_sol.size(); i++)
        std::cout << (char)(97 + i) << " = " << x_sol[i] << "\n";

    system("pause");
    return 0;
}