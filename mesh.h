#ifndef MESH_H_
#define MESH_H_

#include <iostream>
#include <vector>
using std::vector;

class Mesh {

public:
    virtual ~Mesh(){}

    virtual vector<int>  get_NodesList_ID() = 0;
    virtual vector< vector<double> >  get_NodesList_pos() = 0;
    
};

#endif  // MESH_H_