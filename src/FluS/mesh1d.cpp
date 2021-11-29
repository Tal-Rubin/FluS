// Based on https://github.com/Tal-Rubin/FluS/blob/Tal/src/mocks/mesh_mock.h
#include <iostream>
#include <vector>

#include "mesh1d.h"

struct Edge {
    unsigned int edge_number;
    std::pair<unsigned int, unsigned int> neighbor_elements;
    std::valarray<double> unit_vector;
};

struct Elem {
    unsigned int elem_number;
    std::array<unsigned int,2> nodes;
    double volume;
    bool ghost;
};

struct Node {
    unsigned int node_number;
    std::array<double,1> position;
};
Mesh1D::Mesh1D(int num_Elems, double x0, double x1)
    :Num_Elems(num_Elems),x0_(x0), x1_(x1)
{
    }

