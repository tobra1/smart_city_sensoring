#define SOUND_SENSOR A0
unsigned long sound_sampletime_ms = 10000;//sampe 1s ;

bool soundError = false;

bool isSoundError(){
  return soundError;
}

String getTableSound(){
  return "sound";
}

String soundReading()
{ 
  soundError = false;
  
  long sound_starttime = millis();
  int sensorValue = analogRead(SOUND_SENSOR);//use A0 to read the electrical signal
  int high = sensorValue, low = sensorValue, sum = sensorValue, count = 1;
  
  while ((millis()-sound_starttime) < sound_sampletime_ms) {
    sensorValue = analogRead(SOUND_SENSOR);//use A0 to read the electrical signal
    if(sensorValue != 0){
      if(high < sensorValue)
        high = sensorValue;
      else if(low > sensorValue)
        low = sensorValue;
      sum = sum + sensorValue;
      count++;
    }
  }
  
  if(sum/count == 0){
    soundError = true;
  }
  else {
    addStringVariable(getTableSound(),getTableSound());
    addOtherVariable(getTableSound()+"low", (String)low);
    addOtherVariable(getTableSound()+"high", (String)high);
    addOtherVariable(getTableSound()+"avg", (String)(sum/count));
    addOtherVariable(getTableSound()+"meassurements", (String)count);
  }

  return getJSON(false);
}
 
void setupSound()
{
    pinMode(SOUND_SENSOR, INPUT);
}



