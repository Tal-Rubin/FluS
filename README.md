\mainpage

# FluS

## Synopsis

FluS (Fluid Solver) is a multidimensional finite volume fluid solver. Several models are implemented, such as advection, and Euler equations, in one and two dimensions.

## Installation and dependencies

FluS was tested in a Linux environment. A few submodules of FluS call upon the OS.

The FluS visualization tool (post-processor) uses Python, with the Numpy and Matplotlib libraries. We recommend using Anaconda (https://www.anaconda.com/) for the Python and libraries distribution. 

The documentation is generated using Doxygen (https://www.doxygen.nl/index.html). Doxygen uses Graphviz (http://www.graphviz.org/) to generate some figures. 

**FluS configuration file is read using Libconfig (http://hyperrealm.github.io/libconfig/).**

Cmake (version >= 3.10) is required, as well as a C++ compiler, using the C++14 standard and up.

### Generating the documentation

From the root (FluS) directory, run:

```bash
$ doxygen
```

Doxygen generates a folder `documentation` with two sub-folders: 
1. `html` - containing web-based documentation. Accessible through `index.htm`.
2. `latex` - containing tex files. 

#### Generating the Latex documentation

From the root (FluS) directory, run:

```bash
$ cd documentation/latex
$ make
```

The latex documentaion is in `refman.pdf`.

## Building the code

From the root (FluS) directory, run:

```bash
$ mkdir build  
$ cd build
$ cmake ../
$ cmake --Build .
$ make
```

## Executables and sub-programs

### To run FluS

From the root (FluS) directory, run:
```bash
$ cd build
$ src/FluS/./FluS ../src/FluS/FluSConfig.cfg > data.txt
```

Two pre-set config files are saved:
1. `FluSConfigAdvection.cfg` 1d advection with periodic domain.
2. `FluSConfigEuler.cfg` 1d Euler equations with constant bounday conditions - two rarefaction wave solutions.


### To run the post-processor

From the root (FluS) directory, run:
```bash
$ cd build
$ python ../src/FluS/FluSPostProc.py
```

### Exact Reimann solver for Euler equaitons
From the root (FluS) directory, run:
```bash
$ cd build
$ python ../src/exactRS/ersWrap.py
```

#### Other executables

Other executables are located in `src/dev` and are used to print stuff to console. They are used in developent.

## Unit testing

From the root (FluS) directory, run:
```bash
$ cd build
$ make test
```


