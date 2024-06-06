#pragma once
#include "vertex.hpp"

// Marks visited elements in the bool array and colours them
// The bool array needs to be at least the size of count of all elements that can be accessed
void bipartiteDfs(bool *visited, Vertex *root, char desired_colour, bool *is_bipartite)
{
    if (!visited[root->number])
    {
        visited[root->number] = true;
        root->colour = desired_colour;

        for (unsigned long int i = 0; i < root->neighbours_count; i++)
        {
            bipartiteDfs(visited, root->neighbours[i], 1 - desired_colour, is_bipartite);
        }
    }
    else if (static_cast<int>(root->colour) != desired_colour)
    {
        *is_bipartite = false;
    }
}