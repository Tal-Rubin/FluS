#ifndef MESH1D_H_
#define MESH1D_H_

#include <iostream>
#include <vector>
using std::vector;

#include "mesh.h"

class Mesh1D : public Mesh {

public:
    Mesh1D(int num_Elems);  // Constructor
    ~Mesh1D();              // Destructor

    int dim();

    int n_elements();

    int n_interfaces(); // in 1D, is the number of points on element edges, in 2D is the number of elements edges, in 3D is the number of faces, etc.

    // double el_volume(int element);  // TO DO

    /* ----- Some useful functions ----- */
    vector<int> get_NodesList_ID();                // Get the Nodes ID
    vector< vector<double> > get_NodesList_pos();  // Get the global Nodes position
    /* --------------------------------- */

private:

    static const int dimen_ = 1; // Space dimension

    int Num_Elems_;  // The number of Elements, Nodes and Edges.
    int Num_Nodes_; 
    int Num_Edges_;

    vector<int> NodesList_ID;               // ID of Nodes, dim=(Num_Nodes). 
    vector< vector<double> > NodesList_pos; // coordinates of Nodes, dim=(1, Num_Nodes). 

    void define_NodesList_ID();
    void define_NodesList_pos();
    void PBE_NodesList_pos();
    
};

#endif  // MESH1D_H_