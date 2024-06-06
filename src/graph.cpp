#include "bipartite_dfs.hpp"
#include "depth_bfs.hpp"
#include "graph.hpp"
#include "quicksort.hpp"
#include "subgraphs_dfs.hpp"
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

void Graph::printVerticesColours() const
{
    for (unsigned long int i = 0; i < vertices_count; i++)
    {
        printf("%lu ", vertices[i].colour);
    }
    printf("\n");
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

void Graph::printComponentsCountAndBipartiteness() const
{
    unsigned long int components_count = 0;
    bool is_bipartite = true;
    bool *visited = static_cast<bool *>(calloc(sizeof(bool), vertices_count));

    for (unsigned long int i = 0; i < vertices_count; i++)
    {
#pragma warning(suppress : 6011)
        if (!visited[i])
        {
            components_count++;
            bipartiteDfs(visited, &vertices[i], 0, &is_bipartite);
        }
    }

    free(visited);
    printf("%lu\n", components_count);
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

void Graph::printGreedyColours()
{
    bool *used_colours = static_cast<bool *>(malloc(sizeof(bool) * vertices_count));
    for (unsigned long int i = 0; i < vertices_count; i++)
    {
        vertices[i].colour = 0;
    }
    for (unsigned long int i = 0; i < vertices_count; i++)
    {
        vertices[i].setFreeColour(used_colours);
        printf("%lu ", vertices[i].colour);
    }
    free(used_colours);
    printf("\n");

    return;
}

void Graph::printLFColours()
{
    Vertex **sorted_vertices = static_cast<Vertex **>(malloc(sizeof(Vertex *) * vertices_count));
    for (unsigned long int i = 0; i < vertices_count; i++)
    {
#pragma warning(suppress : 6011)
        sorted_vertices[i] = &vertices[i];
        vertices[i].colour = 0;
    }
    quickSort<Vertex *>(sorted_vertices, 0, vertices_count - 1, compareVerticesPointersByDegree);

    bool *used_colours = static_cast<bool *>(malloc(sizeof(bool) * vertices_count));
    for (unsigned long int i = 0; i < vertices_count; i++)
    {
        sorted_vertices[i]->setFreeColour(used_colours);
    }
    free(sorted_vertices);
    free(used_colours);

    printVerticesColours();

    return;
}

void Graph::printSLFColours()
{
    for (unsigned long int i = 0; i < vertices_count; i++)
    {
        vertices[i].colour = 0;
    }

    bool *used_colours = static_cast<bool *>(malloc(sizeof(bool) * vertices_count));
    bool *saturation_used_colours = static_cast<bool *>(malloc(sizeof(bool) * vertices_count));
    for (unsigned long int i = 0; i < vertices_count; i++)
    {
        Vertex *selected_vertex = nullptr;
        // unsigned long int highest_saturation_i = 0;
        unsigned long int highest_saturation = 0;

        // finding uncoloured vertex with highest saturation
        for (unsigned long int j = 0; j < vertices_count; j++)
        {
            if (vertices[j].colour == 0)
            {
                unsigned long int current_saturation =
                    vertices[j].getSaturationDegree(saturation_used_colours, vertices_count);
                if (selected_vertex == nullptr || current_saturation > highest_saturation ||
                    (current_saturation == highest_saturation &&
                     (vertices[j].neighbours_count > selected_vertex->neighbours_count ||
                      (vertices[j].neighbours_count == selected_vertex->neighbours_count &&
                       j < selected_vertex->number))))
                {
                    selected_vertex = &vertices[j];
                    highest_saturation = current_saturation;
                }
            }
        }

        selected_vertex->setFreeColour(used_colours);
    }

    free(used_colours);
    free(saturation_used_colours);

    printVerticesColours();

    return;
}

void Graph::printC4SubgraphsCount() const
{
    unsigned long long int subgraphs_sum = 0;

    for (unsigned long int i = 0; i < vertices_count; i++)
    {
        subgraphsDfs(&vertices[i], nullptr, &vertices[i], 0, &subgraphs_sum);
    }

    printf("%llu\n", subgraphs_sum / 8);

    return;
}

void Graph::printComplementEdgesCount() const
{
    unsigned long long int edges_count = 0;

    for (unsigned long int i = 0; i < vertices_count; i++)
    {
        edges_count += vertices[i].neighbours_count;
    }

    edges_count /= 2;

    printf("%llu\n", (vertices_count * (vertices_count - 1) / 2) - edges_count);

    return;
}

Graph Graph::operator=(Graph other)
{
    std::swap(vertices_count, other.vertices_count);
    std::swap(vertices, other.vertices);
    return *this;
}
