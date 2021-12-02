/**
 * @file mesh.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef FLUS_MESH_H_
#define FLUS_MESH_H_

/// @brief Base class for Mesh1D and Mesh2D.
class Mesh {
public:
    /// @brief Get the number of dimensions
    virtual int dim() =0;

    /// @brief Get the number of elements
    virtual int n_elements() =0;

    /// @brief Get the number of interfaces
    ///
    /// In 1D, it is the number of points on element edges. 
    /// In 2D, it is the number of elements edges. 
    /// In 3D, it is the number of faces, etc.
    virtual int n_interfaces() =0; 

    /// @brief Get the volume of a specified element
    /// @param element ID of the specified element
    virtual double el_volume(int element) =0; 

protected:
    /// @brief The number of Elements
    int Num_Elems_;  

    /// @brief The number of Edges
    int Num_Edges_;

    /// @brief The number of Nodes, including those in ghost and corner cells.
    int Num_Nodes_; 
};

#endif // FLUS_MESH_H_
