#include "vertex.hpp"

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <utility>

Vertex::Vertex() : number(0), colour(0), neighbours_count(0), neighbours(nullptr)
{
}

Vertex::Vertex(const unsigned long int number, const unsigned long int neighbours_count)
    : number(number), colour(0), neighbours_count(neighbours_count)
{
    if (neighbours_count > 0)
    {
        neighbours = static_cast<Vertex **>(malloc(sizeof(Vertex *) * neighbours_count));
    }
    else
    {
        neighbours = nullptr;
    }
}

Vertex::Vertex(const Vertex &other)
    : number(other.number), colour(other.colour), neighbours_count(other.neighbours_count)
{
    if (neighbours_count > 0)
    {
        neighbours = static_cast<Vertex **>(malloc(sizeof(Vertex *) * neighbours_count));
        #pragma warning(suppress : 6387)
        memcpy(neighbours, other.neighbours, sizeof(Vertex *) * neighbours_count);
    }
    else
    {
        neighbours = nullptr;
    }
}

Vertex::~Vertex()
{
    free(neighbours);
}

void Vertex::debugPrintShort()
{
    printf("ID: %lu; Colour: %lu; Neighbours: %lu", number, colour, neighbours_count);
}

Vertex Vertex::operator=(Vertex other)
{
    std::swap(number, other.number);
    std::swap(colour, other.colour);
    std::swap(neighbours_count, other.neighbours_count);
    std::swap(neighbours, other.neighbours);
    return *this;
}

