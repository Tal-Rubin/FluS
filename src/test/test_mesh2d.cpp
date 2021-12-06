#include <iostream>

#include "../FluS/mesh2d.cpp"

#include "catch.hpp"


TEST_CASE( "Mesh2d data access and manupulation", "[mesh2d]" ) {
    
    int Elem_row = 3;
    int Elem_col = 4;
    double x0 = -1;
    double x1 = 1;
    double y0 = -1;
    double y1 = 1;
    double dx = ( x1 - x0 ) / double(Elem_col);
    double dy = ( y1 - y0 ) / double(Elem_row);
    
    Mesh2D* mesh2d = new Mesh2D(Elem_row, Elem_col, x0, x1, y0, y1);
    
    SECTION( "mesh2d pointer access" ) {
        REQUIRE( mesh2d->n_elements() == Elem_row * Elem_col );
        REQUIRE( mesh2d->n_interfaces() == ( Elem_row + 1 ) * Elem_col + ( Elem_col + 1 ) * Elem_row );
    }
    
    std::vector<Node> nodeVector = mesh2d->get_NodeVector();
    
    SECTION( "Node vector access" ) {
        int idx_row = GENERATE (0, 1, 2, 3, 4, 5);
        int idx_col = GENERATE (0, 1, 2, 3, 4, 5, 6);
        
        REQUIRE( nodeVector[idx_row + idx_col * ( Elem_row + 3 )].node_number == idx_row + idx_col * ( Elem_row + 3 ) );
        
        REQUIRE( nodeVector[idx_row + idx_col * ( Elem_row + 3 )].position[0] == x0 + dx * ( idx_col - 1 ) );
        REQUIRE( nodeVector[idx_row + idx_col * ( Elem_row + 3 )].position[1] == y1 - dy * ( idx_row - 1 ) );
    }
    
    std::vector<Elem> elemVector = mesh2d->get_ElemVector();
    
    SECTION( "Element vector access" ) {
        int idx_row = GENERATE (0, 1, 2, 3, 4);
        int idx_col = GENERATE (0, 1, 2, 3, 4, 5);
        
        REQUIRE( elemVector[idx_row + idx_col * ( Elem_row + 2 )].elem_number == idx_row + idx_col * ( Elem_row + 2 ) );
        
        REQUIRE( elemVector[idx_row + idx_col * ( Elem_row + 2 )].nodes[2]->node_number - elemVector[idx_row + idx_col * ( Elem_row + 2 )].nodes[1]->node_number ==  Elem_row + 3 );
        REQUIRE( elemVector[idx_row + idx_col * ( Elem_row + 2 )].nodes[3]->node_number - elemVector[idx_row + idx_col * ( Elem_row + 2 )].nodes[0]->node_number ==  Elem_row + 3 );
        
        REQUIRE( elemVector[idx_row + idx_col * ( Elem_row + 2 )].volume == dx * dy );
        
    }
    
    std::vector<Edge> horiedgeVector = mesh2d->get_HoriEdgeVector();
    
    SECTION( "Hori-Edge vector access" ) {
        int idx_row = GENERATE (0, 1, 2, 3);
        int idx_col = GENERATE (0, 1, 2, 3);
        
        REQUIRE( horiedgeVector[idx_row + idx_col * ( Elem_row + 1 )].edge_number == idx_row + idx_col * ( Elem_row + 1 ) );
        
        REQUIRE( horiedgeVector[idx_row + idx_col * ( Elem_row + 1 )].neighbor_elements.second->elem_number - horiedgeVector[idx_row + idx_col * ( Elem_row + 1 )].neighbor_elements.first->elem_number == 1 );
        
    }
    
    std::vector<Edge> vertedgeVector = mesh2d->get_VertEdgeVector();
    
    SECTION( "Vert-Edge vector access" ) {
        int idx_row = GENERATE (0, 1, 2);
        int idx_col = GENERATE (0, 1, 2, 3, 4);
        
        REQUIRE( vertedgeVector[idx_col + idx_row * ( Elem_col + 1 )].edge_number == idx_col + idx_row * ( Elem_col + 1 ) );
        
        REQUIRE( vertedgeVector[idx_col + idx_row * ( Elem_col + 1 )].neighbor_elements.second->elem_number - vertedgeVector[idx_col + idx_row * ( Elem_col + 1 )].neighbor_elements.first->elem_number == Elem_row + 2 );
        
    }
     
    
}
