// g++ -o *.exe *.cpp

#include <iostream>
#include <vector>
using std::vector;

#include "mesh2d.h"


Mesh2D::Mesh2D(int elem_row, int elem_col)
{
    Elem_row_ = elem_row;
    Elem_col_ = elem_col;

    Node_row_ = 2*elem_row + 1;
    Node_col_ = 2*elem_col + 1;

    Num_Nodes = Node_row_*Node_col_;
    Num_Edges = (Elem_row_+1)*Elem_col_ + (Elem_col_+1)*Elem_row_;

}

vector<int> Mesh2D::get_EdgesList_ID(){

    define_EdgesList_ID();

    return EdgesList_ID;
}

vector<int> Mesh2D::get_NodesList_ID(){

    define_NodesList_ID();

    return NodesList_ID;
}

vector< vector<double> > Mesh2D::get_NodesList_pos(){

    define_NodesList_pos();
    PBE_NodesList_pos();

    return NodesList_pos;
}


void Mesh2D::define_EdgesList_ID(){

    EdgesList_ID.resize(Num_Edges, 0);

    for (int i = 0; i < Elem_col_; i++){
        for (int j = 0; j < 2*Elem_row_+1; j++){
            EdgesList_ID[i*(2*Elem_row_+1) + j] = i*(2*Elem_row_+1) + j;
        }
    }

    for (int k =0; k < Elem_row_; k++){
        EdgesList_ID[Elem_col_*(2*Elem_row_+1) + k] = Elem_col_*(2*Elem_row_+1) + k;
    }
}

void Mesh2D::define_NodesList_ID(){
    
    NodesList_ID.resize(Num_Nodes, 0);

    for (int i = 0; i < Node_col_; i++){
        for (int j = 0; j < Node_row_; j++){
            NodesList_ID[i*Node_row_ + j] = i*Node_row_ + j;
        }
    }
}

void Mesh2D::define_NodesList_pos(){

    NodesList_pos.resize(DIM, vector<double> (Num_Nodes, 0.0));
    
    for (int i = 0; i < Node_col_; i++){
        for (int j = 0; j< Node_row_; j++){
            NodesList_pos[0][i*Node_row_ + j] = -1.0 + i / double(Elem_col_); // x
            NodesList_pos[1][i*Node_row_ + j] = 1.0 - j / double(Elem_row_) ; // y
        }
    }
}

void Mesh2D::PBE_NodesList_pos(){

    for (int j = 0; j< Node_row_; j++){ // let all x=1 -> x=-1
        NodesList_pos[0][(Node_col_-1)*Node_row_ + j] = NodesList_pos[0][0*Node_row_ + j];
    }
    for (int i = 0; i < Node_col_; i++){ // let all y=1 -> y=-1
        NodesList_pos[1][i*Node_row_ + 0] = NodesList_pos[1][i*Node_row_ + (Node_row_-1)];
    }
}

int main(){
    Mesh2D* mesh2d = new Mesh2D(4,3);

    vector<int> edgesList_ID = mesh2d->get_EdgesList_ID();
    vector<int> nodesList_ID = mesh2d->get_NodesList_ID();
    vector< vector<double> > nodesList_pos = mesh2d->get_NodesList_pos();

    std::cout << "NodesList_ID size = " << nodesList_ID.size() << std::endl;

    // std::cout << "----- NodesList_pos -----" << std::endl;
    // for(int i = 0; i < nodesList_pos.size(); i++){
    //     for (int j = 0; j < nodesList_pos[i].size(); j++)
    //         std::cout << i << "," << j<< " = " << nodesList_pos[i][j] << std::endl;
    // }
    // std::cout << "----- NodesList_pos -----" << std::endl;

    // std::cout << "----- EdgesList_ID -----" << std::endl;
    // for(int i = 0; i < edgesList_ID.size(); i++){
    //     std::cout << i << " = " << edgesList_ID[i] << std::endl;
    // }
    // std::cout << "----- EdgesList_ID -----" << std::endl;

}