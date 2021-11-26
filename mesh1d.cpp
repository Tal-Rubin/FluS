// g++ -o *.exe *.cpp

#include <iostream>
#include <vector>
using std::vector;

#include "mesh1d.h"

Mesh1D::Mesh1D(int num_Elems)
{
    Num_Elems = num_Elems;
    Num_Nodes = 2*Num_Elems + 1;
}

vector<int> Mesh1D::get_NodesList_ID(){

    define_NodesList_ID();

    return NodesList_ID;
}

vector< vector<double> > Mesh1D::get_NodesList_pos(){

    define_NodesList_pos();
    // PBE_NodesList_pos();

    return NodesList_pos;
}

void Mesh1D::define_NodesList_ID(){
    
    NodesList_ID.resize(Num_Nodes, 0);

    for (int i = 0; i < Num_Nodes; i++){
        NodesList_ID[i] = i;
    }

}

void Mesh1D::define_NodesList_pos(){

    NodesList_pos.resize(DIM, vector<double> (Num_Nodes, 0.0));

    for (int i = 0; i < Num_Nodes; i++){
        NodesList_pos[0][i] = -1 + 2*i/double(Num_Nodes-1);
    }
}

int main(){

    Mesh1D* mesh1d = new Mesh1D(4);
    vector<int> nodesList_ID = mesh1d->get_NodesList_ID();
    vector< vector<double> > nodesList_pos = mesh1d->get_NodesList_pos();

    // std::cout << "NodesList_ID size = " << nodesList_ID.size() << std::endl;
    
    // std::cout << "----- NodesList_pos -----" << std::endl;
    // for(int i = 0; i < nodesList_pos.size(); i++){
    //     for (int j = 0; j < nodesList_pos[i].size(); j++)
    //         std::cout << i << "," << j<< " = " << nodesList_pos[i][j] << std::endl;
    // }
    // std::cout << "----- NodesList_pos -----" << std::endl;

}