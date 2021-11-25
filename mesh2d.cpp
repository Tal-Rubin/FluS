// g++ -o *.exe *.cpp

#include <iostream>
#include <vector>
using std::vector;

#include "mesh2d.h"


    Mesh2D::Mesh2D(int elem_row, int elem_col)
    {
        Elem_row_ = elem_row;
        Elem_col_ = elem_col;

        Node_row_ = 2 * elem_row + 1;
        Node_col_ = 2 * elem_col + 1;

    }

    vector<int> Mesh2D::get_NodesList_ID(){

        define_NodesList_ID();
        return NodesList_ID;

    }

    vector< vector<double> > Mesh2D::get_NodesList_pos(){
        define_NodesList_pos();
        return NodesList_pos;
    }


    void Mesh2D::define_NodesList_ID(){
        
        int dim_NodesList_ID = Node_row_ * Node_col_;

        NodesList_ID.resize(dim_NodesList_ID, 0);

        for (int i = 0; i < Node_col_; i++){
            for (int j = 0; j< Node_row_; j++){
                NodesList_ID[i * Node_row_ + j] = i * Node_row_ + j;
            }
        }
    }

    void Mesh2D::define_NodesList_pos(){

        int dim1_NodesList_pos = DIM;
        int dim2_NodesList_pos = Node_row_ * Node_col_;

        NodesList_pos.resize(dim1_NodesList_pos, vector<double> (dim2_NodesList_pos, 0.0));
        
        for (int i = 0; i < Node_col_; i++){
            for (int j = 0; j< Node_row_; j++){
                NodesList_pos[0][i * Node_row_ + j] = -1.0 + i / double(Elem_col_); // x
                NodesList_pos[1][i * Node_row_ + j] = 1.0 - j / double(Elem_row_) ; // y
            }
        }
    }

int main()
{
    Mesh2D* mesh2d = new Mesh2D(1,2);

    vector<int> nodesList_ID = mesh2d->get_NodesList_ID();
    vector< vector<double> > nodesList_pos = mesh2d->get_NodesList_pos();

    std::cout << "NodesList_ID size = " << nodesList_ID.size() << std::endl;

    for(int i = 0; i < nodesList_ID.size(); i++){
        std::cout << i << " = " << nodesList_ID[i] << std::endl;
    }

    for(int i = 0; i < nodesList_pos.size(); i++){
        for (int j = 0; j < nodesList_pos[i].size(); j++)
            std::cout << i << "," << j<< " = " << nodesList_pos[i][j] << std::endl;
    }
}