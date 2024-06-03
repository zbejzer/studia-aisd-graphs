#pragma once
#include "vertex.hpp"

// Marks visited elements in the bool array
// The bool array needs to at least the size of count of all elements that can be accessed
void dfs(bool *visited, Vertex *root)
{
    if (!visited[root->number])
    {
        visited[root->number] = true;

        for (unsigned long int i = 0; i < root->neighbours_count; i++)
        {
            dfs(visited, root->neighbours[i]);
        }
    }

    return;
}