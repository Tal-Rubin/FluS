#ifndef MESH2D_H_
#define MESH2D_H_

#include <iostream>
#include <vector>
using std::vector;

#include "mesh.h"

class Mesh2D : public Mesh {

public:
    Mesh2D(int n_row, int n_col);  // Constructor
    ~Mesh2D();                     // Destructor      

    int dim();

    int n_elements();

    int n_interfaces(); // in 1D, is the number of points on element edges, in 2D is the number of elements edges, in 3D is the number of faces, etc.

    // double el_volume(int element);  // TO DO

    /* ----- Some useful functions ----- */
    vector<int> get_EdgesList_ID();                // Get the Edges ID
    vector<int> get_NodesList_ID();                // Get the Nodes ID
    vector< vector<double> > get_NodesList_pos();  // Get the global Nodes position
    /* --------------------------------- */

private:

    static const int dimen_ = 2; // Space dimension

    int Elem_row_;  // The number of rows and columns for Elements
    int Elem_col_;  

    int Node_row_;  // The number of rows and columns for Nodes
    int Node_col_;  

    int Num_Elems_;  // The number of Elements, Nodes and Edges.
    int Num_Nodes_;  
    int Num_Edges_;  

    vector<int> EdgesList_ID;               // ID of Edges, dim=(Num_Edges). 
    vector<int> NodesList_ID;               // ID of Nodes, dim=(Num_Nodes). 
    vector< vector<double> > NodesList_pos; // x and y coordinates of Nodes, dim=(2, Num_Nodes). 

    void define_EdgesList_ID();
    void define_NodesList_ID();
    void define_NodesList_pos();
    void PBE_NodesList_pos();
    
};

#endif  // MESH2D_H_