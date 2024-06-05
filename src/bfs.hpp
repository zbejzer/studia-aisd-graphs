#pragma once

#include "queue.hpp"
#include "vertex.hpp"

// Marks visited elements in the bool array and returns the maximum distance to the 
// The bool array needs to be at least the size of count of all elements that can be accessed
unsigned long long int depthBfs(bool *visited, Vertex *root)
{
    Queue<Vertex *> q;
    unsigned long long int depth = 0;

    visited[root->number] = true;
    q.push(root);
    
    while (!q.empty())
    {
        unsigned long long int level_size = q.size();
        depth++;

        while (level_size > 0)
        {
            level_size--;
            root = q.front();
            q.pop();

            for (unsigned long int i = 0; i < root->neighbours_count; i++)
            {
                if (!visited[root->neighbours[i]->number])
                {
                    visited[root->neighbours[i]->number] = true;
                    q.push(root->neighbours[i]);
                }
            }
        }
    }

    return depth - 1;
}