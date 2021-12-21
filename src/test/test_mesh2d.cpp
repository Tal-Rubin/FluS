#include <iostream>

#include "../FluS/mesh.h"
#include "../FluS/mesh.cpp"
#include "catch.hpp"


TEST_CASE( "Mesh2d data access and manupulation", "[mesh2d]" ) {
    SECTION( "mesh in 2D" ) {
        std::vector<unsigned int> num_ele = {2, 3};
        std::vector<std::vector <double> > positions = {{-1., 1.},{-1., 1.}};
        double dx = ( positions[0][1] - positions[0][0] ) / double(num_ele[1]);
        double dy = ( positions[1][1] - positions[1][0] ) / double(num_ele[0]);
        bool bc1 = GENERATE(true, false);
        bool bc2 = GENERATE(true, false);
        std::vector<bool> circular = {bc1, bc2};
        
        Mesh mesh({2,3}, {{-1., 1.},{-1., 1.}}, circular);
        
        SECTION( "mesh basic quantities verify" ) {
            REQUIRE( mesh.dim() == 2 );
            REQUIRE( mesh.num_elements() == (num_ele[0]+2*(!circular[0])) * (num_ele[1]+2*(!circular[1])) );
        }
        
        SECTION( "Node vector test" ) {
            int idx_row = GENERATE (0, 1);
            int idx_col = GENERATE (0, 1, 2);
            
            REQUIRE( mesh.node_vect[idx_row + idx_col * ( num_ele[0] + 1 + 2 * (!circular[0]) )].node_number == idx_row + idx_col * ( num_ele[0] + 1 + 2 * (!circular[0]) ) );
            
            REQUIRE( mesh.node_vect[idx_row + idx_col * ( num_ele[0] + 1 + 2 * (!circular[0]) )].position[0] == positions[0][0] + dx * ( idx_col - (!circular[0]) ) );
            REQUIRE( mesh.node_vect[idx_row + idx_col * ( num_ele[0] + 1 + 2 * (!circular[0]) )].position[1] == positions[1][1] - dy * ( idx_row - (!circular[1]) ) );
        }
        
        SECTION( "Element vector test" ) {
            int idx_row = GENERATE (0, 1);
            int idx_col = GENERATE (0, 1, 2);
            
            REQUIRE( mesh.elem_vect[idx_row + idx_col * ( num_ele[0] + 2 * (!circular[0]) )].elem_number == idx_row + idx_col * ( num_ele[0] + 2 * (!circular[0]) ) );
            
            REQUIRE( mesh.elem_vect[idx_row + idx_col * ( num_ele[0] + 2 * (!circular[0]) )].nodes[1]->node_number - mesh.elem_vect[idx_row + idx_col * ( num_ele[0] + 2 * (!circular[0]) )].nodes[0]->node_number ==  num_ele[0] + 2 * (!circular[0]) + 1 );
            REQUIRE( mesh.elem_vect[idx_row + idx_col * ( num_ele[0] + 2 * (!circular[0]) )].nodes[0]->node_number - mesh.elem_vect[idx_row + idx_col * ( num_ele[0] + 2 * (!circular[0]) )].nodes[3]->node_number ==  1 );
            
            // REQUIRE( mesh.elem_vect[idx_row + idx_col * ( num_ele[0] + 2 * (!circular[0]) )].volume == dx * dy );
            
        }
        
        SECTION( "Edge vector test" ) {
            int idx_row = GENERATE (0);
            int idx_col = GENERATE (0, 1);

            REQUIRE( mesh.edge_vect[0][idx_row + idx_col * ( num_ele[0] + (!circular[0]) )].edge_number == idx_row + idx_col * ( num_ele[0] + (!circular[0]) ) );

            REQUIRE( mesh.edge_vect[0][idx_row + idx_col * ( num_ele[0] + (!circular[0]) )].neighbor_elements.second - mesh.edge_vect[0][idx_row + idx_col * ( num_ele[0] + (!circular[0]) )].neighbor_elements.first == 1 );


            REQUIRE( mesh.edge_vect[1][idx_col + idx_row * ( num_ele[1] + (!circular[1]) )].edge_number == idx_col + idx_row * ( num_ele[1] + (!circular[1]) ) );

            REQUIRE( mesh.edge_vect[1][idx_col + idx_row * ( num_ele[1] + (!circular[1]) )].neighbor_elements.second - mesh.edge_vect[1][idx_col + idx_row * ( num_ele[1] + (!circular[1]) )].neighbor_elements.first == num_ele[0] + 2 * (!circular[0]) );

        }
        
    }
     
    
}
