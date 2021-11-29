// Meshing for 2D
#ifndef MESH2D_H_
#define MESH2D_H_
#include <iostream>
#include <array>
#include <utility>
#include <valarray>
#include <vector>

#include "mesh.h"

struct Edge;
struct Elem;
struct Node;

class Mesh2D : public Mesh {

public:
    Mesh2D(int n_row, int n_col, double x0, double x1, double y0, double y1); 
    ~Mesh2D();                     

    int dim();
    int n_elements();
    int n_interfaces(); 
    // double el_volume(int element);  // TO DO

    std::vector<Node> get_NodeVector();

private:

    static const int dimen_ = 2; // Space dimension

    // The number of rows and columns for Elements.
    int Elem_row_;   
    int Elem_col_;  

    // The number of Nodes, including nodes for ghost and corner cells.
    int Node_row_;   
    int Node_col_; 
    int Num_Nodes_;  

    // The number of Elements and Edges.
    int Num_Elems_;  
    int Num_Edges_; 

    /* ----------------------------- The domain ----------------------------- */
    double x0_;
    double x1_;
    double y0_;
    double y1_;

    /* --------------------------- Useful vectors --------------------------- */
    std::vector<Node> node_vect;
    std::vector<Elem> elem_vect;
    std::vector<Edge> edge_vect;

    std::valarray<double> element_volume;
    std::vector<unsigned int> ghost_elements;

    /* ---- Functions to construct node_vect, elem_vect and edge_vect. ---- */
    void define_NodeVector();

};

#endif  // MESH2D_H_