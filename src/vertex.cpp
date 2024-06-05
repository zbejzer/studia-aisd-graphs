#include "vertex.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>

Vertex::Vertex() : number(0), colour(0), saturation(0), neighbours_count(0), neighbours(nullptr)
{
}

Vertex::Vertex(const unsigned long int number, const unsigned long int neighbours_count)
    : number(number), colour(0), saturation(0), neighbours_count(neighbours_count)
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

void Vertex::debugPrintShort() const
{
    printf("ID: %lu; Colour: %lu; Neighbours: %lu", number, colour, neighbours_count);
}

// The bool array needs to be at least the size of count of all vertices in given graph
void Vertex::findFreeColour(bool *used_colours)
{
    if (neighbours_count > 0)
    {
        #pragma warning(suppress : 6387)
        // zeroing used colours including the one past the neigbours count that's guaranteed to be free
        memset(used_colours, 0, sizeof(bool) * neighbours_count + 1);
        for (unsigned long int i = 0; i < neighbours_count; i++)
        {
            // colour == 0 means that its colour is unset
            if (neighbours[i]->colour != 0)
            {
                #pragma warning(suppress : 6011)
                // colours are numerated starting with 1, so we need to offset the colour
                used_colours[neighbours[i]->colour - 1] = true;
            }
        }
        for (unsigned long int i = 0; i < neighbours_count + 1; i++)
        {
            #pragma warning(suppress : 6385)
            if (!used_colours[i])
            {
                colour = i + 1;
                break;
            }
        }
    }
    else
    {
        colour = 1;
    }

    return;
}

unsigned long int Vertex::getSaturationDegree(unsigned long int max_vertices) const
{
    unsigned long int saturation_degree = 0;
    bool *used_colours = static_cast<bool *>(calloc(max_vertices, sizeof(bool)));

    for (unsigned long int i = 0; i < neighbours_count; i++)
    {
        if (neighbours[i]->colour != 0 && !used_colours[neighbours[i]->colour - 1])
        {
            saturation_degree++;
            used_colours[neighbours[i]->colour - 1] = true;
        }
    }

    return saturation_degree;
}

Vertex Vertex::operator=(Vertex other)
{
    std::swap(number, other.number);
    std::swap(colour, other.colour);
    std::swap(neighbours_count, other.neighbours_count);
    std::swap(neighbours, other.neighbours);
    return *this;
}

