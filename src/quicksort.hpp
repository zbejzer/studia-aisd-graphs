#pragma once

#include "vertex.hpp"

#include <utility>

int compareVerticesPointersByDegreeAsc(Vertex *const &a, Vertex *const &b)
{
    if (a->neighbours_count < b->neighbours_count)
    {
        return -1;
    }
    else if (a->neighbours_count == b->neighbours_count)
    {
        if (a->number > b->number)
        {
            return -1;
        }
        else if (a->number == b->number)
        {
            return 0;
        }
    }

    return 1;
}

int compareVerticesPointersByDegree(Vertex *const &a, Vertex *const &b)
{
    if (a->neighbours_count > b->neighbours_count)
    {
        return -1;
    }
    else if (a->neighbours_count == b->neighbours_count)
    {
        if (a->number < b->number)
        {
            return -1;
        }
        else if (a->number == b->number)
        {
            return 0;
        }
    }

    return 1;
}

int compareULInt(unsigned long int const &a, unsigned long int const &b)
{
    if (a > b)
    {
        return -1;
    }
    else if (a == b)
    {
        return 0;
    }

    return 1;
}

template <typename T>
void quickSort(T arr[], unsigned long int start, unsigned long int end, int (*compar)(T const &, T const &))
{
    if (start < end)
    {
        T pivot = arr[(start + end) / 2];
        unsigned long int i = start, j = end;

        while (i <= j)
        {
            while (compar(arr[i], pivot) < 0)
            {
                ++i;
            }

            while (compar(arr[j], pivot) > 0)
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