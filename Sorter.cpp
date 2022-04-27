#include "Sorter.h"

void Sorter::swap(cache_info *input_1, cache_info *input_2) {
    cache_info buffer = *input_1;
    *input_1 = *input_2;
    *input_2 = buffer;
}

void Sorter::try_shift_value(std::vector<cache_info>& sortList, size_t position, size_t interval)
{
    for (int left_counter = position - interval, right_counter = position; left_counter >= 0; right_counter = left_counter, left_counter -= interval)
    {
        auto [left_Matrix, right_Matrix] = GetComparisonValues(sortList.at(left_counter).slave_data,
                                                                            sortList.at(right_counter).slave_data);
        if(right_Matrix <= left_Matrix)
        {
            swap(&sortList.at(right_counter), &sortList.at(left_counter));
        }
    }
}

std::tuple<float, float> Sorter::GetComparisonValues(const Matrix& lcomp, const Matrix& rcomp)
{
    float lDiagonalsSum{lcomp.getSumDiagonalsResult()};
    float rDiagonalsSum{rcomp.getSumDiagonalsResult()};
    //choose the way to comparison
    if (lDiagonalsSum != rDiagonalsSum) {
        return std::make_tuple(lDiagonalsSum, rDiagonalsSum);
    }
    else
    {
        float lTraceSum{lcomp.getMajorDiagonalSum()};
        float rTraceSum{rcomp.getMajorDiagonalSum()};
        return std::make_tuple(lTraceSum, rTraceSum);
    }
}

int QuickSort::partition(std::vector<cache_info>& arrangeList, int low, int high)
{
    int position = low - 1;
    for (size_t i = low; i < high; ++i) {
        //choose the way to comparison
        auto [step_comparator, pivot] = GetComparisonValues(arrangeList.at(i).slave_data,
                                                                        arrangeList.at(high).slave_data);
        //rearranging array
        if (step_comparator <= pivot)
        {
            position++;
            swap(&arrangeList.at(position), &arrangeList.at(i));
        }
    }
    swap(&arrangeList.at(position + 1), &arrangeList.at(high));
    return (position + 1);
}

void QuickSort::sort(std::vector<cache_info> &sortList)
{
    startListPos = 0;
    stopListPos = sortList.size() - 1;
    Qsort(sortList, startListPos, stopListPos);
}

void QuickSort::Qsort(std::vector<cache_info> &sortList, int low, int high)
{
    if(low < high)
    {
        int pi = partition(sortList, low, high);
        Qsort(sortList, low, pi - 1);
        Qsort(sortList, pi + 1, high);
    }
}

void BubbleSort::sort(std::vector<cache_info>& sortList)
{
    size_t stop_pos{sortList.size()};
    for (size_t run_counter = 0; run_counter < stop_pos - 1; run_counter++)
    {
        for (size_t counter = 0; counter < stop_pos - run_counter - 1; counter++)
        {
            auto [l_member, r_member] = GetComparisonValues(sortList.at(counter).slave_data,
                                                            sortList.at(counter + 1).slave_data);
            if (l_member >= r_member)
            {
                swap(&sortList.at(counter), &sortList.at(counter + 1));
            }
        }
    }
}

void ShellSort::sort(std::vector<cache_info> &sortList)
{
    constexpr size_t step_modificator{2};
    size_t size{sortList.size()};
    size_t interval{static_cast<size_t>(size / step_modificator)};
    bool success_check_sort{false};
    while(!success_check_sort)
    {
        if(interval == 1)
        {
            success_check_sort = true;
        }
        for(size_t left_counter = 0, right_counter = interval;  right_counter < size; left_counter++, right_counter = left_counter + interval)
        {
            auto [left_Matrix, right_Matrix] = GetComparisonValues(sortList.at(left_counter).slave_data,
                                                                                sortList.at(right_counter).slave_data);
            if (left_Matrix >= right_Matrix)
            {
                try_shift_value(sortList, right_counter, interval);
            }
        }
        interval = static_cast<size_t>(interval / step_modificator);
    }
}

