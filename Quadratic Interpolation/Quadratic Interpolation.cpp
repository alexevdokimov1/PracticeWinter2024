#include <iostream>
#include <vector>
#include <cstdlib>
#include <exception>  
#include "Header.h"


int main() {
    
    try {
        
    std::vector<std::vector<double>> real_values, calculated_values;
    
    RetriveData(real_values, "Data/Real.txt");
    RetriveData(calculated_values, "Data/Calculated.txt");
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception:\t" << e.what() << '\n';
    }

    std::cout << "Enter a, b, c, x0, y0, left, right, eps\n";

    double a, b, c, x0, y0, left, right, eps;

    std::cin >> a >> b >> c >> x0 >> y0 >> left >> right >> eps;

    std::cout << calcEquation(a, b, c, x0, y0, left, right, eps) << "\n";


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
