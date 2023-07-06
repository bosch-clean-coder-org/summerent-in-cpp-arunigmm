#include "typewise-alert.h"
#include <string>
#include <map>
#include <stdio.h>

typedef std::pair<int,int> BoundValues;

std::map<CoolingType, BoundValues> coolingBoundValue = 
{ 
   { std::make_pair(PASSIVE_COOLING,    std::make_pair(0,35))},
   { std::make_pair(HI_ACTIVE_COOLING,  std::make_pair(0,45))},
   { std::make_pair(MED_ACTIVE_COOLING, std::make_pair(0,40))}
};

std::map<BreachType, std::string> breachMessage =
{
   { std::make_pair(NORMAL,    "Hi, the temperature is Normal")},
   { std::make_pair(TOO_LOW,   "Hi, the temperature is Too Low")},
   { std::make_pair(TOO_HIGH,  "Hi, the temperature is Too High")}
};

typedef void (*AlertFunction)(BreachType);

std::map<AlertTarget, AlertFunction> alertFunctionPtr =
{
   { std::make_pair(TO_CONTROLLER,   sendToController)},
   { std::make_pair(TO_EMAIL,   sendToController)}
};

BreachType inferTemperatureBreach(CoolingType coolingType, double temperatureInC) 
{
   BoundValues temperatureRange = coolingBoundValue[coolingType];
   if(temperatureInC < temperatureRange.first) 
   {
      return TOO_LOW;
   }
   if(temperatureInC > temperatureRange.second) 
   {
      return TOO_HIGH;
   }
   return NORMAL;
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
   BreachType breachType = inferTemperatureBreach(batteryChar.coolingType, temperatureInC);
   alertFunctionPtr[alertTarget](breachType);
}

void sendToController(BreachType breachType)
{
   const unsigned short header = 0xfeed;
   printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType)
{
   const char* recepient = "a.b@c.com";
   printf("To: %s\n", recepient);
   printf("Message: %s\n", breachMessage[breachType]);
}
