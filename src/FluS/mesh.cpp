/**
 * @file mesh.cpp
 * @author Tal Rubin (trubin@princeton.edu), Bingjia Yang, Kehan Cai
 * @brief
 * @version 0.1
 * @date 2021-12-16
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <stdexcept>


#include "mesh.h"

//! 1D mesh constructor
Mesh::Mesh(unsigned int num_ele, std::vector<double> x_pos, bool circular): element_volume(num_ele+2*(!circular)), dim_(1)  {

  unsigned int node_number = 0;
  unsigned int edge_number = 0;
  unsigned int ele_number = 0;

  // No grouping of edges in 1D
  edge_vect.resize(1);
  
  Node temp_node;
    temp_node.position.resize(dim_);
  Edge temp_edge;
    temp_edge.unit_vector.resize(dim_);
  Elem temp_elem;
    temp_elem.nodes.resize(2);

  if (x_pos.size()<2) {
    throw std::invalid_argument("wrong size of 1d domain");
  } else if (x_pos.size()==2) {

    double dx = (x_pos[1]-x_pos[0])/num_ele;

    double x = x_pos[0]-dx*(!circular);


    for (unsigned int i = 0; i < num_ele+1+2*(!circular); i++) {
      temp_node.node_number = node_number++;
      temp_node.position[0] = x;
      
      node_vect.push_back(temp_node);

      x+=dx;
    }
  } else if (x_pos.size()>2) {
    /**
     * @brief This option meshes the 1d domain using a 2nd order Lagrange polynomial interpolation
     *
     */
    double xi = -1. -(!circular)*(2./num_ele);
    for (unsigned int i = 0; i < num_ele+1+2*(!circular); i++) {
      temp_node.node_number = node_number++;
      temp_node.position[0] = x_pos[0] * 0.5 * xi * (xi - 1.) \
                              - x_pos[1] * (xi*xi -1)  \
                              +x_pos[2] *0.5 * xi * (xi + 1.) ;
      
      node_vect.push_back(temp_node);

      xi+=(2./num_ele);
    }
  }
  for (unsigned int i = 0; i < num_ele+(!circular); i++) {
    temp_edge.edge_number = edge_number++;
    temp_edge.neighbor_elements = {i, i+1};
    if (circular && i == num_ele-1) {
      temp_edge.neighbor_elements = {i, 0};
    }

    temp_edge.unit_vector = {1.};
    temp_edge.edge_area = 1.;
    
    edge_vect[0].push_back(temp_edge);
  }
  for (unsigned int i = 0; i < num_ele+2*(!circular); i++) {
    temp_elem.elem_number = ele_number++;
    temp_elem.ghost = false;
    temp_elem.nodes = {&node_vect[i], &node_vect[i+1]};
    temp_elem.volume = temp_elem.nodes[1]->position[0]-temp_elem.nodes[0]->position[0];

    if ((!circular) &&(i==0 || i == num_ele+1)){
      temp_elem.ghost = true;
      ghost_elements.push_back(temp_elem.elem_number);
      temp_elem.volume = 1000.;
    }
    if (temp_elem.volume <= 0){
      throw std::invalid_argument("domain parameters result in negative element volume");
    }
    elem_vect.push_back(temp_elem);
  }
  ele_number = 0;
  for (auto ele: elem_vect) {
    element_volume[ele_number++] = ele.volume;
  }
  min_elem_vol = element_volume.min();
  num_ele_ = elem_vect.size();
}

//! 2D mesh constructor
Mesh::Mesh(std::vector<unsigned int> num_ele, std::vector<std::vector <double> > positions, std::vector<bool> circular): element_volume( (num_ele[0]+2*(!circular[0])) * (num_ele[1]+2*(!circular[1])) ), dim_(2)
{
    // Split edges based on orientation
    edge_vect.resize(2);
    
    Node temp_node;
    temp_node.position.resize(dim_);
    Edge temp_edge;
    temp_edge.unit_vector.resize(dim_);
    Elem temp_elem;
    temp_elem.nodes.resize(4);
    
    
    if (positions.size() < 2) {
        throw std::invalid_argument("wrong size of 2d domain");
    }else if (positions[0].size() < 2) {
        throw std::invalid_argument("wrong size of x domain");
    }else if (positions[1].size() < 2) {
        throw std::invalid_argument("wrong size of y domain");
    }

    // suppose [ [x0, x1],[y0, y1] ]
    double x0_ = positions[0][0];
    double x1_ = positions[0][1];
    double y0_ = positions[1][0];
    double y1_ = positions[1][1];

    int Elem_row_ = num_ele[0];
    int Elem_col_ = num_ele[1];

    int Node_row_ = Elem_row_ + 1 + 2 * (!circular[0]);
    int Node_col_ = Elem_col_ + 1 + 2 * (!circular[1]);

    double dx_ = ( x1_ - x0_ ) / double(Elem_col_);
    double dy_ = ( y1_ - y0_ ) / double(Elem_row_);
    
    for (int i = 0; i < Node_col_; i++){
        for (int j = 0; j< Node_row_; j++){

            temp_node.node_number = i*Node_row_ + j;

            temp_node.position[0] = x0_ + dx_ * (i-(!circular[0]));
            temp_node.position[1] = y1_ - dy_ * (j-(!circular[1]));

            node_vect.push_back(temp_node);
        }
    }
    
    
    for (unsigned int i = 0; i < num_ele[1] + 2 * (!circular[1]); i++){
        for (unsigned int j = 0; j < num_ele[0] + 2 * (!circular[0]); j++){

            temp_elem.elem_number = i * ( num_ele[0] + 2 * (!circular[0]) ) + j;

            temp_elem.nodes[0] = &node_vect[ j + i * ( num_ele[0] + 2 * (!circular[0]) + 1 ) + 1 ];    // node 1 #
            temp_elem.nodes[1] = &node_vect[ j + ( i + 1 ) * ( num_ele[0] + 2 * (!circular[0]) + 1 ) + 1 ];    // node 2 #
            temp_elem.nodes[2] = &node_vect[ j + ( i + 1 ) * ( num_ele[0] + 2 * (!circular[0]) + 1 ) ];    // node 3 #
            temp_elem.nodes[3] = &node_vect[ j + i * ( num_ele[0] + 2 * (!circular[0]) + 1 ) ];    // node 4 #
            
            temp_elem.volume = ( temp_elem.nodes[1]->position[0] - temp_elem.nodes[0]->position[0] ) * ( temp_elem.nodes[3]->position[1] - temp_elem.nodes[0]->position[1] );
            
            temp_elem.ghost = false;
            
            /*
            if ( (!circular[1]) && ( i == 0 || i == num_ele[1] + 1 ) && (!circular[0]) && ( j == 0 || j == num_ele[0] + 1 ) ){
                temp_elem.mega_ghost = true;
                mega_ghost_elements.push_back(temp_elem.elem_number);
                temp_elem.volume = 1000.;
            }*/
            
            if ( ( (!circular[1]) && ( i == 0 || i == num_ele[1] + 1 ) ) || ( (!circular[0]) && ( j == 0 || j == num_ele[0] + 1 ) ) ){
                temp_elem.ghost = true;
                ghost_elements.push_back(temp_elem.elem_number);
                temp_elem.volume = 1000.;
            }
            
            if (temp_elem.volume <= 0){
                  throw std::invalid_argument("domain parameters result in negative element volume");
            }

            elem_vect.push_back(temp_elem);
            
        }
    }
    
    
    for (unsigned int i = 0; i < num_ele[1]; i++){
        for (unsigned int j = 0; j < num_ele[0] + (!circular[0]); j++){
            
            temp_edge.edge_number = i * ( num_ele[0] + (!circular[0]) ) + j;
            
            temp_edge.neighbor_elements.first = ( i + (!circular[1]) ) * ( num_ele[0] + 2 * (!circular[0]) ) + j;
            temp_edge.neighbor_elements.second = ( i + (!circular[1]) ) * ( num_ele[0] + 2 * (!circular[0]) ) + j + 1;
            if ( circular[0] && j == num_ele[0] - 1 ) {
                temp_edge.neighbor_elements.second = ( i + (!circular[1]) ) * ( num_ele[0] + 2 * (!circular[0]) );
            }
            
            temp_edge.unit_vector = {0, -1};
            temp_edge.edge_area = 1.;
            
            edge_vect[0].push_back(temp_edge);
            
        }
    }
    
    for (unsigned int j = 0; j < num_ele[0]; j++){
        for (unsigned int i = 0; i < num_ele[1] + (!circular[1]); i++){
            
            temp_edge.edge_number = j * ( num_ele[1] + (!circular[1]) ) + i;
            
            temp_edge.neighbor_elements.first = i * ( num_ele[0] + 2 * (!circular[0]) ) + j + (!circular[1]);
            temp_edge.neighbor_elements.second = ( i + 1 ) * ( num_ele[0] + 2 * (!circular[0]) ) + j + (!circular[1]);
            if ( circular[1] && i == num_ele[1] - 1 ) {
                temp_edge.neighbor_elements.second = j + (!circular[1]);
            }
            
            temp_edge.unit_vector = {1, 0};
            temp_edge.edge_area = 1.;
            
            edge_vect[1].push_back(temp_edge);
            
        }
    }
    
}


std::ostream& operator<<(std::ostream& os, Mesh& mesh){
  os << "NODES\n";
  for (auto node: mesh.node_vect) {
    for (auto pos: node.position) {
      os << pos <<" ";
    }
    os << "\n";
  }
  os << "END_NODES\n";

  os << "ELEMENTS\n";
  for (auto element: mesh.elem_vect) {
    for (auto node: element.nodes) {
      os << node->node_number <<" ";
    }
    os << "\n";
  }
  os << "END_ELEMENTS" << std::endl;

  return os;
}


//! Getter funciton for the spatial dimension
unsigned int Mesh::dim() const {return dim_;}
//! Getter funciton for number of elments (including ghosts)
unsigned int Mesh::num_elements() const {return num_ele_;}




int main() {

  // --------------------- 1. testing output ---------------------
  // Mesh mesh1d(5, {0., 1.}, false);
  // std::cout << mesh1d;

  // Mesh mesh2d({2,2}, {{-1., 1.},{-1., 1.}}, {false, false});
  // std::cout << mesh2d;


  // --------------------- 2. testing echo ---------------------
  Mesh mesh({2,2}, {{-1., 1.},{-1., 1.}}, {false, false});
  std::cout<<"Edges: "<<std::endl;
  for (auto edges:mesh.edge_vect){
  for (auto edge :edges) {
    std::cout<<"#"<<edge.edge_number<<" Element 1: "<<edge.neighbor_elements.first<<" Element 2: "<<edge.neighbor_elements.second<<std::endl;
  }}

  std::cout<<"Elements: "<<std::endl;

  for (auto& elem :mesh.elem_vect) {
    std::cout<<"#"<<elem.elem_number<<" Volume: "<<elem.volume<<" Node 1: "<<elem.nodes[0]->node_number<<" Node 2: "<<elem.nodes[1]->node_number<<" Ghost\?: "<<elem.ghost<<std::endl;
    std::cout<<"Position node 1: "<<elem.nodes[0]->position[0]<<" Position node 2: "<<elem.nodes[1]->position[0]<<std::endl;

  }
  std::cout<<"Nodes: "<<std::endl;
  for (auto& node :mesh.node_vect) {
    std::cout<<"#"<<node.node_number<<" Position: "<<node.position[0]<<std::endl;
  }

  std::cout<<"Volume valarray:" <<std::endl;
  for (auto v:mesh.element_volume){
    std::cout<<v<<" ";
  }
  std::cout<<std::endl;

  std::cout<<"Ghost elements:" <<std::endl;
  for (auto v:mesh.ghost_elements){
    std::cout<<v<<" ";
  }
  std::cout<<std::endl;


  std::cout<<mesh;
  return 0;
}