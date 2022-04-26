#include "Loader.h"
#include "iostream"

std::tuple<bool, size_t> Loader::isInCash(const std::vector<cash_info>& cash, const std::string& name)
{

    for (size_t searcher_id = 0; searcher_id < cash.size(); ++searcher_id)
    {
        if (cash.at(searcher_id).owner_id == name)
        {
             return std::make_tuple(true, searcher_id);
        }
    }
    return std::make_tuple(false, 0);
}

Matrix ConsoleLoader::loadMatrix()
{
    std::string getter_matrix;
    std::string MatrixName;
    std::cout << "Please enter matrix:" << std::endl;
    std::cin >> getter_matrix;

    Matrix processMatrix(getter_matrix.c_str());

    std::cout << "Please give the name to input matrix"<< std::endl;
    std::cin >> MatrixName;

    auto [isPresent, where] = isInCash(cashBuffer, MatrixName);
    if(!isPresent)
    {
        cashBuffer.emplace_back(cash_info{MatrixName, processMatrix});
        return cashBuffer.back().slave_data;
    }
    else
    {
        return std::move(processMatrix);
    }
}

void ConsoleLoader::clear_cash()
{
    if (!cashBuffer.empty())
    {
        cashBuffer.clear();
    }
}

Matrix FileLoader::loadMatrix()
{
    std::string getter_matrix;
    read_thread.open(path);
    if(read_thread.is_open())
    {
        read_thread >> getter_matrix;
    }
    read_thread.close();
    return Matrix(getter_matrix.c_str());
}

Matrix FileLoader::loadMatrix(const std::string& fileName)
{
    auto [isPresent, where] = isInCash(cashBuffer, fileName);
    if (!isPresent)
    {
        setFileName(std::filesystem::absolute(fileName));
        cashBuffer.emplace_back(cash_info(fileName, loadMatrix()));
        return cashBuffer.at(cashBuffer.size() - 1).slave_data;
    }
    else
    {
        return cashBuffer.at(where).slave_data;
    }
}

void FileLoader::clear_cash()
{

    if(!cashBuffer.empty())
    {
        cashBuffer.clear();
    }
}