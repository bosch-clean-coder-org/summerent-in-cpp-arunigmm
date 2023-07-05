#include "typewise-alert.h"
#include <stdio.h>

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) 
{
  if(temperatureInC < 0) {
    return TOO_LOW;
  }
  if(temperatureInC > coolingType) {
    return TOO_HIGH;
  }
  return NORMAL;
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
  BreachType breachType = classifyTemperatureBreach( batteryChar.coolingType, temperatureInC);
  switch(alertTarget) 
  {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) 
{
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) 
{
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
