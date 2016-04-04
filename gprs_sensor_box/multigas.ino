// Multichannel gas sensor by Jacob Mortensen
// Based on example by Jacky Zhang

#include <Wire.h>
#include "MutichannelGasSensor.h"

bool multigasERROR = false;
int errorCount = 0;

/*
 * Things for the setup

    Serial.begin(9600);  // start serial for output

    mutichannelGasSensor.begin(0x04);//the default I2C address of the slave is 0x04
    //mutichannelGasSensor.changeI2cAddr(0x10);
    //mutichannelGasSensor.doCalibrate();

    mutichannelGasSensor.powerOn();
 */


void setupMultigas(){
  mutichannelGasSensor.begin(0x04);//the default I2C address of the slave is 0x04
  mutichannelGasSensor.doCalibrate();
  mutichannelGasSensor.powerOn();
}

bool isMultigasError(){
  return multigasERROR;
}

String getTableMultigas(){
  return "multigas";
}

String multigasReading(){
  // Temp value to hold reading
  resetJSON();
  
  float c;
  String GasStr;
  
  for(int i = 1; i < 9; i++){
    switch (i) {
      case 1:
      GasStr = "nh3";
      c = mutichannelGasSensor.measure_NH3();
      break;

      case 2:
      GasStr = "co";
      c = mutichannelGasSensor.measure_CO();
      break;

      case 3:
      GasStr = "no2";
      c = mutichannelGasSensor.measure_NO2();
      break;

      case 4:
      GasStr = "c3h8";
      c = mutichannelGasSensor.measure_C3H8();
      break;

      case 5:
      GasStr = "c4h10";
      c = mutichannelGasSensor.measure_C4H10();
      break;

      case 6:
      GasStr = "ch4";
      c = mutichannelGasSensor.measure_CH4();
      break;

      case 7:
      GasStr = "h2";
      c = mutichannelGasSensor.measure_H2();
      break;

      case 8:
      GasStr = "c2h5oh";
      c = mutichannelGasSensor.measure_C2H5OH();
      break;

      default: 
      Serial.println("ERROR! Multigas - This state should never be reached!");
      GasStr = "ERROR";
      c = -255;
      break;
    } 
    if (c <=0) { //If it's lower there's an error
      errorCount++;
      addOtherVariable(GasStr, (String)c);
    }
    else{
      addOtherVariable(GasStr, (String)c);
    }
  }

  if(errorCount == 8)
    multigasERROR = true;
  else
    multigasERROR = false;

  errorCount = 0;
  return getJSON(true);
}
