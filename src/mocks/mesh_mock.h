/**
 * @file mesh_mock.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef FLUS_MOCK_MESH_H_
#define FLUS_MOCK_MESH_H_


#include <valarray>
#include <array>
#include <vector>
#include <utility>

struct Edge {
  unsigned int edge_number;
  std::pair<unsigned int, unsigned int> neighbor_elements;
  std::valarray<double> unit_vector;
};
struct Node {
  unsigned int node_number;
  std::array<double,1> position;
};

struct Elem {
  unsigned int elem_number;
  std::array<Node *,2> nodes;
  double volume;
  bool ghost;
};


/*
struct EdgeCmp {
  bool operator()(const Edge& lhs, const Edge& rhs) const { 
    return lhs.edge_number < rhs.edge_number; 
  }
};
struct ElemCmp {
  bool operator()(const Elem& lhs, const Elem& rhs) const { 
    return lhs.elem_number < rhs.elem_number; 
  }
};
struct NodeCmp {
  bool operator()(const Node& lhs, const Node& rhs) const { 
    return lhs.node_number < rhs.node_number; 
  }
};
*/
class Mesh_1d_mock {
  public:
  Mesh_1d_mock(unsigned int num_ele, double x0, double x1): element_volume(num_ele+2){
    unsigned int node_number = 0;
    unsigned int edge_number = 0;
    unsigned int ele_number = 0;
    
    const double dx = (x1-x0)/num_ele;

    double x = x0-dx;

    Node temp_node;
    Edge temp_edge;
    Elem temp_elem;


    for (unsigned int i = 0; i < num_ele+3; i++) {
      temp_node.node_number = node_number++;
      temp_node.position[0] = x;
      
      node_vect.push_back(temp_node);

      x+=dx;
    }
    for (unsigned int i = 0; i < num_ele+1; i++) {
      temp_edge.edge_number = edge_number++;
      temp_edge.neighbor_elements = {i, i+1};
      temp_edge.unit_vector = {1};
      
      edge_vect.push_back(temp_edge);
    }
    for (unsigned int i = 0; i < num_ele+2; i++) {
      temp_elem.elem_number = ele_number++;
      temp_elem.volume = dx;
      temp_elem.ghost = false;
      temp_elem.nodes = {&node_vect[i], &node_vect[i+1]};

      if (i==0 ||i == num_ele+1){
        temp_elem.ghost = true;
        ghost_elements.push_back(temp_elem.elem_number);
      }
      elem_vect.push_back(temp_elem);
    }
    ele_number = 0;
    for (auto ele: elem_vect) {
      element_volume[ele_number++] = ele.volume;
    }
    min_elem_vol = element_volume.min();

  };

  std::valarray<double> element_volume;
  std::vector<Edge> edge_vect;
  std::vector<Elem> elem_vect;
  std::vector<Node> node_vect;

  std::vector<unsigned int> ghost_elements;

  double min_elem_vol;


};


#endif  // FLUS_MOCK_MESH_H_