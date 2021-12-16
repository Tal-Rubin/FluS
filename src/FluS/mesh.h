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

#ifndef FLUS_MESH_H_DEPRERCATED
#define FLUS_MESH_H_DEPRERCATED

struct Edge;
struct Elem;
struct Node;


struct mesh_parameters {
    unsigned int dimension;
    
};


class Mesh {
public:

    virtual ~Mesh(){}

    virtual int dim() =0;

    virtual int n_elements() =0;

    virtual int n_interfaces() =0; // in 1D, is the number of points on element edges, in 2D is the number of elements edges, in 3D is the number of faces, etc.

    virtual double el_volume(int element)=0;  // TO DO

};

#endif // FLUS_MESH_H_DEPRERCATED
