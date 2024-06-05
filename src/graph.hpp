#pragma once

#include "vertex.hpp"

class Graph
{
  public:
    unsigned long int vertices_count;
    Vertex *vertices;

    Graph();
    Graph(const unsigned long int vertices_count);
    Graph(const Graph &other);
    ~Graph();

    void debugPrintVertices() const;
    void printDegreeSequence() const;
    void printComponentsCount() const;
    void printBipartiteness();
    void printEccentricity() const;
    void printPlanarity() const;

    Graph operator=(Graph other);
};
