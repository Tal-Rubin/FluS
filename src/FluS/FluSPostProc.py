##
#  @file FluSPostProc.py
#  @author Tal Rubin (trubin@princeton.edu)
#  @brief Data collection and plotting 
#  @version 0.1
#  @date 2021-12-07
# 
#  @copyright Copyright (c) 2021



import numpy as np
import matplotlib.pyplot as plt
from numpy.core.numeric import empty_like

##
# @brief Reads the mesh geometry
#
# @param filename The mesh geometry file path, name.
# @return dim The space dimention of the mesh, nodes numpy array of node coordinates, 
# elem numpy array of node numbers per element.
#
# The geometry file is divided to nodes, between "NODES" and "END_NODES", 
# and elements, between "ELEMENTS" and "END_ELEMENTS".
# Each line in the node section has the coordinates of a node X Y ...
# Each line in the element section has node numbers, in a CONTERCLOCKWISE manner (in 2D), or increaing in 1D.
#
# This funciton can read only one type of elements (line segments, tri-s or quads).


def read_geometry(filename = 'mesh.txt'):
  lines = []
  with open(filename) as geomfile:
      copy = False
      for line in geomfile:
          if line.strip() == "NODES":
              copy = True
              continue
          elif line.strip() == "END_NODES":
              copy = False
              continue
          elif copy:
              lines.append(line)
  test = np.fromstring(lines[0], dtype=float, sep=' ')
  dim = len(test)
  nodes = np.zeros((len(lines), dim), dtype = float)     

  for i in range(len(lines)):
      nodes[i,:] = np.fromstring(lines[i], dtype=float, sep=' ')

  lines = []
  with open(filename) as infile:
      copy = False
      for line in infile:
          if line.strip() == "ELEMENTS":
              copy = True
              continue
          elif line.strip() == "END_ELEMENTS":
              copy = False
              continue
          elif copy:
            lines.append(line)

  test = np.fromstring(lines[0], dtype = int, sep=' ')
  el_shape = len(test)

  elem = np.zeros((len(lines),el_shape),dtype = int)     

  for i in range(len(lines)):
      elem[i,:] = np.fromstring(lines[i], dtype=int, sep=' ')

  return dim, nodes, elem




##
# @brief Splits quadrilateral elements into triangular elements for plotting.
#
# @param elem numpy array of quadrilateral element nodes.
# @return elemtri numpy array of triangular element nodes.
#
def split_quad_to_tri(elem):
  elemtri = elem.repeat(2,axis=0)
  elemtri[1::2,1:3] = elemtri[1::2,2:4]

  elemtri = elemtri[:,0:3]

  return elemtri

##
# @brief Duplicates data to be plotted using plt.tripcolor on a quad mesh, to be used with split geometry from split_quad_to_tri(elem)
#
# @param elem numpy array of data.
# @return numpy array of data to be plotted.
#
def split_data(data):
  return data.repeat(2, axis = 2)


def plot_frame(dim, nodes, elem, data, time, x_plot_grid, y_plot_grid,filename):
  fig = plt.figure(figsize=[10, 8])
  fig.suptitle("t = {}".format(time))

  if dim == 1:
    for i in range(x_plot_grid*y_plot_grid):
      ax = fig.add_subplot(x_plot_grid, y_plot_grid,i+1)
      x = nodes.repeat(2,axis=0)
      y = np.zeros(2*len(data[i,:])+2)
      y[1:-1] = data[i].repeat(2,axis=0)

      ax.plot(x,y)
      ax.set_xlabel("x")

  elif dim == 2:
    for i in range(x_plot_grid*y_plot_grid):
      ax = fig.add_subplot(x_plot_grid, y_plot_grid,i+1)
      tcf = ax.tripcolor(nodes[:,0], nodes[:,1], elem, data[i])
      ax.set_xlabel("x")
      ax.set_ylabel("y")
      fig.colorbar(tcf)


  else: 
    print("No plotting is implemented to this data mesh dimension")
    return

  plt.tight_layout()
  plt.savefig(filename)


def read_data(filename = "data.txt"):
  fields, params = np.genfromtxt(filename, dtype = int, delimiter=' ',max_rows=1)
  file_data = np.genfromtxt(filename, dtype = float, delimiter=' ',skip_header=1, skip_footer = 1)
  time = file_data[:,0]  

  num_ele = int( (file_data.shape[1]-1) / (fields * params))

  data = np.zeros((len(time),fields, num_ele))  

  for i in range(fields):
    for j in range(params):  
      data[:,i+j] = file_data[:,1+(i+j)*num_ele:1+(i+j+1)*num_ele]

  return time, data


def plotFluS(geomfile, datafile):
  time, data = read_data(datafile)
  dim, nodes, elem = read_geometry(geomfile)

  i=0
  plot_frame(dim, nodes, elem, data[i], time[i],1,1)


if __name__ == '__main__':
  splitted = False
  dim, nodes, elem = read_geometry("src/test/mesh.txt")
  if elem.shape[1]==4:
    elem = split_quad_to_tri(elem)
    splitted = True
  time, data = read_data("src/test/data.txt")
  if splitted:
    data = split_data(data)

  for i in range(len(time)):
    plot_frame(dim, nodes, elem, data[i,:,:], time[i],1,data.shape[1],"src/FluS/save/fig"+str(i)+".png")

