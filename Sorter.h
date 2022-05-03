#include"Matrix.h"
#include"Loader.h"
class ISorter
{
public:
    virtual void sort(std::vector<cache_info>& sortList) = 0;
protected:
    virtual std::tuple<float, float> GetComparisonValues(const Matrix& lcomp, const Matrix& rcomp) const;
    virtual void try_shift_value(std::vector<cache_info>& array, size_t position, size_t interval);
    virtual void swap(cache_info* input_1, cache_info* input_2);
public:
    virtual ~ISorter(){};
};

class QuickSort: public ISorter
{
public:
    void sort(std::vector<cache_info>& sortList) override;
private:
    void Qsort(std::vector<cache_info>& sortList, int low, int high);
    int partition(std::vector<cache_info>& arrangeList, int low, int high);
private:
    int startListPos;
    int stopListPos;
};

class BubbleSort: public ISorter
{
public:
    void sort(std::vector<cache_info>& sortList) override;
};

class ShellSort: public ISorter
{
public:
    void sort(std::vector<cache_info>& sortList) override;
};

