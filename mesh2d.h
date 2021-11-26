#ifndef MESH2D_H_
#define MESH2D_H_

#include <iostream>
#include <vector>
using std::vector;

#include "mesh.h"

class Mesh2D : public Mesh {

public:
    Mesh2D(int n_row, int n_col);  // Constructor
    // ~Mesh2D();                  // Destructor

    vector<int> get_EdgesList_ID();                // Get the Edges ID
    vector<int> get_NodesList_ID();                // Get the Nodes ID
    vector< vector<double> > get_NodesList_pos();  // Get the global Nodes position

private:

    static const int DIM = 2; // Space dimension

    int Elem_row_;  // The number of rows and columns for elements
    int Elem_col_;  

    int Node_row_;  // The number of rows and columns for nodes
    int Node_col_;  

    int Num_Nodes;  // The number of Nodes
    int Num_Edges;  // The number of Edges

    vector<int> EdgesList_ID;               // ID of Edges, dim=(Num_Edges). 
    vector<int> NodesList_ID;               // ID of Nodes, dim=(Num_Nodes). 
    vector< vector<double> > NodesList_pos; // x and y coordinates of Nodes, dim=(2, Num_Nodes). 

    void define_EdgesList_ID();
    void define_NodesList_ID();
    void define_NodesList_pos();

    void PBE_NodesList_pos();
    
};

#endif  // MESH2D_H_