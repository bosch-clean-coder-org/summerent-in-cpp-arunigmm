#pragma once

#include <map>
#include <utility>

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;


typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

pair<int,int> BoundValues;
map<CoolingType, BoundValues> CoolingBoundValue {{PASSIVE_COOLING,BoundValues(0,35)}};

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);


void checkAndAlert( AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
