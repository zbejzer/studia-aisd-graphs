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
    void printVerticesColours() const;
    void printDegreeSequence() const;
    void printComponentsCountAndBipartiteness() const;
    void printEccentricity() const;
    void printPlanarity() const;
    void printGreedyColours() const;
    void printLFColours() const;
    void printSLFColours() const;

    Graph operator=(Graph other);
};
