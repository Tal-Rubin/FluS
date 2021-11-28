#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

int f();



int f(){
  return 0;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( f() == 1 );
}