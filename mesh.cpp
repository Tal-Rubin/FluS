// g++ -std=c++11 -o 1.exe 1.cpp

#include <iostream>
#include <vector>
using std::vector;


class Mesh2D
{
private:
    int N_row;
    int N_col;

    int Node_row;
    int Node_col;

    int NodeBeginNum;
    int ElemBeginNum;

    vector< vector<int> > NodeList_ID;
    vector< vector<double> > NodeList_pos;

    void define_NodeList_ID(){
        
        int dim1_NodeList_ID = 1;
        int dim2_NodeList_ID = Node_row * Node_col;

        vector< vector<int> > NodeList_ID(dim1_NodeList_ID, vector<int> (dim2_NodeList_ID, 0));

        for (int i = 0; i < Node_col; i++){
            for (int j = 0; j< Node_row; j++){
                NodeList_ID[0][i * Node_row + j] = i * Node_row + j;
            }
        }

        for(int j =0; j < dim2_NodeList_ID; j++){
            std::cout << 0 <<","<< j <<" = " << NodeList_ID[0][j] << std::endl;
        }
    }



public:
    Mesh2D(int n_row, int n_col, int nodeBeginNum, int elemBeginNum)
    {
        N_row = n_row;
        N_col = n_col;

        Node_row = 2 * N_row +1;
        Node_col = 2 * N_col +1;

        NodeBeginNum = nodeBeginNum;
        ElemBeginNum = elemBeginNum;

        std::cout << "N_row = " << N_row << std::endl;
        std::cout << "N_col = " << N_col << std::endl;

        std::cout << "Node_row = " << Node_row << std::endl;
        std::cout << "Node_col = " << Node_col << std::endl;

    }
    vector<vector<int> > get_NodeList_ID(){
        define_NodeList_ID();
        return NodeList_ID;
    }
};

int main()
{
    Mesh2D mesh(1,2,3,4);
    mesh.get_NodeList_ID();

}