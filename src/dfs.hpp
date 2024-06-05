#pragma once
#include "vertex.hpp"

// Marks visited elements in the bool array
// The bool array needs to be at least the size of count of all elements that can be accessed
void depthFirstSearch(bool *visited, Vertex *root)
{
    if (!visited[root->number])
    {
        visited[root->number] = true;

        for (unsigned long int i = 0; i < root->neighbours_count; i++)
        {
            depthFirstSearch(visited, root->neighbours[i]);
        }
    }

    return;
}

// Marks visited elements in the bool array and colours them
// The bool array needs to be at least the size of count of all elements that can be accessed
bool bipartiteDfs(bool *visited, Vertex *root, char desired_colour)
{
    if (!visited[root->number])
    {
        visited[root->number] = true;
        root->colour = desired_colour;

        for (unsigned long int i = 0; i < root->neighbours_count; i++)
        {
            if (!bipartiteDfs(visited, root->neighbours[i], 1 - desired_colour))
            {
                return false;
            }
        }
    }
    else if (static_cast<int>(root->colour) != desired_colour)
    {
        return false;
    }

    return true;
}