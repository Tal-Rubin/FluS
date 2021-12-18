##
# @file ersWrap.py
# @author Tal Rubin (trubin@princeton.edu)
# @brief 
# @version 0.1
# @date 2021-12-17


import os
import numpy as np
import matplotlib.pyplot as plt

def runErsTest():
  params = [1., 0., 0., 0., 1., .125, 0., 0., 0., .10, 0.25]
  command_str = "src/exactRS/./testErs"
  command_str += " {}".format(params[0])
  if len(params) == 11:
    for i in range(10):
      command_str += " {}".format(params[i+1])
  command_str += " > output.txt"
  print(command_str)
  os.system(command_str)


def readErs(datafile="output.txt"):
    header = np.genfromtxt(datafile, max_rows=1)
    gamma = header


    data = np.genfromtxt(datafile, skip_header=1)
    x = data[:, 0]
    rho = data[:, 1]
    u = data[:, 2]
    v = data[:, 3]
    w = data[:, 4]
    p = data[:, 5]

    return [gamma, x, rho, u, v, w, p]


def plotErs(vars):
  [gamma, x, rho, u, v, w, p] = vars
  fig, axarr = plt.subplots(3, 3, figsize=[10, 8])
  
  axarr[0, 0].plot(x, rho)
  axarr[0, 0].set_title("$\\rho$")
  
  axarr[1, 0].plot(x, p)
  axarr[1, 0].set_title("$p$")

  axarr[2, 0].plot(x, 0.5*rho*(u**2+v**2+w**2)+p/(gamma-1))
  axarr[2, 0].set_title("$E$")


  axarr[0, 1].plot(x, u)
  axarr[0, 1].set_title("$u$")

  axarr[1, 1].plot(x, v)
  axarr[1, 1].set_title("$v$")

  axarr[2, 1].plot(x, w)
  axarr[2, 1].set_title("$w$")


  axarr[0, 2].plot(x, rho*u)
  axarr[0, 2].set_title("$\\rho u$")

  axarr[1, 2].plot(x, rho*v)
  axarr[1, 2].set_title("$\\rho v$")

  axarr[2, 2].plot(x, rho*w)
  axarr[2, 2].set_title("$\\rho w$")

  plt.tight_layout()
  plt.show()

if __name__=='__main__':
  runErsTest()
  plotErs(readErs())