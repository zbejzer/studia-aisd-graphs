#include <cstdio>
#include <new>

#include "graph.hpp"
#include "vertex.hpp"

using namespace std;

int main()
{
    unsigned int graphs_count;
    static_cast<void>(scanf("%u", &graphs_count));
    for (unsigned int g = 0; g < graphs_count; g++)
    {
        unsigned long int vertices_count;
        static_cast<void>(scanf("%lu", &vertices_count));
        Graph graph(vertices_count);
        for (unsigned long int v = 0; v < vertices_count; v++)
        {
            unsigned long int neighbours_count;
            static_cast<void>(scanf("%lu", &neighbours_count));
            new (&graph.vertices[v]) Vertex(v, neighbours_count);
            for (unsigned long int n = 0; n < neighbours_count; n++)
            {
                unsigned long int neighbour_num;
                static_cast<void>(scanf("%lu", &neighbour_num));
                graph.vertices[v].neighbours[n] = &graph.vertices[neighbour_num - 1];
            }
        }
        graph.printDegreeSequence();
        graph.printComponentsCount();
        //graph.debugPrintVertices();
        for (size_t i = 0; i < 8; i++)
        {
            printf("?\n");
        }
    }

    return 0;
}