#include <iostream>
#include <valarray>
#include <array>


#include "../mocks/mesh_mock.h"

int main() {

  Mesh_1d_mock mesh(7,1., 11.);
  std::cout<<"Edges: "<<std::endl;
  for (auto& edge :mesh.edge_set) {
    std::cout<<"#"<<edge.edge_number<<" Element 1: "<<edge.neighbor_elements.first<<" Element 2: "<<edge.neighbor_elements.second<<std::endl;
  }

  std::cout<<"Elements: "<<std::endl;

  for (auto& elem :mesh.elem_set) {
    std::cout<<"#"<<elem.elem_number<<" Volume: "<<elem.volume<<" Node 1: "<<elem.nodes[0]<<" Node 2: "<<elem.nodes[1]<<" Ghost\?: "<<elem.ghost<<std::endl;
  }
  std::cout<<"Nodes: "<<std::endl;
  for (auto& node :mesh.node_set) {
    std::cout<<"#"<<node.node_number<<" Position: "<<node.position[0]<<std::endl;
  }

  std::cout<<"Volume valarray:" <<std::endl;
  for (auto v:mesh.element_volume){
    std::cout<<v<<" ";
  }
  std::cout<<std::endl;
  return 0;
}


