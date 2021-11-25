// g++ -std=c++11 -o 1.exe 1.cpp

#include <iostream>
#include <vector>
using std::vector;

class Mesh2D
{
private:
    static const int DIM = 2;
    
    int N_row;
    int N_col;

    int Node_row;
    int Node_col;

    // vector<int> NodesList_ID;
    // vector< vector<double> > NodesList_pos;

    vector<int> define_NodesList_ID(){
        
        int dim1_NodesList_ID = 1;
        int dim2_NodesList_ID = Node_row * Node_col;

        vector<int> NodesList_ID(dim2_NodesList_ID, 0);

        for (int i = 0; i < Node_col; i++){
            for (int j = 0; j< Node_row; j++){
                NodesList_ID[i * Node_row + j] = i * Node_row + j;
            }
        }
        return NodesList_ID;
    }
    vector< vector<double> > define_NodesList_pos(){

        int dim1_NodesList_pos = DIM;
        int dim2_NodesList_pos = Node_row * Node_col;

        vector< vector<double> > NodesList_pos(dim1_NodesList_pos, vector<double> (dim2_NodesList_pos, 0.0));
        for (int i = 0; i < Node_col; i++){
            for (int j = 0; j< Node_row; j++){
                NodesList_pos[0][i * Node_row + j] = -1.0 + i / double(N_col); // x
                NodesList_pos[1][i * Node_row + j] = 1.0 - j / double(N_row) ; // x
            }
        }
        return NodesList_pos;
    }



public:
    Mesh2D(int n_row, int n_col)
    {
        N_row = n_row;
        N_col = n_col;

        Node_row = 2 * N_row + 1;
        Node_col = 2 * N_col + 1;

    }

    vector<int>  get_NodesList_ID(){

        vector<int> NodesList_ID = define_NodesList_ID();

        return NodesList_ID;

    }
    vector< vector<double> >  get_NodesList_pos(){

        vector< vector<double> > NodesList_pos = define_NodesList_pos();

        return NodesList_pos;

    }
};

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