#include "graph.hpp"
#include "dfs.hpp"
#include "quicksort.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>

Graph::Graph() : vertices_count(0), vertices(nullptr)
{
}

// Create graph with specified number of vertices
// Warning: vertices in the created internal array are uninitialized
Graph::Graph(const unsigned long int vertices_count) : vertices_count(vertices_count)
{
    if (vertices_count > 0)
    {
        vertices = static_cast<Vertex *>(malloc(sizeof(Vertex) * vertices_count));
    }
    else
    {
        vertices = nullptr;
    }
}

Graph::Graph(const Graph &other) : vertices_count(other.vertices_count)
{
    if (vertices_count > 0)
    {
        vertices = static_cast<Vertex *>(malloc(sizeof(Vertex) * vertices_count));
#pragma warning(suppress : 6387)
        memcpy(vertices, other.vertices, sizeof(Vertex) * vertices_count);
    }
    else
    {
        vertices = nullptr;
    }
}

Graph::~Graph()
{
    for (unsigned long int i = 0; i < vertices_count; i++)
    {
        vertices[i].~Vertex();
    }
    free(vertices);
}

void Graph::debugPrintVertices() const
{
    for (unsigned long int i = 0; i < vertices_count; i++)
    {
        vertices[i].debugPrintShort();
        printf("\n");
    }
}

void Graph::printDegreeSequence() const
{
    unsigned long int *degree_sequence =
        static_cast<unsigned long int *>(malloc(sizeof(unsigned long int) * vertices_count));
    for (unsigned long int i = 0; i < vertices_count; i++)
    {
#pragma warning(suppress : 6011)
        degree_sequence[i] = vertices[i].neighbours_count;
    }

    quickSort<unsigned long int>(degree_sequence, 0, vertices_count - 1, compareULInt);

    for (unsigned long int i = 0; i < vertices_count; i++)
    {
        printf("%lu ", degree_sequence[i]);
    }
    printf("\n");

    free(degree_sequence);

    return;
}

void Graph::printComponentsCount() const
{
    unsigned long int components_count = 0;
    bool *visited = static_cast<bool *>(calloc(sizeof(bool), vertices_count));

    for (unsigned long int i = 0; i < vertices_count; i++)
    {
        if (!visited[i])
        {
            components_count++;
            dfs(visited, &vertices[i]);
        }
    }

    free(visited);
    printf("%lu\n", components_count);

    return;
}

Graph Graph::operator=(Graph other)
{
    std::swap(vertices_count, other.vertices_count);
    std::swap(vertices, other.vertices);
    return *this;
}
