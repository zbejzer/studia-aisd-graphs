#pragma once
#include "vertex.hpp"

// Marks visited elements in the bool array and colours them
// The bool array needs to be at least the size of count of all elements that can be accessed
void subgraphsDfs(Vertex const *start, Vertex *parent, Vertex *root, unsigned char depth, unsigned long long int* subgraphs_sum)
{
    depth++;
    if (depth < 4)
    {
        for (unsigned long int i = 0; i < root->neighbours_count; i++)
        {
            if (root->neighbours[i] != parent)
            {
                subgraphsDfs(start, root, root->neighbours[i], depth, subgraphs_sum);
            }
        }
    }
    else
    {
        for (unsigned long int i = 0; i < root->neighbours_count; i++)
        {
            if (root->neighbours[i] == start)
            {
                (*subgraphs_sum)++;
            }
        }
    }

    return;
}