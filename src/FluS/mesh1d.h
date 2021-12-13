// Based on https://github.com/Tal-Rubin/FluS/blob/Tal/src/mocks/mesh_mock.h
#ifndef MESH1D_H_
#define MESH1D_H_
#include <iostream>
#include <array>
#include <utility>
#include <valarray>
#include <vector>

#include "mesh.h"

class Mesh1D : public Mesh {

public:
    /* ------------------- Constructor and Deconstructor ------------------- */
    Mesh1D(int num_Elems, double x0, double x1); 
    ~Mesh1D();          

    /* ---------------- Functions to get useful properties ---------------- */
    int dim();
    int n_elements();
    int n_interfaces();
    double el_volume(int element); 
    
    /* ------- Functions to get node_vect, elem_vect and edge_vect. ------- */
    std::vector<Node> get_NodeVector();
    std::vector<Edge> get_EdgeVector();
    std::vector<Elem> get_ElemVector();

private:

    static const int dimen_ = 1; // Space dimension 

    // The number of Elements and Edges.
    int Num_Elems_;  
    int Num_Edges_;

    // The number of Nodes, including those in ghost cells.
    int Num_Nodes_; 

    /* ----------------------------- The domain ----------------------------- */
    double x0_;
    double x1_;
    double dx_;

    /* --------------------------- Useful vectors --------------------------- */
    std::vector<Node> node_vect;
    std::vector<Elem> elem_vect;
    std::vector<Edge> edge_vect;
    // std::valarray<double> element_volume;
    std::vector<unsigned int> ghost_elements;

    /* ---- Functions to construct node_vect, elem_vect and edge_vect. ---- */
    void define_NodeVector();
    void define_ElemVector();
    void define_EdgeVector();
    
};

#endif  // MESH1D_H_