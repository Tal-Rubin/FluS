// g++ -o *.exe *.cpp

#include <iostream>
#include <vector>
using std::vector;

#include "mesh2d.h"

Mesh2D::Mesh2D(int elem_row, int elem_col, double x0, double x1, double y0, double y1)
    :Elem_row_(elem_row), Elem_col_(elem_col), x0_(x0), x1_(x1), y0_(y0), y1_(y1)
{
    Node_row_ = 2*elem_row + 1;
    Node_col_ = 2*elem_col + 1;

    Num_Elems_ = Elem_row_*Elem_col_;
    Num_Nodes_ = Node_row_*Node_col_;
    Num_Edges_ = (Elem_row_+1)*Elem_col_ + (Elem_col_+1)*Elem_row_;
}

Mesh2D::~Mesh2D(){
    // TO DO
}

int Mesh2D::dim(){
    return dimen_;
}

int Mesh2D::n_elements(){
    return Num_Elems_;
}

int Mesh2D::n_interfaces(){
    return Num_Edges_;
}

// double el_volume(int element){
//     double tol_volume = 2**dimen_;
//     return tol_volume/double(Num_Elems_);
// }  

std::vector<Node> Mesh2D::get_NodeVector(){

    define_NodesVector();

    return node_vect;
}

void Mesh2D::define_NodeVector(){
    double dx = (x1_-x0_)/double(Node_col_-1);
    double dy = (y1_-y0_)/double(Node_row_-1);

    Node temp_node;

    for (int i = 0; i < Node_col_; i++){
        for (int j = 0; j< Node_row_; j++){

            temp_node.node_number = i*Node_row_ + j;

            temp_node.position[0] = x0_ + dx * i;
            temp_node.position[1] = y1_ - dy * j;

            node_vect.push_back(temp_node);
        }
    }
}

int main(){

    /* Some Tests */

    Mesh2D* mesh2d = new Mesh2D(3,2,-2,2,-1,1);

    std::vector<Node> nodeVector = mesh2d->get_NodeVector();

    for(int i = 0; i < nodeVector.size(); i++){
        // std::cout << i << " = " << nodeVector[i].node_number << std::endl;
        std::cout << i << " = " << nodeVector[i].position[0] << std::endl;
        // std::cout << i << " = " << nodeVector[i].position[1] << std::endl;
    }
    for(int i = 0; i < nodeVector.size(); i++){
        std::cout << i << " = " << nodeVector[i].position[1] << std::endl;
    }


}