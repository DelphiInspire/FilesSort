#include "Loader.h"
#include "iostream"

std::tuple<bool, size_t> ILoader::isInCache(const std::vector<cache_info>& cache, const std::string& name)
{

    for (size_t searcher_id = 0; searcher_id < cache.size(); ++searcher_id)
    {
        if (cache.at(searcher_id).owner_id == name)
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

    auto [isPresent, where] = isInCache(cacheBuffer, MatrixName);
    if(!isPresent)
    {
        cacheBuffer.emplace_back(cache_info{MatrixName, processMatrix});
        return cacheBuffer.back().slave_data;
    }
    else
    {
        return std::move(processMatrix);
    }
}

void ConsoleLoader::clear_cache()
{
    if (!cacheBuffer.empty())
    {
        cacheBuffer.clear();
    }
}

Matrix FileLoader::loadMatrix()
{
    std::ifstream read_thread;
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
    auto [isPresent, where] = isInCache(cacheBuffer, fileName);
    if (!isPresent)
    {
        setFileName(std::filesystem::absolute(fileName));
        cacheBuffer.emplace_back(cache_info(fileName, loadMatrix()));
        return cacheBuffer.at(cacheBuffer.size() - 1).slave_data;
    }
    else
    {
        return cacheBuffer.at(where).slave_data;
    }
}

void FileLoader::clear_cache()
{

    if(!cacheBuffer.empty())
    {
        cacheBuffer.clear();
    }
}