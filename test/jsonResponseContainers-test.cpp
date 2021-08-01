#include "catch.hpp"
#include "../utils/jsonResponseContainers.h"

TEST_CASE("Testing SituationUpdateContainer") {
    SituationUpdateContainer test(true, "test\ntest", 1, 2);
    REQUIRE(test.JSONserializer() == "{\n   \"isStarted\": true,\n   \"currTurn\": \"1\",\n   \"winner\": \"2\",\n   \"boardSituation\": \"test\ntest\"\n}");
    
    SituationUpdateContainer test2;
    test2.JSONparser(test.JSONserializer());
    REQUIRE(test2.JSONserializer() == "{\n   \"isStarted\": true,\n   \"currTurn\": \"1\",\n   \"winner\": \"2\",\n   \"boardSituation\": \"test\ntest\"\n}");

    test.JSONparser("{\n   \"isStarted\": false,\n   \"currTurn\": \"2\",\n   \"winner\": \"4\",\n   \"boardSituation\": \"testtest\"\n}");
    REQUIRE(test.isStarted == false);
    REQUIRE(test.currTurn == 2);
    REQUIRE(test.boardSituation == "testtest");
    REQUIRE(test.winner == 4);
}

TEST_CASE("Testing RegisterContainer") {
    RegisterContainer test(false, 9);
    REQUIRE(test.JSONserializer() == "{\n   \"inAction\": false,\n   \"id\": \"9\"\n}");
    
    RegisterContainer test2;
    test2.JSONparser(test.JSONserializer());
    REQUIRE(test2.JSONserializer() == "{\n   \"inAction\": false,\n   \"id\": \"9\"\n}");

    test2.JSONparser("{\n   \"inAction\": true,\n   \"id\": \"7\"\n}");
    REQUIRE(test2.id == 7);
    REQUIRE(test2.inAction == true);
}

TEST_CASE("Testing MakeMoveContainer") {
    MakeMoveContainer test(false);
    REQUIRE(test.JSONserializer() == "{\n   \"isDone\": false\n}");

    MakeMoveContainer test2;
    test2.JSONparser(test.JSONserializer());
    REQUIRE(test2.JSONserializer() == "{\n   \"isDone\": false\n}");

    test2.JSONparser("{\n   \"isDone\": true\n}");
    REQUIRE(test2.isDone == true);
}