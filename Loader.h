#include "Matrix.h"
#include "fstream"


class Loader {
public:
    Loader(){};
    Matrix ConsoleLoader();
    Matrix FileLoader(const std::filesystem::path& file_name);
private:
    size_t load_rows;
    size_t load_columns;

};

