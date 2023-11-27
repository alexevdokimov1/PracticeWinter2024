#include <iostream>
#include <vector>
#include <cstdlib>
#include <exception>  
#include "Header.h"
#include <fstream>


int main() {
    
    std::vector<std::vector<double>> experimental_values, calculated_values;

    try {
    
    RetriveData(experimental_values, "Data/Real.txt");
    RetriveData(calculated_values, "Data/Calculated.txt");
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception:\t" << e.what() << '\n';
    }

    for (int i = 0; i < experimental_values.size(); i++)
    {

    }

    std::vector<double> X_vec{ 2,6,8,10,11 };
    std::vector<double> Y_vec{ 4,36,64,100,121 };

    double x;
    std::cout << "Enter x\n";
    std::cin >> x;
    try {
    std::cout << "Answer is " << Interpolation(x, X_vec, Y_vec) << "\n";
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception:\t" << e.what() << '\n';
    }
    system("pause");

    return 0;
}
