/**
 * @file mesh1d.h
 * @author Bingjia Yang, Kehan Cai
 * @brief 
 * @version 0.1
 * @date 2021-12-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// Based on https://github.com/Tal-Rubin/FluS/blob/Tal/src/mocks/mesh_mock.h

#ifndef MESH1D_H_
#define MESH1D_H_
#include <iostream>
#include <array>
#include <utility>
#include <valarray>
#include <vector>

#include "mesh.h"

struct Node;
struct Elem;
struct Edge;

/// @brief Class handling the meshing in one-dimension space.
///
/// This method is a 1D mesher.
class Mesh1D : public Mesh {

public:
    /* ---------------------------- Constructor --------------------------- */

    /// @brief Construct a new Mesh1D object
    /// 
    /// Construct a num_Elems grid in the specified region [x0, x1]. The ghost elements are created outside of the region.
    /// @param num_Elems Number of elements / finite volume data 
    /// @param x0 lower x-bound for the meshing region
    /// @param x1 upper x-bound for the meshing region
    Mesh1D(int num_Elems, double x0, double x1); 

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

    /// @brief Get the edge_vect, which containing Edge objects.
    /// @return std::vector<Edge> The edge_vect. 
    std::vector<Edge> get_EdgeVector();

    /// @brief Output operator overload.
    friend std::ostream& operator<<(std::ostream& os, Mesh1D& mesh1d);

private:

    static const int dimen_ = 1; // Space dimension 

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