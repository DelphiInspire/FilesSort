#include"Matrix.h"

class Sorter
{
public:
    void quickSort(Matrix* sort_array, int low_element, int high_element);
    void bubbleSort(Matrix* sort_array, size_t size);
    void shellSort(Matrix* array, size_t size);
private:
    int partition(Matrix* array, int low, int high);
    static std::tuple<float, float> GetComparisonValues(Matrix* lcomp, Matrix* rcomp);
    static void swap(Matrix* input_1, Matrix* input_2);
    static void try_shift_value(Matrix* array, size_t position, size_t interval);
};


