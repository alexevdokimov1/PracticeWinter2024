#include <iostream>
#include <vector>
#include <cstdlib>
#include <exception> 
#include <cmath>
#include "Function.h"
#include "Approximation.h"
#include "Data.h"

int main() {
    
    std::vector<std::vector<double>> experimental_values, calculated_values;
    int experimental_values_count, calculated_values_count;

    try {
    RetriveData(experimental_values, experimental_values_count, "Data/Real.txt");
    RetriveData(calculated_values, calculated_values_count, "Data/Calculated.txt");
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception:\t" << e.what() << '\n';
        return 0;
    }

    std::vector<double> slice, slice2;
    for (int i = 2; i < experimental_values_count - 1; i++) {
        for (int j = 2; j < calculated_values_count - 1; j++)
            if (experimental_values[0][i] > calculated_values[0][j] &&
                experimental_values[0][i + 1] > calculated_values[0][j + 1]) {
                slice = std::vector<double>(calculated_values[0].begin() + i - 2, calculated_values[0].begin() + i + 2);
                slice2 = std::vector<double>(calculated_values[1].begin() + i - 2, calculated_values[1].begin() + i + 2);

                std::vector<double> x_sol = Aproximate(slice, slice2, 3);

                double x_closest = calcEquation(x_sol[0], x_sol[1], x_sol[2], calculated_values[0][i], calculated_values[1][i], calculated_values[1][i - 2], calculated_values[1][i + 1], 0.01);

                std::cout << x_closest << "\n";
            }



    }

    system("pause");

    return 0;
}
