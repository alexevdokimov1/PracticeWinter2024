#include <iostream>
#include <vector>
#include <cstdlib>
#include <exception> 
#include <cmath> 
#include "Header.h"

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

    std::vector<double> x = { 0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9 };
    std::vector<double> y = { 0.21, 0.23, 0.31, 0.29, 0.42, 0.35,0.58,0.61, 0.59, 0.66 };

    std::vector<double> x_sol = Aproximate(x, y);

    for (int i = 0; i < 3; i++) {
        switch (i) {
        case 0: std::cout << "a: ";
        break;
        case 1: std::cout << "b: ";
        break;
        case 2: std::cout << "c: ";
        break;
        }
        std::cout << x_sol[i] << "\n";
    }
    std::cout << "\n";

    system("pause");

    return 0;
}
