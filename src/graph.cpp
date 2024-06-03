#include "graph.hpp"

#include <cstdlib>
#include <cstdio>
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

void Graph::debugPrintVertices()
{
    for (unsigned long int i = 0; i < vertices_count; i++)
    {
        vertices[i].debugPrintShort();
        printf("\n");
    }
}

Graph Graph::operator=(Graph other)
{
    std::swap(vertices_count, other.vertices_count);
    std::swap(vertices, other.vertices);
    return *this;
}
