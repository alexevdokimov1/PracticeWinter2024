#include <iostream>
#include <vector>
#include <cstdlib>
#include <exception>  
#include "Header.h"
#include <fstream>


int main() {
    
    try {
        
    std::vector<std::vector<double>> experimental_values, calculated_values;
    
    RetriveData(experimental_values, "Data/Real.txt");
    RetriveData(calculated_values, "Data/Calculated.txt");
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception:\t" << e.what() << '\n';
    }

    int n;
    double solution_count, a, b, c, x0, y0, left, right, eps = 0.01;
    double calc;
    std::vector <double> solutions;
    bool fits;

    std::ifstream file("Debug/CalcTest.txt");
    if (!file) return -1;
    
    file >> n;
    std::cout << "Enter solve accuracy:\n";
     
    std::cin >> eps;
    std::cout << "Accuracy set to " << eps << "\n";
    
    for (int i = 0; i < n; i++) {
        fits = false;
        file >> a >> b >> c >> x0 >> y0 >> left >> right >> solution_count;
        solutions.clear();
        solutions.resize(solution_count);
        for (int j = 0; j < solution_count; j++)
            file >> solutions[j];
        calc = calcEquation(a, b, c, x0, y0, left, right, eps);
        for (int j = 0; j < solution_count; j++)
            if (std::abs(calc - solutions[j]) <= eps) {
                std::cout << "Calculated " << calc << "\t" << "Predeterminated " << solutions[j] << "\n";
                fits = true;
                break;
            }
        if (!fits){
            std::cout << "Error at " << i << " with calculated value: " << calc << " with row of answers: ";
            for (int j = 0; j < solution_count; j++)
                std::cout << solutions[j] << "\t";
            std::cout << "\n";
        } 
    }

    file.close();

    system("pause");

    return 0;

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
