/**
 * @file test_mesh1d.cpp
 * @author Bingjia Yang, Kehan Cai
 * @brief 
 * @version 0.1
 * @date 2021-12-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include <iostream>
#include <cmath>      

#include "../FluS/mesh.h"
#include "catch.hpp"

TEST_CASE( "Mesh1d data access and manipulation", "[mesh]" ) {
    
    unsigned int Num_Elems = 10;
    double x0 = -1;
    double x1 = 1;
    double dx = ( x1 - x0 ) / double(Num_Elems);
    
    // no circular
    Mesh mesh1d_false(Num_Elems, {x0, x1}, false);
    
    SECTION( "mesh1d  access" ) {

        REQUIRE( mesh1d_false.num_elements() == Num_Elems + 2);
        REQUIRE( mesh1d_false.dim() == 1);
    
    }
    
    SECTION( "Node vector access" ) {

        unsigned int idx = GENERATE (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
        
        REQUIRE( mesh1d_false.node_vect[idx].node_number == idx );
        
        REQUIRE( std::abs(mesh1d_false.node_vect[idx].position[0] - (x0 - dx + dx *idx )) < 0.0001 );
    
    }
    
    SECTION( "Element vector access" ) {
        unsigned int idx = GENERATE (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11);
        
        REQUIRE( mesh1d_false.elem_vect[idx].elem_number == idx );
        
        REQUIRE( mesh1d_false.elem_vect[idx].nodes[1]->node_number - mesh1d_false.elem_vect[idx].nodes[0]->node_number ==  1 );
        
        REQUIRE( std::abs(mesh1d_false.elem_vect[idx].volume  - dx) < 0.0001 );
        

    }
        
    SECTION( "Edge vector access" ) {
        unsigned int idx = GENERATE (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
        
        REQUIRE( mesh1d_false.edge_vect[0][idx].edge_number == idx );
        
        REQUIRE( mesh1d_false.edge_vect[0][idx].neighbor_elements.second - mesh1d_false.edge_vect[0][idx].neighbor_elements.first == 1 );  
    
    }
    
}