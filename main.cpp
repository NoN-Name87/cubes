#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
#include <algorithm>

void display_cubes(std::vector<int> cubes) noexcept
{
    std::cout << "MATRIX\n";
    for(int i = 0; i < cubes.size(); i++)
    {
        for(int j = 0; j < cubes.size(); j++)
        {
            if(cubes.size() - 1 - i  == cubes[j] - 1)
            {
                std::cout << "1 ";
                cubes[j]--;
                continue;
            }
            std::cout << "0 ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void get_rotated_cubes(std::vector<int> & cubes, int rotations)
{
    std::vector<int> rotated_cubes(cubes.size(), 0);
    for(int k = 0; rotations > 0 && k < (rotations - 1 % 2) + 1; k++)
    {
        for(auto & i : cubes)
        {
            std::for_each(rotated_cubes.begin(), rotated_cubes.begin() + i, [](int & elem)
            {
                elem++;
            });
        }
        cubes = rotated_cubes;
        display_cubes(cubes);
        rotated_cubes.clear();
        rotated_cubes.resize(cubes.size(), 0);
    }
}

std::vector<int> get_cubes_num(int N)
{
    std::string temp;
    std::getline(std::cin, temp);
    std::stringstream total_cubes(temp);
    std::vector<int> cubes;
    while(std::getline(total_cubes, temp, ' '))
    {
        if(temp.empty())
            continue;
        int num_cubes = std::stoi(temp);
        if(num_cubes >= 0 && num_cubes <= N)
            cubes.push_back(num_cubes);
        else
            throw std::logic_error("Number of cubes must be positive");
    }
    if(cubes.size() != N)
        throw std::logic_error("Num of column cubes != N");
    return cubes;
}

int main(int argc, char **argv)
{
    int N{0};
    int rotations{0};
    std::cout << "Enter matrix size and number of rotations: \n";
    try
    {
        std::cin >> N >> rotations;
        std::cin.get();
        if(N < 1 || N > 10)
        {
            throw std::logic_error("Matrix range must be from 1 to 10");
        }
        auto cubes = get_cubes_num(N);
        display_cubes(cubes);
        get_rotated_cubes(cubes, rotations);
        for(const auto & i : cubes)
        {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
    catch(const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << "\n";
    }   
}