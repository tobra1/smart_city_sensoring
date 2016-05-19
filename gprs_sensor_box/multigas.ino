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
  
  float nh3,co,no2,c3h8,c4h10,ch4,h2,c2h5oh;
  String GasStr;
  
  GasStr = "nh3";
  nh3 = mutichannelGasSensor.measure_NH3();
  addOtherVariable(getTableMultigas()+GasStr, (String)nh3);
  
  GasStr = "co";
  co = mutichannelGasSensor.measure_CO();
  addOtherVariable(getTableMultigas()+GasStr, (String)co);
  
  GasStr = "no2";
  no2 = mutichannelGasSensor.measure_NO2();
  addOtherVariable(getTableMultigas()+GasStr, (String)no2);
  
  GasStr = "c3h8";
  c3h8 = mutichannelGasSensor.measure_C3H8();
  addOtherVariable(getTableMultigas()+GasStr, (String)c3h8);
  
  GasStr = "c4h10";
  c4h10 = mutichannelGasSensor.measure_C4H10();
  addOtherVariable(getTableMultigas()+GasStr, (String)c4h10);
  
  GasStr = "ch4";
  ch4 = mutichannelGasSensor.measure_CH4();
  addOtherVariable(getTableMultigas()+GasStr, (String)ch4);
  
  GasStr = "h2";
  h2 = mutichannelGasSensor.measure_H2();
  addOtherVariable(getTableMultigas()+GasStr, (String)h2);
  
  GasStr = "c2h5oh";
  c2h5oh = mutichannelGasSensor.measure_C2H5OH();
  addOtherVariable(getTableMultigas()+GasStr, (String)c2h5oh);
      
  if(nh3 <=0 && co <=0 && no2 <=0 && c3h8 <=0 && c4h10 <=0 && ch4 <=0 && h2 <=0 && c2h5oh <=0 ){
    multigasERROR = true;
  }
  else{
    multigasERROR = false;
    addStringVariable(getTableMultigas(),getTableMultigas());
  }
  errorCount = 0;
  return getJSON(false);
}

