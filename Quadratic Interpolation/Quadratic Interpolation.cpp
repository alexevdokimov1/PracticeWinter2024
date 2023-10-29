#include <iostream>
#include <vector>
#include <windows.h>
#include <exception>  
#include "Header.h"


int main() {
    
    try {
        
    std::vector<std::vector<double>> real_values, calculated_values;
    
    RetriveData(real_values, "Data/Real.txt");
    RetriveData(calculated_values, "Data/Calculated.txt");

    std::cout << calcEquation(1, 1, 1, 1, 1, 0, 1, 0.0001) << "\n";
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception:\t" << e.what() << '\n';
    }
    

    system("pause");

    return 0;
}
