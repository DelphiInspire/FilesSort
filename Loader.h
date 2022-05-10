#include "Matrix.h"
#include "fstream"
#include <vector>
#include<map>
#include "filesystem"

struct cache_info
{
    cache_info(std::string name, Matrix inMatrix): owner_id{std::move(name)}, slave_data{std::move(inMatrix)}{};
    std::string owner_id;
    Matrix slave_data;
};

class ILoader
{
public:
    virtual Matrix loadMatrix() = 0;
    virtual void clear_cache() = 0;
    virtual std::vector<cache_info> getCache() const = 0;
protected:
    virtual std::tuple<bool, size_t> isInCache(const std::vector<cache_info>&, const std::string& name);
public:
    virtual ~ILoader(){};
};

class ConsoleLoader: public ILoader
{
public:
    Matrix loadMatrix() override;
    std::vector<cache_info> getCache() const override {return cacheBuffer;};
    void clear_cache() override;
private:
    std::vector<cache_info> cacheBuffer;
};

class FileLoader: ILoader
{
public:
    Matrix loadMatrix() override;
    Matrix loadMatrix(const std::string& fileName);
    std::vector<cache_info> getCache() const override {return cacheBuffer;};
    void clear_cache() override;
private:
    void setFileName(const std::string& file_name){path = std::filesystem::absolute(file_name);};
private:
    std::vector<cache_info> cacheBuffer;
    std::filesystem::path path;
};





