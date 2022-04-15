#include "Loader.h"
#include "iostream"

Matrix Loader::ConsoleLoader()
{
    std::string getter_matrix;
    std::cout << "Please enter matrix:" << std::endl;
    std::cin >> getter_matrix;
    return Matrix(getter_matrix.c_str());
}

Matrix Loader::FileLoader(const std::filesystem::path& file_name)
{
    std::ifstream read_file;
    std::string getter_matrix;
    read_file.open(std::filesystem::absolute(file_name));
    if(read_file.is_open())
    {
        read_file >> getter_matrix;
    }
    read_file.close();
    return Matrix(getter_matrix.c_str());
}