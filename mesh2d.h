#ifndef MESH2D_H_
#define MESH2D_H_

#include <iostream>
#include <vector>
using std::vector;

#include "mesh.h"

class Mesh2D : public Mesh {

public:
    Mesh2D(int n_row, int n_col); // Constructor
    // ~Mesh2D();                 // Destructor

    vector<int>  get_NodesList_ID();
    vector< vector<double> >  get_NodesList_pos();

private:

    static const int DIM = 2;

    int Elem_row_;
    int Elem_col_;

    int Node_row_;
    int Node_col_;

    vector<int> NodesList_ID;
    vector< vector<double> > NodesList_pos;

    void define_NodesList_ID();
    void define_NodesList_pos();

};

#endif  // MESH2D_H_