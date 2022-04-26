#include "Matrix.h"
#include "fstream"
#include <vector>
#include<map>

class Loader
{
public:
    virtual Matrix loadMatrix() = 0;
    virtual void clear_cash() = 0;
    virtual std::vector<cash_info> getCash() = 0;
protected:
    static std::tuple<bool, size_t> isInCash(const std::vector<cash_info>&, const std::string& name);
};

class ConsoleLoader: public Loader
{
public:
    Matrix loadMatrix() override;
    std::vector<cash_info> getCash() override {return cashBuffer;};
    void clear_cash() override;
private:
    std::vector<cash_info> cashBuffer;
};

class FileLoader: Loader
{
public:
    Matrix loadMatrix() override;
    Matrix loadMatrix(const std::string& fileName);
    std::vector<cash_info> getCash() override {return cashBuffer;};
    void clear_cash() override;
private:
    void setFileName(const std::string& file_name){path = std::filesystem::absolute(file_name);};
private:
    std::vector<cash_info> cashBuffer;
    std::filesystem::path path;
    std::ifstream read_thread;
};





