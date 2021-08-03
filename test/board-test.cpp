#include "catch.hpp"
#include "../board.h"

const double EPSILON = 1e-5;

TEST_CASE("checking board class") {
    Board test(4);
    
    REQUIRE(test.getPlayer(0) == NULL);
    REQUIRE(test.getPlayerAmount() == 4);
    Player testPlayer(0);
    test.savePlayer(&testPlayer, 0);
    REQUIRE(test.whichInMiddle() == 0);
    test.startPlayer(0);
    REQUIRE(test.isValidCell(testPlayer, static_cast<Direction>(2)) == false);
    REQUIRE(test.isValidCell(testPlayer, static_cast<Direction>(0)) == true);
    REQUIRE(test.setPlayer(testPlayer, static_cast<Direction>(0)) == true);
    REQUIRE(test.setBlock(3, 3, static_cast<Direction>(0)) == true);
    REQUIRE((test.getDistance(test.getPlayer(0)) - 7.0710678119) <= EPSILON);
}