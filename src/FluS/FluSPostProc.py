##
#  @file FluSPostProc.py
#  @author Tal Rubin (trubin@princeton.edu)
#  @brief Data collection and plotting 
#  @version 0.1
#  @date 2021-12-07
# 
#  @copyright Copyright (c) 2021


import os
import numpy as np
import matplotlib.pyplot as plt
import shutil
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
  return data.repeat(2, axis = 3)

##
# @brief Plots time-slice, cell-average data, and saves the image.
#
# @param dim 1 or 2 dimensional domain: line plot or contour plot
# @param nodes Location of element vertices
# @param elem Indices of nodes associated with each element 
# @param data Data to be plotted
# @param time Time label of the frame
# @param x_plot_grid Display shape, number of horizontal frames in a figure
# @param y_plot_grid Display shape, number of vertical frames in a figure
# @param filename Filename for the figure to be saved as
# 
# This function plots cell averages (Finite-Volumes)
def plot_frame(dim, nodes, elem, data, time, x_plot_grid, y_plot_grid, filename):
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
  fig.clf()
  plt.close()
##
# @brief Reads the FluS solution from the saved file
#
# @param filename The data file path to be read.
# @return Numpy array of time labels, and numpy array of the read data.
#
def read_data(filename = "data.txt"):
  fields, params = np.genfromtxt(filename, dtype = int, delimiter=' ',max_rows=1)
  file_data = np.genfromtxt(filename, dtype = float, delimiter=' ',skip_header=1, skip_footer = 1)
  time = file_data[:,0]  

  num_ele = int( (file_data.shape[1]-1) / (fields * params))

  data = np.zeros((len(time),fields,params,num_ele))  

  for i in range(fields):
    for j in range(params):  
      data[:,i,j] = file_data[:,1+(i+j)*num_ele:1+(i+j+1)*num_ele]

  return time, data




if __name__ == '__main__':
  save_dir_path = '../src/FluS/save'
  if os.path.isdir(save_dir_path):
    shutil.rmtree(save_dir_path)
  os.makedirs(save_dir_path)
  dim, nodes, elem = read_geometry("../src/test/mesh.txt")  
  time, data = read_data("../src/test/data.txt")

  if elem.shape[1]==4:
    elem = split_quad_to_tri(elem)
    data = split_data(data)
  for i in range(len(time)):
    plot_frame(dim, nodes, elem, data[i,:,0,:], time[i],1,data.shape[1],save_dir_path+"/fig{:0>5d}.png".format(i))
  os.system('convert -delay 20 -loop 0 '+save_dir_path+'/*.png '+save_dir_path+'/plot.gif')
