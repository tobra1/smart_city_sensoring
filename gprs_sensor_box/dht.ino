// Made by Jacob Mortensen, s112906@student.dtu.dk and Tobias Brasch, s113618@student.dtu.dk
// Based on testing sketch for various DHT humidity/temperature sensors
// by ladyada, public domain

#include <HDC1000.h>

HDC1000 dht;

bool dhtERROR = false;

bool isDhtERROR(){
  return dhtERROR;
}

void setupDHT(){
  dht.begin();
}

String getTableDHT(){
  return "temp_hum";
}

String getDHT(){
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    resetJSON();

    float h = dht.getHumi();
    float t = dht.getTemp();

    // check if returns are valid, if they are NaN (not a number) then something went wrong!
    if (isnan(t) || isnan(h)) 
    {
        dhtERROR = true;
    }

    dhtERROR = false;

    addOtherVariable("temp", (String)t);
    addStringVariable("temp_unit", "C");
    addOtherVariable("hum", (String)h);
    addStringVariable("hum_unit", "%");
    return getJSON(true);
}
