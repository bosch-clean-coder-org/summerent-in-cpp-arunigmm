#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

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
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 40) == NORMAL);
}

TEST_CASE("classifyTemperatureBreach for High active cooling config_High") 
{
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50) == TOO_HIGH);
}


TEST_CASE("classifyTemperatureBreach for Mid active cooling config_Normal") 
{
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 40) == NORMAL);
}

TEST_CASE("classifyTemperatureBreach for Mid active cooling config_High") 
{
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 41) == TOO_HIGH);
}
