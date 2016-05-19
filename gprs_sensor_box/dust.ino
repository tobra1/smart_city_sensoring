
int pin = 8;

unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 30000;//sampe 30s ;
unsigned long lowpulseoccupancy = 0;

bool dustERROR = false;

void setupDust(){
  pinMode(pin,INPUT);
}


String getTableDust(){
  return "dust";
}

bool isDustError(){
  return dustERROR;
}

String dustReading(){
  starttime = millis();
  lowpulseoccupancy = 0;

  dustERROR = false;
  
  while ((millis()-starttime) < sampletime_ms) {
    duration = pulseIn(pin, LOW);
    lowpulseoccupancy = lowpulseoccupancy + duration;
  }

  float ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
  float concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve

  if(concentration == 0.62)
  {
    dustERROR = true;
  }
  else {
    addStringVariable(getTableDust(),getTableDust());
    addOtherVariable(getTableDust()+"lowpulseoccupancy", (String)lowpulseoccupancy);
    addOtherVariable(getTableDust()+"ratio", (String)ratio);
    addOtherVariable(getTableDust()+"concentration", (String)concentration);
    //addStringVariable("concentration_unit", "pcs/0.01cf");
  }

  return getJSON(false);
}


