#include <iostream>
#include <vector>
#include <cstdlib>
#include <exception>  
#include <iomanip>
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

    double time, x_inter, y_inter, z_inter;
    for (int i = 2; i < experimental_values_count-2; i++) //не трогаем 0-2 и n-2-n точки
    {
        time = experimental_values[0][i];
        x_inter = Interpolation(time, experimental_values[0], calculated_values[1]);
        y_inter = Interpolation(x_inter, calculated_values[1], calculated_values[2]);
        z_inter = Interpolation(x_inter, calculated_values[1], calculated_values[3]);
        std::cout << time << std::setw(20) << x_inter << std::setw(20) << y_inter << std::setw(20) << z_inter << "\n";

        
    }

    system("pause");

    return 0;
}
