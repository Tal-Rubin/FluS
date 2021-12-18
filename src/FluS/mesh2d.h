/**
 * @file mesh2d.h
 * @author Bingjia Yang, Kehan Cai
 * @brief 
 * @version 0.1
 * @date 2021-12-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// Meshing for 2D
#ifndef MESH2D_H_
#define MESH2D_H_
#include <iostream>
#include <array>
#include <utility>
#include <valarray>
#include <vector>

#include "mesh.h"

class Mesh2D : public Mesh {

public:
    /* ------------------- Constructor and Deconstructor ------------------- */
    Mesh2D(int n_row, int n_col, double x0, double x1, double y0, double y1); 
    ~Mesh2D();                     

    /* ---------------- Functions to get useful properties ---------------- */
    int dim();
    int n_elements();
    int n_interfaces(); 
    double el_volume(int element); 

    /* ------- Functions to get node_vect, elem_vect and edge_vect. ------- */
    std::vector<Node> get_NodeVector();
    std::vector<Elem> get_ElemVector();
    std::vector<Edge> get_HoriEdgeVector();
    std::vector<Edge> get_VertEdgeVector();

private:

    static const int dimen_ = 2; // Space dimension

    // The number of rows and columns for Elements.
    int Elem_row_;   
    int Elem_col_;  

    // The number of Elements and Edges.
    int Num_Elems_;  
    int Num_Edges_; 

    // The number of Nodes, including those in ghost and corner cells.
    int Node_row_;   
    int Node_col_; 
    int Num_Nodes_;  

    /* ----------------------------- The domain ----------------------------- */
    double x0_;
    double x1_;
    double y0_;
    double y1_;
    double dx_;
    double dy_;

    /* --------------------------- Useful vectors --------------------------- */
    std::vector<Node> node_vect;
    std::vector<Elem> elem_vect;
    std::vector<Edge> hori_edge_vect;
    std::vector<Edge> vert_edge_vect;
    // std::valarray<double> element_volume;
    std::vector<unsigned int> ghost_elements;
    std::vector<unsigned int> mega_ghost_elements;
    
    /* ---- Functions to construct node_vect, elem_vect and edge_vect. ---- */
    void define_NodeVector();
    void define_ElemVector();
    void define_HoriEdgeVector();
    void define_VertEdgeVector();

};

#endif  // MESH2D_H_
