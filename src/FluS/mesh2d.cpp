// Meshing for 2D

#include <iostream>

#include "mesh2d.h"

/// @brief The type used to identify a node
struct Node {
    /// @brief The ID of the node
    ///
    /** @verbatim
     The node numbering example (2D): 
     1↓  4↓  7↓
     2↓  5↓  8↓ 
     3↓  6↓  9↓ @endverbatim 
     */
    unsigned int node_number;

    /// @brief In 2D, the position of a node is represented by x and y coordinates
    std::array<double,2> position;
};

/// @brief The type used to identify an element
struct Elem {
    /// @brief The ID of the element
    /// 
    /** @verbatim
     The element numbering example (2D): 
        __     __
     1↓|__| 3↓|__| 
     2↓|__| 4↓|__| @endverbatim 
     */
    unsigned int elem_number;

    /// @brief In 2D, there are 4 nodes in each element
    /** @verbatim
     The node numbering in each element (2D): 
      0 ____ 3
       |    | 
       |____|
      1      2  @endverbatim 
     */
    std::array<Node *,4> nodes; 

    /// @brief The volume of each element
    double volume;

    /// @brief Return true if it is a corner element (2D only)
    bool mega_ghost;

    /// @brief Return true if it is a ghost element
    bool ghost;
};

/// @brief The type used to identify an edge
struct Edge {
    /// @brief The ID of the edge
    unsigned int edge_number;

    /// @brief The pair of pointers represents neighbor elements of the edge
    std::pair<Elem *, Elem *> neighbor_elements;

    /// @brief The orientation of the edge
    std::valarray<double> unit_vector;
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

int Mesh2D::dim(){
    return dimen_;
}

int Mesh2D::n_elements(){
    return Num_Elems_;
}

int Mesh2D::n_interfaces(){
    return Num_Edges_;
}

double Mesh2D::el_volume(int element){

    define_ElemVector();

    return elem_vect[element].volume;
}  

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

            temp_elem.nodes[0] = &node_vect[ j + i * ( Elem_row_ + 3 ) ];    // node 1 #
            temp_elem.nodes[1] = &node_vect[ j + i * ( Elem_row_ + 3 ) + 1 ];    // node 2 #
            temp_elem.nodes[2] = &node_vect[ j + ( i + 1 ) * ( Elem_row_ + 3 ) + 1 ];    // node 3 #
            temp_elem.nodes[3] = &node_vect[ j + ( i + 1 ) * ( Elem_row_ + 3 ) ];    // node 4 #
            
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
            
            temp_edge_hor.neighbor_elements.first = &elem_vect[ ( i + 1 ) * ( Elem_row_ + 2 ) + j ];
            temp_edge_hor.neighbor_elements.second = &elem_vect[ ( i + 1 ) * ( Elem_row_ + 2 ) + j + 1 ];
            
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
            
            temp_edge_ver.neighbor_elements.first = &elem_vect[ i * ( Elem_row_ + 2 ) + j + 1 ];
            temp_edge_ver.neighbor_elements.second = &elem_vect[ ( i + 1 ) * ( Elem_row_ + 2 ) + j + 1 ];
            
            temp_edge_ver.unit_vector = {1, 0};
            
            vert_edge_vect.push_back(temp_edge_ver);
            
        }
    }
}

std::ostream& operator<<(std::ostream& os, Mesh2D& mesh2d){

    std::vector<Node> nodeVector = mesh2d.get_NodeVector();

    os << "NODES" << std::endl;
    for(int i = 0; i < nodeVector.size(); i++){
        os <<  nodeVector[i].position[0] << " ";
        os <<  nodeVector[i].position[1] << std::endl;
    }
    os << "END_NODES" << std::endl;


    os << "ELEMENTS" << std::endl;

    std::vector<Elem> elemVector = mesh2d.get_ElemVector();

    for(int i = 0; i < elemVector.size(); i++){

        // Node number should be reported clockwise. 
        // Our node numbering in each element:
        //  0 ____ 3
        //   |    | 
        //   |____|
        //  1      2 
        // So the ordering here should be 0 3 2 1

        os << elemVector[i].nodes[0]->node_number << " ";
        os << elemVector[i].nodes[3]->node_number << " ";
        os << elemVector[i].nodes[2]->node_number << " ";
        os << elemVector[i].nodes[1]->node_number << std::endl;
        // if (elemVector[i].ghost){
        //     os << " (ghost) " << std::endl;
        // }
        // else if (elemVector[i].mega_ghost) {
        //     os << " (mega_ghost/corner) " << std::endl;
        // }
        // else {
        //     os << std::endl;
        // }
    }
    os << "END_ELEMENTS" << std::endl;

    return os;
}

// int main(){

//     /* Output Tests */

//     Mesh2D mesh2d = Mesh2D(2,2,-1,1,-1,1);
//     operator<<(std::cout, mesh2d);

// }