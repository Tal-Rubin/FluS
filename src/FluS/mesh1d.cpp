// Based on https://github.com/Tal-Rubin/FluS/blob/Tal/src/mocks/mesh_mock.h

#include <iostream>

#include "mesh1d.h"

struct Node {
    /** @verbatim
     The node numbering example (1D): 
     1 → 2 → 3 → 4 → 5 → 6 @endverbatim 
     */
    unsigned int node_number;

    /// @brief In 1D, the position of a node is represented by x coordinate
    std::array<double,1> position;
};

struct Elem {
    /** @verbatim
     The element numbering example (1D): 
     1→|__| 2→|__| 3→|__|  @endverbatim 
     */
    unsigned int elem_number;

    /// @brief In 1D, there are 2 nodes(left node and right node) in each element
    /** @verbatim
     The node numbering in each element (1D): 
        |___|
       0     1 @endverbatim 
     */
    std::array<Node *,2> nodes; 

    double volume;
    bool ghost;
};

struct Edge {
    unsigned int edge_number;
    std::pair<Elem *, Elem *> neighbor_elements;
    std::valarray<double> unit_vector;
};

Mesh1D::Mesh1D(int num_Elems, double x0, double x1)
    :x0_(x0), x1_(x1)
{
    Num_Elems_ = num_Elems;
    Num_Nodes_ = num_Elems + 3;
    Num_Edges_ = num_Elems + 1;
    dx_ = (x1_-x0_)/double(Num_Elems_);
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

double Mesh1D::el_volume(int element){

    define_ElemVector();

    return elem_vect[element].volume;
} 

std::vector<Node> Mesh1D::get_NodeVector(){

    define_NodeVector();

    return node_vect;
}
std::vector<Edge> Mesh1D::get_EdgeVector(){

    define_EdgeVector();

    return edge_vect;
}

std::vector<Elem> Mesh1D::get_ElemVector(){

    define_ElemVector();

    return elem_vect;
}

void Mesh1D::define_NodeVector(){

    Node temp_node;

    for (int i = 0; i < Num_Nodes_; i++){

            temp_node.node_number = i;

            temp_node.position[0] = x0_ + dx_ * (i-1);

            node_vect.push_back(temp_node);
        }  
}

void Mesh1D::define_ElemVector(){
    Elem temp_elem;

    for(int i = 0; i < Num_Elems_+ 2; i++){
        temp_elem.elem_number = i;
        temp_elem.volume = dx_;
        temp_elem.ghost = false;
        temp_elem.nodes[0] = &node_vect[ i ];
        temp_elem.nodes[1] = &node_vect[ i + 1 ];

        if (i==0 || i == Num_Elems_+1){
            temp_elem.ghost = true;
            ghost_elements.push_back(temp_elem.elem_number);
        }
        elem_vect.push_back(temp_elem);
    }
}

void Mesh1D::define_EdgeVector(){
    Edge temp_edge;

    for (int i = 0; i < Num_Edges_; i++){
        temp_edge.edge_number = i;
        temp_edge.neighbor_elements.first = &elem_vect[ i ];
        temp_edge.neighbor_elements.second = &elem_vect[ i + 1 ];
        temp_edge.unit_vector = {1};

        edge_vect.push_back(temp_edge);
    }

}
