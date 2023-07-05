#pragma once

typedef enum 
{
  PASSIVE_COOLING = 35,
  MED_ACTIVE_COOLING = 40,
  HI_ACTIVE_COOLING = 45
} CoolingType;

typedef enum 
{
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

BreachType inferBreach(double& value, double& lowerLimit, double& upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum 
{
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct 
{
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

void checkAndAlert( AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
