
#include "SI114X.h"

SI114X SI1145 = SI114X();

bool sunlightError = false;

bool isSunlightError(){
  return sunlightError;
}

String getTableSunlight(){
  return "sunlight";
}

void setupSunlight() {
  int i = 0;
  while (!SI1145.Begin() && i != 10) {
    i++;
    delay(1000);
  }
}

String sunlightReading() {
  resetJSON();

  sunlightError = false;
  
  addOtherVariable("visible",(String)SI1145.ReadVisible());
  addOtherVariable("ir",(String)SI1145.ReadIR());
  //the real UV value must be div 100 from the reg value , datasheet for more information.
  addOtherVariable("uv", (String)((float)SI1145.ReadUV()/100));

  if(SI1145.ReadVisible() == 0 && SI1145.ReadIR() == 0 && SI1145.ReadUV() == 0){
    sunlightError = true;
  }
  
  return getJSON(true);
}


