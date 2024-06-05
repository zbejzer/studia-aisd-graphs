#include "bfs.hpp"
#include "dfs.hpp"
#include "graph.hpp"
#include "quicksort.hpp"
#include "vertex.hpp"

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
#pragma warning(suppress : 6011)
        if (!visited[i])
        {
            components_count++;
            depthFirstSearch(visited, &vertices[i]);
        }
    }

    free(visited);
    printf("%lu\n", components_count);

    return;
}

void Graph::printBipartiteness()
{
    bool is_bipartite = true;
    bool *visited = static_cast<bool *>(calloc(sizeof(bool), vertices_count));

    for (unsigned long int i = 0; i < vertices_count && is_bipartite; i++)
    {
#pragma warning(suppress : 6011)
        if (!visited[i])
        {
            is_bipartite = bipartiteDfs(visited, &vertices[i], 0);
        }
    }

    free(visited);

    if (is_bipartite)
    {
        printf("T\n");
    }
    else
    {
        printf("F\n");
    }

    return;
}

void Graph::printEccentricity() const
{
    bool *visited = static_cast<bool *>(malloc(sizeof(bool) * vertices_count));

    for (unsigned long int i = 0; i < vertices_count; i++)
    {
        #pragma warning(suppress : 6387)
        memset(visited, 0, sizeof(bool) * vertices_count);

        printf("%llu ", depthBfs(visited, &vertices[i]));
    }
    printf("\n");

    free(visited);

    return;
}

void Graph::printPlanarity() const
{
    // TODO implement planarity test
    printf("?\n");
}

Graph Graph::operator=(Graph other)
{
    std::swap(vertices_count, other.vertices_count);
    std::swap(vertices, other.vertices);
    return *this;
}
