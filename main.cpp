#include "Sorter.h"

int main()
{
    FileLoader ld;
    ld.loadMatrix("dataMatrix_2.txt");
    ld.loadMatrix("dataMatrix_1.txt");
    std::vector<cache_info> savedMatrices{ld.getCache()};
    QuickSort qSort;
    BubbleSort bSort;
    ShellSort sSort;
    qSort.sort(savedMatrices);
    return 0;
}
