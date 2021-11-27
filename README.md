# FluS
## to build
mkdir build  
cd build
cmake ../
cmake --Build .

## To run the exact Reimann solver
python ../src/exactRS/ersWrap.py


in Flus:
doxygen
cd documentation/latex
make

refman.pdf

