// Meshing for 2D
#include <iostream>

#include "mesh2d.h"

struct Edge {
    unsigned int edge_number;
    std::pair<unsigned int, unsigned int> neighbor_elements;
    std::valarray<double> unit_vector;
};

struct Elem {
    unsigned int elem_number;
    std::array<unsigned int,4> nodes; // 4 nodes in each element
    double volume;
    bool mega_ghost;
    bool ghost;
};

struct Node {
    unsigned int node_number;
    std::array<double,2> position; // 2D
};

Mesh2D::Mesh2D(int elem_row, int elem_col, double x0, double x1, double y0, double y1)
    :Elem_row_(elem_row), Elem_col_(elem_col), x0_(x0), x1_(x1), y0_(y0), y1_(y1)
{
    Node_row_ = elem_row + 3;
    Node_col_ = elem_col + 3;

    Num_Elems_ = Elem_row_*Elem_col_;
    Num_Nodes_ = Node_row_*Node_col_;
    Num_Edges_ = (Elem_row_+1)*Elem_col_ + (Elem_col_+1)*Elem_row_;
    
    dx_ = ( x1_ - x0_ ) / double(Elem_col_);
    dy_ = ( y1_ - y0_ ) / double(Elem_row_);
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

    define_NodeVector();

    return node_vect;
}

std::vector<Elem> Mesh2D::get_ElemVector(){
    
    define_ElemVector();
    
    return elem_vect;
}

std::vector<Edge> Mesh2D::get_HoriEdgeVector(){
    
    define_HoriEdgeVector();
    
    return hori_edge_vect;
}

std::vector<Edge> Mesh2D::get_VertEdgeVector(){
    
    define_VertEdgeVector();
    
    return vert_edge_vect;
}

void Mesh2D::define_NodeVector(){

    Node temp_node;

    for (int i = 0; i < Node_col_; i++){
        for (int j = 0; j< Node_row_; j++){

            temp_node.node_number = i*Node_row_ + j;

            temp_node.position[0] = x0_ + dx_ * (i-1);
            temp_node.position[1] = y1_ - dy_ * (j-1);

            node_vect.push_back(temp_node);
        }
    }
}

void Mesh2D::define_ElemVector(){
    
    Elem temp_elem;
    
    for (unsigned int i = 0; i < Elem_col_ + 2; i++){
        for (unsigned int j = 0; j< Elem_row_ + 2; j++){

            temp_elem.elem_number = i * ( Elem_row_ + 2 ) + j;

            temp_elem.nodes[0] = j + i * ( Elem_row_ + 3 );    // node 1 #
            temp_elem.nodes[1] = j + i * ( Elem_row_ + 3 ) + 1;    // node 2 #
            temp_elem.nodes[2] = j + ( i + 1 ) * ( Elem_row_ + 3 ) + 1;    // node 3 #
            temp_elem.nodes[3] = j + ( i + 1 ) * ( Elem_row_ + 3 );    // node 4 #
            
            temp_elem.volume = dx_ * dy_;
            
            temp_elem.mega_ghost = false;
            temp_elem.ghost = false;
            
            if ( ( i == 0 || i == Elem_col_ + 1 ) && ( j == 0 || j == Elem_row_ + 1 ) ){
                temp_elem.mega_ghost = true;
                mega_ghost_elements.push_back(temp_elem.elem_number);
            }
            
            if ( ( i == 0 || i == Elem_col_ + 1 || j == 0 || j == Elem_row_ + 1 ) && ( temp_elem.mega_ghost == false ) ){
                temp_elem.ghost = true;
                ghost_elements.push_back(temp_elem.elem_number);
            }

            elem_vect.push_back(temp_elem);
        }
    }
    
}

void Mesh2D::define_HoriEdgeVector(){
    
    Edge temp_edge_hor;
    
    for (unsigned int i = 0; i < Elem_col_; i++){
        for (unsigned int j = 0; j < Elem_row_ + 1; j++){
            
            temp_edge_hor.edge_number = i * ( Elem_row_ + 1 ) + j;
            
            temp_edge_hor.neighbor_elements.first = ( i + 1 ) * ( Elem_row_ + 2 ) + j;
            temp_edge_hor.neighbor_elements.second = ( i + 1 ) * ( Elem_row_ + 2 ) + j + 1;
            
            temp_edge_hor.unit_vector = {0, -1};
            
            hori_edge_vect.push_back(temp_edge_hor);
            
        }
    }
}

void Mesh2D::define_VertEdgeVector(){
    
    Edge temp_edge_ver;
    
    for (unsigned int j = 0; j < Elem_row_; j++){
        for (unsigned int i = 0; i < Elem_col_ + 1; i++){
            
            temp_edge_ver.edge_number = j * ( Elem_col_ + 1 ) + i;
            
            temp_edge_ver.neighbor_elements.first = i * ( Elem_row_ + 2 ) + j + 1;
            temp_edge_ver.neighbor_elements.second = ( i + 1 ) * ( Elem_row_ + 2 ) + j + 1;
            
            temp_edge_ver.unit_vector = {1, 0};
            
            vert_edge_vect.push_back(temp_edge_ver);
            
        }
    }
}

int main(){

    /* Some Tests */

    Mesh2D* mesh2d = new Mesh2D(4,5,-1,1,-1,1);

    std::cout << mesh2d->n_elements() << std::endl;
    std::cout << mesh2d->n_interfaces() << std::endl;
    

    // Test node vector
    std::vector<Node> nodeVector = mesh2d->get_NodeVector();

    for(int i = 0; i < nodeVector.size(); i++){
        // std::cout << i << " = " << nodeVector[i].node_number << std::endl;
        std::cout << i << " = " << nodeVector[i].position[0] << std::endl;
        // std::cout << i << " = " << nodeVector[i].position[1] << std::endl;
    }
    for(int i = 0; i < nodeVector.size(); i++){
        std::cout << i << " = " << nodeVector[i].position[1] << std::endl;
    }
    

    // // Test element vector
    // std::vector<Elem> elemVector = mesh2d->get_ElemVector();
    
    // for(int i = 0; i < elemVector.size(); i++){
    //     std::cout << " elem ID = " << elemVector[i].elem_number << std::endl;
    //     std::cout << " node 1 = " << elemVector[i].nodes[0] << std::endl;
    //     std::cout << " node 2 = " << elemVector[i].nodes[1] << std::endl;
    //     std::cout << " node 3 = " << elemVector[i].nodes[2] << std::endl;
    //     std::cout << " node 4 = " << elemVector[i].nodes[3] << std::endl;
    //     std::cout << " volume = " << elemVector[i].volume << std::endl;
    //     std::cout << " meta_ghost = " << elemVector[i].mega_ghost << std::endl;
    //     std::cout << " ghost = " << elemVector[i].ghost << std::endl;
    // }

    
    // // Test edge vector
    // std::vector<Edge> horiedgeVector = mesh2d->get_HoriEdgeVector();
    
    // for(int i = 0; i < horiedgeVector.size(); i++){
    //     std::cout << " hori-edge ID = " << horiedgeVector[i].edge_number << std::endl;
    //     std::cout << " neigh-elem 1 = " << horiedgeVector[i].neighbor_elements.first << std::endl;
    //     std::cout << " neigh-elem 2 = " << horiedgeVector[i].neighbor_elements.second << std::endl;
    //     std::cout << " unit vector x = " << horiedgeVector[i].unit_vector[0] << std::endl;
    //     std::cout << " unit vector y = " << horiedgeVector[i].unit_vector[1] << std::endl;
    // }
    
    // std::vector<Edge> vertedgeVector = mesh2d->get_VertEdgeVector();
    
    // for(int i = 0; i < vertedgeVector.size(); i++){
    //     std::cout << " vert-edge ID = " << vertedgeVector[i].edge_number << std::endl;
    //     std::cout << " neigh-elem 1 = " << vertedgeVector[i].neighbor_elements.first << std::endl;
    //     std::cout << " neigh-elem 2 = " << vertedgeVector[i].neighbor_elements.second << std::endl;
    //     std::cout << " unit vector x = " << vertedgeVector[i].unit_vector[0] << std::endl;
    //     std::cout << " unit vector y = " << vertedgeVector[i].unit_vector[1] << std::endl;
    // }
    
}
