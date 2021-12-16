/**
 * @file mesh.h
 * @author Tal Rubin (trubin@princeton.edu)
 * @brief 
 * @version 0.1
 * @date 2021-12-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef FLUS_MOCK_MESH_H_
#define FLUS_MOCK_MESH_H_


#include <valarray>
#include <vector>
#include <utility>
#include <stdexcept>
#include <iostream>


//#include "../FluS/mesh.h"

struct Edge {
  unsigned int edge_number;
  std::pair<unsigned int, unsigned int> neighbor_elements;
  std::valarray<double> unit_vector;
  double edge_area;
};
struct Node {
  unsigned int node_number;
  std::valarray<double> position;
};

struct Elem {
  unsigned int elem_number;
  std::vector<Node *> nodes;
  double volume;
  bool ghost;
};


class Mesh {
  public:
  Mesh(unsigned int num_ele, std::vector<double> x_pos, bool circular): element_volume(num_ele+2*(!circular)) {
    unsigned int node_number = 0;
    unsigned int edge_number = 0;
    unsigned int ele_number = 0;
    Node temp_node;
      temp_node.position.resize(1);
    Edge temp_edge;
      temp_edge.unit_vector.resize(1);
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
      
      edge_vect.push_back(temp_edge);
    }
    for (unsigned int i = 0; i < num_ele+2*(!circular); i++) {
      temp_elem.elem_number = ele_number++;
      temp_elem.ghost = false;
      temp_elem.nodes = {&node_vect[i], &node_vect[i+1]};
      temp_elem.volume = temp_elem.nodes[1]->position[0]-temp_elem.nodes[0]->position[0];
      if (temp_elem.volume <= 0){
        throw std::invalid_argument("domain parameters result in negative element volume");
      }
      if ((!circular) &&(i==0 || i == num_ele+1)){
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
    num_ele_ = elem_vect.size();
  };

  std::valarray<double> element_volume;
  std::vector<Edge> edge_vect;
  std::vector<Elem> elem_vect;
  std::vector<Node> node_vect;

  std::vector<unsigned int> ghost_elements;

  double min_elem_vol;
  unsigned int num_ele_;


};


#endif  // FLUS_MOCK_MESH_H_
