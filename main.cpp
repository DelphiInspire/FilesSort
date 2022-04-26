#include "Loader.h"
#include "Sorter.h"

int main()
{
    FileLoader ld;
    ld.loadMatrix("dataMatrix_2.txt");
    ld.loadMatrix("dataMatrix_1.txt");
    std::vector<cash_info> savedMatrices{ld.getCash()};
    QuickSort qSort;
    BubbleSort bSort;
    ShellSort sSort;
    qSort.sort(savedMatrices);
    return 0;
}
