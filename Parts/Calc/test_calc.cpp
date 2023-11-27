#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

double f(std::map <char, double>& values, double x) {
    return (2 * values['a'] * x + values['b']) * (values['a'] * x * x + values['b'] * x + values['c'] - values['y']) + x - values['x'];
}

double calcEquation(double a, double b, double c, double x0_param, double y0_param, double left, double right, double eps)
{
    std::map <char, double> values{
        {'a', a},
        {'b', b},
        {'c', c},
        {'x', x0_param},
        {'y', y0_param}
    };

    if (std::abs(f(values, left)) < eps) return left;
    if (std::abs(f(values, right)) < eps) return right;
    while (std::abs(right - left) > 2 * eps) {
        double c = (left + right) / 2;
        if (std::abs(f(values, c)) < eps) return c;
        else if (f(values, left) * f(values, c) < 0) right = c;
        else left = c;
    }
    return (left + right) / 2;
}

main(){
	int n;
	double solution_count, a, b, c, x0, y0, left, right, eps = 0.01;
	double calc;
	std::vector <double> solutions;
	bool fits;
	
	std::ifstream file("CalcTest.txt");
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
}
