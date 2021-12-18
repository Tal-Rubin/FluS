/**
 * @file echo_mesh2.cpp
 * @author Tal Rubin (trubin@princeton.edu)
 * @brief 
 * @version 0.1
 * @date 2021-12-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>

#include "../mocks/mesh.h"

int main() {

  Mesh mesh(7,std::vector<double> {0.,0.7, 1.}, false);
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


