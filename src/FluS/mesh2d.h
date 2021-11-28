#ifndef MESH2D_H_
#define MESH2D_H_

#include <iostream>
#include <valarray>
#include <array>
#include <vector>
#include <utility>
// using std::vector;

#include "mesh.h"

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
    std::array<double,2> position;
};

class Mesh2D : public Mesh {

public:
    Mesh2D(int n_row, int n_col, double x0, double x1, double y0, double y1);  // Constructor
    ~Mesh2D();                     // Destructor      

    int dim();

    int n_elements();

    int n_interfaces(); 

    // double el_volume(int element);  // TO DO

    std::vector<Node> get_NodeVector();


private:

    static const int dimen_ = 2; // Space dimension

    int Elem_row_;  // The number of rows and columns for Elements
    int Elem_col_;  

    int Node_row_;  // The number of rows and columns for Nodes
    int Node_col_;  

    int Num_Elems_;  // The number of Elements, Nodes and Edges.
    int Num_Nodes_;  
    int Num_Edges_;  

    double x0_;
    double x1_;
    double y0_;
    double y1_;

    std::valarray<double> element_volume;

    std::vector<Edge> edge_vect;
    std::vector<Elem> elem_vect;
    std::vector<Node> node_vect;

    std::vector<unsigned int> ghost_elements;

    void define_NodeVector();

};

#endif  // MESH2D_H_