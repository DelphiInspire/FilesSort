#include"Matrix.h"

class Sorter
{
public:
    virtual void sort(std::vector<cash_info>& sortList) = 0;
protected:
    static std::tuple<float, float> GetComparisonValues(const Matrix& lcomp, const Matrix& rcomp);
    static void try_shift_value(std::vector<cash_info>& array, size_t position, size_t interval);
    static void swap(cash_info* input_1, cash_info* input_2);
};

class QuickSort: public Sorter
{
public:
    void sort(std::vector<cash_info>& sortList) override;
private:
    void Qsort(std::vector<cash_info>& sortList, int low, int high);
    int partition(std::vector<cash_info>& arrangeList, int low, int high);
private:
    int startListPos;
    int stopListPos;
};

class BubbleSort: public Sorter
{
public:
    void sort(std::vector<cash_info>& sortList) override;
};

class ShellSort: public Sorter
{
public:
    void sort(std::vector<cash_info>& sortList) override;
};

