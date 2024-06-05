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

void Graph::printGreedyColours() const
{
    // TODO optimize by creating used colors in Graph class
    bool *used_colours = static_cast<bool *>(malloc(sizeof(bool) * vertices_count));
    for (unsigned long int i = 0; i < vertices_count; i++)
    {
        vertices[i].colour = 0;
    }
    for (unsigned long int i = 0; i < vertices_count; i++)
    {
        vertices[i].findFreeColour(used_colours);
        printf("%lu ", vertices[i].colour);
    }
    free(used_colours);
    printf("\n");

    return;
}

void Graph::printLFColours() const
{
    // TODO optimize
    for (unsigned long int i = 0; i < vertices_count; i++)
    {
        vertices[i].colour = 0;
    }

    Vertex **sorted_vertices = static_cast<Vertex **>(malloc(sizeof(Vertex *) * vertices_count));
    for (unsigned long int i = 0; i < vertices_count; i++)
    {
        #pragma warning(suppress : 6011)
        sorted_vertices[i] = &vertices[i];
    }
    quickSort<Vertex *>(sorted_vertices, 0, vertices_count - 1, compareVerticesPointersByDegree);

    bool *used_colours = static_cast<bool *>(malloc(sizeof(bool) * vertices_count));
    for (unsigned long int i = 0; i < vertices_count; i++)
    {
        sorted_vertices[i]->findFreeColour(used_colours);
    }
    free(sorted_vertices);
    free(used_colours);

    for (unsigned long int i = 0; i < vertices_count; i++)
    {
        printf("%lu ", vertices[i].colour);
    }
    printf("\n");

    return;
}

void Graph::printSLFColours() const
{
    // TODO optimize
    for (unsigned long int i = 0; i < vertices_count; i++)
    {
        vertices[i].colour = 0;
    }

    /*Vertex **sorted_vertices = static_cast<Vertex **>(malloc(sizeof(Vertex *) * vertices_count));
    for (unsigned long int i = 0; i < vertices_count; i++)
    {
        #pragma warning(suppress : 6011)
        sorted_vertices[i] = &vertices[i];
    }
    quickSort<Vertex *>(sorted_vertices, 0, vertices_count - 1, compareVerticesPointersByDegreeAsc);*/

    bool *used_colours = static_cast<bool *>(malloc(sizeof(bool) * vertices_count));

    for (unsigned long int i = 0; i < vertices_count; i++)
    {
        Vertex *selected_vertex = nullptr;
        //unsigned long int highest_saturation_i = 0;
        unsigned long int highest_saturation = 0;

        // finding uncoloured vertex with highest saturation 
        for (unsigned long int j = 0; j < vertices_count; j++)
        {
            if (vertices[j].colour == 0)
            {
                unsigned long int current_saturation = vertices[j].getSaturationDegree(vertices_count);
                if (current_saturation > highest_saturation || selected_vertex == nullptr)
                {
                    selected_vertex = &vertices[j];
                    highest_saturation = current_saturation;
                }
                else if (current_saturation == highest_saturation)
                {
                    if (vertices[j].neighbours_count > selected_vertex->neighbours_count)
                    {
                        selected_vertex = &vertices[j];
                        highest_saturation = current_saturation;
                    }
                    else if (vertices[j].neighbours_count == selected_vertex->neighbours_count)
                    {
                        if (j < selected_vertex->number)
                        {
                            selected_vertex = &vertices[j];
                            highest_saturation = current_saturation;
                        }
                    }
                }
            }
        }

        selected_vertex->findFreeColour(used_colours);
        //printf("%lu ", selected_vertex->number);
    }
    //printf("\n");
    //free(sorted_vertices);
    free(used_colours);

    for (unsigned long int i = 0; i < vertices_count; i++)
    {
        printf("%lu ", vertices[i].colour);
    }
    printf("\n");

    return;
}

Graph Graph::operator=(Graph other)
{
    std::swap(vertices_count, other.vertices_count);
    std::swap(vertices, other.vertices);
    return *this;
}
