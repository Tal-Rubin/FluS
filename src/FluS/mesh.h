/**
 * @file mesh.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef FLUS_MESH_H_
#define FLUS_MESH_H_






class Mesh {
  public:

  Mesh();

  ~Mesh();

  int dim();

  int n_elements();

  int n_interfaces(); // in 1D, is the number of points on element edges, in 2D is the number of elements edges, in 3D is the number of faces, etc.

  double el_volume(int element);

};

#endif // FLUS_MESH_H_
