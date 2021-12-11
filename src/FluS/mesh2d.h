// Meshing for 2D

#ifndef MESH2D_H_
#define MESH2D_H_
#include <iostream>
#include <array>
#include <utility>
#include <valarray>
#include <vector>

#include "mesh.h"

struct Node;
struct Elem;
struct Edge;

/// @brief Class handling the meshing in two-dimension space.
///
/// This method is a 2D mesher.
class Mesh2D : public Mesh {

public:
    /* ---------------------------- Constructor --------------------------- */

    /// @brief Construct a new Mesh2D object
    /// 
    /// Construct a n_row x n_col grid in the specified rectangle [x0, x1] x [y0, y1]. The ghost and corner elements are created outside of the rectangle. 
    /// @param n_row Number of rows of elements / finite volume data 
    /// @param n_col Number of columns of elements / finite volume data 
    /// @param x0 lower x-bound for the meshing region
    /// @param x1 upper x-bound for the meshing region
    /// @param y0 lower y-bound for the meshing region
    /// @param y1 upper y-bound for the meshing region
    Mesh2D(int n_row, int n_col, double x0, double x1, double y0, double y1); 

    /* ---------------- Functions to get useful properties ---------------- */
    int dim();
    int n_elements();
    int n_interfaces(); 
    double el_volume(int element); 

    /* ------- Functions to get node_vect, elem_vect and edge_vect. ------- */

    /// @brief Get the node_vect, which containing Node objects.
    /// @return std::vector<Node> The node_vect.
    std::vector<Node> get_NodeVector();

    /// @brief Get the elem_vect, which containing Elem objects.
    /// @return std::vector<Elem> The elem_vect. 
    std::vector<Elem> get_ElemVector();

    /// @brief Get the hori_edge_vect, which containing all the horizontal Edge objects.
    /// @return std::vector<Edge> The hori_edge_vect. 
    std::vector<Edge> get_HoriEdgeVector();

    /// @brief Get the vert_edge_vect, which containing all the vertical Edge objects.
    /// @return std::vector<Edge> The vert_edge_vect. 
    std::vector<Edge> get_VertEdgeVector();

    /// @brief Output operator overload.
    friend std::ostream& operator<<(std::ostream& os, Mesh2D& mesh2d);

private:

    static const int dimen_ = 2; // Space dimension

    // The number of rows and columns for Elements.
    int Elem_row_;   
    int Elem_col_;  

    // The number of Nodes, including those in ghost and corner cells.
    int Node_row_;   
    int Node_col_; 

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
