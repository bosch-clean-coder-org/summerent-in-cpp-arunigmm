#include "typewise-alert.h"
#include <map>
#include <stdio.h>

typedef std::pair<int,int> BoundValues;

std::map<CoolingType, BoundValues> CoolingBoundValue = 
{ 
{std::make_pair( PASSIVE_COOLING, std::make_pair(0,35))},
{std::make_pair( HI_ACTIVE_COOLING, std::make_pair(0,45))},
{std::make_pair( MED_ACTIVE_COOLING, std::make_pair(0,40))}
};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) 
  {
  BoundValues temp = CoolingBoundValue[coolingType];
  return inferBreach(temperatureInC, temp.first, temp.second);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  switch(breachType) {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
      break;
    case NORMAL:
      break;
  }
}
