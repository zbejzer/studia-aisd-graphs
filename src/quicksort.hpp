#pragma once

#include <utility>
#include <cstdio>

int compareULInt(const unsigned long int *a, const unsigned long int *b)
{
    if (*a > *b)
    {
        return -1;
    }
    else if (*a == *b)
    {
        return 0;
    }

    return 1;
}

template <typename T>
void quickSort(T arr[], unsigned long int start, unsigned long int end, int (*compar)(const T *, const T *))
{
    if (start < end)
    {
        T pivot = arr[(start + end) / 2];
        unsigned long int i = start, j = end;

        while (i <= j)
        {
            while (compar(&arr[i], &pivot) < 0)
            {
                ++i;
            }

            while (compar(&arr[j], &pivot) > 0)
            {
                --j;
            }

            if (i <= j)
            {
                std::swap(arr[i], arr[j]);
                if (i < end)
                {
                    ++i;
                }
                if (j > start)
                {
                    --j;
                }
            }
        }

        quickSort(arr, start, j, compar);
        quickSort(arr, i, end, compar);
    }

    return;
}