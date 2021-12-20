/**
 * @file mesh.h
 * @author Tal Rubin (trubin@princeton.edu), Bingjia Yang, Kehan Cai
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

/// @brief The type used to identify an edge
struct Edge {

  /// @brief The ID of this edge
  unsigned int edge_number;

  /// @brief The pair of neighbor elements of this edge
  std::pair<unsigned int, unsigned int> neighbor_elements;
  
  /// @brief The orientation of this edge
  std::valarray<double> unit_vector;

  /// @brief The area of this edge
  double edge_area;
};

/// @brief The type used to identify a node
struct Node {

  /// @brief The ID of this node
  ///
  /** @verbatim
    The node numbering example (1D):
    1 → 2 → 3 → 4 → 5 → 6 @endverbatim
    */
  /** @verbatim
   The node numbering example (2D):
    1↓  4↓  7↓
    2↓  5↓  8↓
    3↓  6↓  9↓ @endverbatim
    */
  unsigned int node_number;
  /// @brief The position of this node
  ///
  /// In 1D, the position of a node is represented by x coordinate
  /// In 2D, the position of a node is represented by x and y coordinates
  std::valarray<double> position;
};

/// @brief The type used to identify an element
struct Elem {

  /// @brief The ID of this element
  ///
  /** @verbatim
    The element numbering example (1D):
    1→|__| 2→|__| 3→|__|  @endverbatim
    */
  /** @verbatim
    The element numbering example (2D):
       __     __
    1↓|__| 3↓|__|
    2↓|__| 4↓|__| @endverbatim
    */
  unsigned int elem_number;

  /// @brief The nodes inside this element
  ///
  /// In 1D, there are 2 nodes(left node and right node) in each element
  /** @verbatim
    The node numbering in each element (1D):
       |___|
      0     1 @endverbatim
    */
  /// In 2D, there are 4 nodes in each element
  /** @verbatim
    The node numbering in each element (2D):
      3 ____ 2
       |    |
       |____|
      0      1  @endverbatim
    */
  std::vector<Node *> nodes;

  /// @brief The volume of each element
  double volume;

  /// @brief Return true if it is a ghost element
  bool ghost;
};



struct mesh_parameters {
    unsigned int dimension;
    
};


class Mesh {
public:
  //! 1D mesh constructor
  Mesh(unsigned int num_ele, std::vector<double> x_pos, bool circular);
  
  //! 2D mesh constructor
  ///
  /// num_ele = {num_row, num_col}, evenly meshing: { {x0, x1},{y0, y1} }
  Mesh(std::vector<unsigned int> num_ele, std::vector<std::vector <double> > positions, std::vector<bool> circular);


  //! Getter funciton for the spatial dimension
  unsigned int dim() const;
  //! Getter funciton for number of elments (including ghosts)
  unsigned int num_elements() const;
  //! Output operator overload.
  friend std::ostream& operator<<(std::ostream& os, Mesh& mesh1d);



  std::valarray<double> element_volume;

  /// @brief [hori_vect, vert_vect]
  std::vector<std::vector<Edge> > edge_vect;
  std::vector<Elem> elem_vect;
  std::vector<Node> node_vect;

  std::vector<unsigned int> ghost_elements;

  double min_elem_vol;


private:
  unsigned int dim_;
  unsigned int num_ele_;

};

#endif  // FLUS_MESH_H_

