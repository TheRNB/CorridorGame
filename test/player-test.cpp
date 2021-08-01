#include "catch.hpp"
#include "../player.h"

TEST_CASE("testing Player class") {
    Player test(0);
    REQUIRE(test.getId() == 0);
    test.setPos(-4, 1209478);
    REQUIRE(test.getPosX() == -4);
    REQUIRE(test.getPosY() == 1209478);
}