#include "Sorter.h"

void Sorter::swap(Matrix *input_1, Matrix *input_2) {
    Matrix buffer = *input_1;
    *input_1 = *input_2;
    *input_2 = buffer;
}

std::tuple<float, float> Sorter::GetComparisonValues(Matrix *lcomp, Matrix *rcomp)
{
    float lDiagonalsSum{lcomp->getSumDiagonalsResult()};
    float rDiagonalsSum{rcomp->getSumDiagonalsResult()};
    float lTraceSum{lcomp->getMajorDiagonalSum()};
    float rTraceSum{rcomp->getMajorDiagonalSum()};
    //choose the way to comparison
    if (lDiagonalsSum != rDiagonalsSum) {
        return std::make_tuple(lDiagonalsSum, rDiagonalsSum);
    }
    else
    {
        return std::make_tuple(lTraceSum, rTraceSum);
    }
}

int Sorter::partition(Matrix *array, int low, int high)
{
    int position = low - 1;
    for (size_t i = low; i < high; ++i) {
        //choose the way to comparison
        auto [step_comparator, pivot] = GetComparisonValues(&array[i], &array[high]);
        //rearranging array
        if (step_comparator <= pivot)
        {
            position++;
            swap(&array[position], &array[i]);
        }
    }
    swap(&array[position + 1], &array[high]);
    return (position + 1);
}

void Sorter::try_shift_value(Matrix* array, size_t position, size_t interval)
{
    for (int left_counter = position - interval, right_counter = position; left_counter >= 0; right_counter = left_counter, left_counter -= interval)
    {
        auto [left_Matrix, right_Matrix] = GetComparisonValues(&array[left_counter], &array[right_counter]);
        if(right_Matrix <= left_Matrix)
        {
            swap(&array[right_counter], &array[left_counter]);
        }
    }
}


void Sorter::quickSort(Matrix *sort_array, int low_element, int high_element) {
    if (low_element < high_element) {
        int pi = partition(sort_array, low_element, high_element);
        //low_case
        quickSort(sort_array, low_element, pi - 1);
        //greater_case
        quickSort(sort_array, pi + 1, high_element);
    }
}

void Sorter::bubbleSort(Matrix *sort_array, size_t size) {

    bool complete{true};
    for (size_t counter = 0; counter < size - 1; counter++) {
        auto [l_member, r_member] = GetComparisonValues(&sort_array[counter], &sort_array[counter + 1]);
        if (l_member >= r_member) {
            complete = false;
            swap(&sort_array[counter], &sort_array[counter + 1]);
        }
    }
    if (!complete) {
        bubbleSort(sort_array, size - 1);
    }
}

void Sorter::shellSort(Matrix* array, size_t size) {
    constexpr size_t step_modificator{2};
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
            auto [left_Matrix, right_Matrix] = GetComparisonValues(&array[left_counter], &array[right_counter]);
            if (left_Matrix >= right_Matrix)
            {
                try_shift_value(array, right_counter, interval);
            }
        }
        interval = static_cast<size_t>(interval / step_modificator);
    }
}