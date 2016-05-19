#include <LBattery.h>



String getTableBattery(){
  return "battery";
}


String getBattery() {
  addStringVariable(getTableBattery(),getTableBattery());
  addOtherVariable(getTableBattery()+"level", (String)LBattery.level());
  addOtherVariable(getTableBattery()+"is_charging", (String)LBattery.isCharging());
  
  return getJSON(false);
}

