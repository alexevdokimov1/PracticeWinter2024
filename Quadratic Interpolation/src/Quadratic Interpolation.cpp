#include <iostream>
#include <vector>
#include <exception> 
#include <cmath>
#include <fstream> 
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

    std::vector<double> time_slice, x_slice, y_slice, z_slice;
    double x_closest, y_closest, z_closest;
    std::vector<double> x_sol, y_sol, z_sol;
    double x_del, y_del, z_del;

    std::ofstream output("Data/Result.txt");
    if (!output) {
        std::cout << "Output file can not be created\n";
        return 0;
    }

    int i_start = 0;
    for (int k = 0; k < experimental_values_count; k++) { //except first and last to set interval
        for (int i = i_start; i < calculated_values_count - 3; i++) {

            if (calculated_values[0][i+1] < experimental_values[0][k] && experimental_values[0][k] < calculated_values[0][i + 2]) {

                time_slice = std::vector<double>(calculated_values[0].begin() + i, calculated_values[0].begin() + i + 4); //time slice
                x_slice = std::vector<double>(calculated_values[1].begin() + i, calculated_values[1].begin() + i + 4); //x slice
                y_slice = std::vector<double>(calculated_values[2].begin() + i, calculated_values[2].begin() + i + 4); //y slice
                z_slice = std::vector<double>(calculated_values[3].begin() + i, calculated_values[3].begin() + i + 4); //z slice
                
                x_sol = Aproximate(time_slice, x_slice, 3); //aproximation of x to time
                y_sol = Aproximate(x_slice, y_slice, 3); //aproximation of y to x
                z_sol = Aproximate(x_slice, z_slice, 3); //aproximation of z to x
               
                x_closest =  calcEquation(x_sol[0], x_sol[1], x_sol[2], experimental_values[0][k], experimental_values[1][k], 
                    calculated_values[1][i+1], calculated_values[1][i + 2], 0.001); //finding x closest
               
                y_closest = 0; //finding y based on x xlosest
                for (int v = 0; v < y_sol.size(); v++)
                    y_closest += y_sol[v] * pow(x_closest, 2 - v);

                z_closest = 0; //finding z based on x xlosest
                for (int v = 0; v < z_sol.size(); v++)
                    z_closest += z_sol[v] * pow(x_closest, 2 - v);

                x_del = std::abs(x_closest - experimental_values[1][k]);
                y_del = std::abs(y_closest - experimental_values[2][k]);
                z_del = std::abs(z_closest - experimental_values[3][k]);

                output << experimental_values[0][k] << "\t" << x_del << "\t" << y_del << "\t" << z_del << "\n";

                if(i>4)i_start = i - 4;

                break;
            }      
        }
    }

    output.close();

    return 0;
}