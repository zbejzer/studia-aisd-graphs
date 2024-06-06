#pragma once

class Vertex
{
  public:
    unsigned long int number;
    unsigned long int colour;
    unsigned long int saturation;
    unsigned long int neighbours_count;
    Vertex **neighbours;

    Vertex();
    Vertex(const unsigned long int number, const unsigned long int neighbours_count);
    Vertex(const Vertex &other);
    ~Vertex();

    void debugPrintShort() const;
    void setFreeColour(bool *used_colours);
    unsigned long int getSaturationDegree(bool *used_colours, const unsigned long int &max_vertices) const;

    Vertex operator=(Vertex other);
};
