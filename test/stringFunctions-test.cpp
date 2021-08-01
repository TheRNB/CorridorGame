#include "catch.hpp"
#include "../utils/stringFunctions.h"

TEST_CASE("testing stringIsInt") {
    REQUIRE(stringIsInt("123321") == true);
    REQUIRE(stringIsInt("123\n2") == false);
    REQUIRE(stringIsInt("") == false);
    REQUIRE(stringIsInt(" ") == false);
    REQUIRE(stringIsInt("0") == true);
}

TEST_CASE("testing string2Int") {
    REQUIRE(string2Int("123456") == 123456);
    REQUIRE(string2Int("0") == 0);
    REQUIRE(string2Int("9") == 9);
}

TEST_CASE("testing int2String") {
    REQUIRE(int2String(11) == "11");
    REQUIRE(int2String(123345) == "123345");
    REQUIRE(int2String(0) == "0");
}

TEST_CASE("testing stringFind") {
    REQUIRE(stringFind("abc", "abc") == 0);
    REQUIRE(stringFind("dd", "d") == 0);
    REQUIRE(stringFind("a 1\nf", "\nf") == 3);
}