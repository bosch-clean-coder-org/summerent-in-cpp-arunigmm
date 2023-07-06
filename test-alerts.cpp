#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("Infers the breach according to limits_Low") 
{
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
}

TEST_CASE("Infers the breach according to limits_Normal") 
{
  REQUIRE(inferBreach(12, 10, 30) == NORMAL);
}

TEST_CASE("Infers the breach according to limits_High") 
{
  REQUIRE(inferBreach(33, 10, 30) == TOO_HIGH);
}

TEST_CASE("classifyTemperatureBreach for Passive cooling config_Normal") 
{
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 10) == NORMAL);
}

TEST_CASE("classifyTemperatureBreach for Passive cooling config_High") 
{
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 40) == TOO_HIGH);
}

TEST_CASE("classifyTemperatureBreach for High active cooling config_Normal") 
{
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 40) == NORMAL);
}

TEST_CASE("classifyTemperatureBreach for High active cooling config_High") 
{
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 50) == TOO_HIGH);
}


TEST_CASE("classifyTemperatureBreach for Mid active cooling config_Normal") 
{
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 40) == NORMAL);
}

TEST_CASE("classifyTemperatureBreach for Mid active cooling config_High") 
{
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 41) == TOO_HIGH);
}
