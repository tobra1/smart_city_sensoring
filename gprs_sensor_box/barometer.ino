#include "Barometer.h"
#include <Wire.h>

Barometer myBarometer;

bool barometerERROR = false;

void setupBarometer(){
  myBarometer.init();
}

String getTableBarometer(){
  return "barometer";
}

bool isBarometerError(){
  return barometerERROR;
}

String barometerReading(){
  resetJSON();
  float temperature = myBarometer.bmp085GetTemperature(myBarometer.bmp085ReadUT());
  float pressure = myBarometer.bmp085GetPressure(myBarometer.bmp085ReadUP());
  float atm = pressure / 101325;

  barometerERROR = false;
  if(temperature == 0 && pressure == 236)
    barometerERROR = false;
  
  addOtherVariable("temp", String(temperature,2));
  addStringVariable("temp_unit", "C");
  addOtherVariable("pressure", String(pressure,0));
  addStringVariable("pressure_unit", "Pa");
  addOtherVariable("atm", String(atm,4));

  return getJSON(true);
}

