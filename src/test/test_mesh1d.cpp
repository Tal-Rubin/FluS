#include <iostream>

#include "../FluS/mesh1d.cpp"

#include "catch.hpp"

TEST_CASE( "Mesh1d data access and manipulation", "[mesh1d]" ) {
    
    int Num_Elems = 10;
    double x0 = -1;
    double x1 = 1;
    double dx = ( x1 - x0 ) / double(Num_Elems);
    
    Mesh1D* mesh1d = new Mesh1D(Num_Elems, x0, x1);
    
    SECTION( "mesh1d pointer access" ) {
        REQUIRE( mesh1d->n_elements() == Num_Elems );
        REQUIRE( mesh1d->n_interfaces() == Num_Elems + 1 );
    }
    //
    std::vector<Node> nodeVector = mesh1d->get_NodeVector();
    
    SECTION( "Node vector access" ) {
        int idx = GENERATE (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
        
        REQUIRE( nodeVector[idx].node_number == idx );
        
        REQUIRE( nodeVector[idx].position[0] == x0 + dx * ( idx - 1 ) );
    }
    
    std::vector<Elem> elemVector = mesh1d->get_ElemVector();
    
    SECTION( "Element vector access" ) {
        int idx = GENERATE (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11);
        
        REQUIRE( elemVector[idx].elem_number == idx );
        
        REQUIRE( elemVector[idx].nodes[1]->node_number - elemVector[idx].nodes[0]->node_number ==  1 );
        
        REQUIRE( elemVector[idx].volume == dx );
        
    }
    
    std::vector<Edge> edgeVector = mesh1d->get_EdgeVector();
    
    SECTION( "Edge vector access" ) {
        int idx = GENERATE (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
        
        REQUIRE( edgeVector[idx].edge_number == idx );
        
        REQUIRE( edgeVector[idx].neighbor_elements.second->elem_number - edgeVector[idx].neighbor_elements.first->elem_number == 1 );
        
    }
    
}

