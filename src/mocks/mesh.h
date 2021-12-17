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

#ifndef FLUS_MESH_H_
#define FLUS_MESH_H_


#include <valarray>
#include <vector>
#include <utility>
#include <iostream>


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
  //! 1D mesh constructor
  Mesh(unsigned int num_ele, std::vector<double> x_pos, bool circular);
  
  


  //! Getter funciton for the spatial dimension
  unsigned int dim() const;
  //! Getter funciton for number of elments (including ghosts)
  unsigned int num_elements() const;  
  //! Output operator overload.
  friend std::ostream& operator<<(std::ostream& os, Mesh& mesh1d);



  std::valarray<double> element_volume;
  std::vector<std::vector<Edge>> edge_vect;
  std::vector<Elem> elem_vect;
  std::vector<Node> node_vect;

  std::vector<unsigned int> ghost_elements;

  double min_elem_vol;


  private:
  unsigned int dim_;
  unsigned int num_ele_;

};

#endif  // FLUS_MESH_H_
