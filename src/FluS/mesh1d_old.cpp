// g++ -o *.exe *.cpp

#include <iostream>
#include <vector>
using std::vector;

#include "mesh1d.h"

Mesh1D::Mesh1D(int num_Elems)
    :Num_Elems_(num_Elems)
{
    Num_Nodes_ = 2*Num_Elems_ + 1;
    Num_Edges_ = Num_Elems_ + 1;
}

Mesh1D::~Mesh1D(){
    // TO DO
}

int Mesh1D::dim(){
    return dimen_;
}

int Mesh1D::n_elements(){
    return Num_Elems_;
}

int Mesh1D::n_interfaces(){
    return Num_Edges_;
}

// double el_volume(int element){
//     double tol_volume = 2**dimen_;
//     return tol_volume/double(Num_Elems_);
// }  

vector<int> Mesh1D::get_NodesList_ID(){

    define_NodesList_ID();

    return NodesList_ID;
}

vector< vector<double> > Mesh1D::get_NodesList_pos(){

    define_NodesList_pos();
    PBE_NodesList_pos();

    return NodesList_pos;
}

void Mesh1D::define_NodesList_ID(){
    
    NodesList_ID.resize(Num_Nodes_, 0);

    for (int i = 0; i < Num_Nodes_; i++){
        NodesList_ID[i] = i;
    }

}

void Mesh1D::define_NodesList_pos(){

    NodesList_pos.resize(dimen_, vector<double> (Num_Nodes_, 0.0));

    for (int i = 0; i < Num_Nodes_; i++){
        NodesList_pos[0][i] = -1 + 2*i/double(Num_Nodes_-1);
    }
}

void Mesh1D::PBE_NodesList_pos(){

    NodesList_pos[0][Num_Nodes_-1] = -1;
}

int main(){

    /* Some Tests */

    Mesh1D* mesh1d = new Mesh1D(4);

    vector<int> nodesList_ID = mesh1d->get_NodesList_ID();
    vector< vector<double> > nodesList_pos = mesh1d->get_NodesList_pos();

    std::cout << "NodesList_ID size = " << nodesList_ID.size() << std::endl;
    
    std::cout << "----- NodesList_pos -----" << std::endl;
    for(int i = 0; i < nodesList_pos.size(); i++){
        for (int j = 0; j < nodesList_pos[i].size(); j++)
            std::cout << i << "," << j<< " = " << nodesList_pos[i][j] << std::endl;
    }

}