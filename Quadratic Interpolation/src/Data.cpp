#include <vector>
#include <fstream>
#include "Data.h"

void RetriveData(std::vector<std::vector<double>>& values, int& line_count, std::string filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        throw std::exception(("Retriving Data: File " + filename + " doesn't exist\n").c_str());
        return;
    }
    line_count = std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n') + 1;
    file.seekg(0, std::ios::beg);
    values.resize(4);
    for (int i = 0; i < 4; i++)
        values[i].resize(line_count);

    for (int j = 0; j < line_count; j++)
        for (int i = 0; i < 4; i++)
            file >> values[i][j];

    file.close();
    return;
}