#include "catch.hpp"
#include "SOjsonAssign/BaseClass.h"
#include "string.h"

using namespace std;

TEST_CASE( "SOjsonAssign BaseClass Method tests", "[SOjsonAssignBaseClass]" ) {

  BaseClass cl;

  SECTION("Method one returns 1") {
    REQUIRE( (cl.one()) == 1);
  }
}
