#pragma once

class Vertex
{
  public:
    unsigned long int number;
    unsigned long int colour;
    unsigned long int neighbours_count;
    Vertex **neighbours;

    Vertex();
    Vertex(const unsigned long int number, const unsigned long int neighbours_count);
    Vertex(const Vertex &other);
    ~Vertex();

    void debugPrintShort();

    Vertex operator=(Vertex other);
};
