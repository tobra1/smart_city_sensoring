

// Test sketch for CO2 sensor for LinkitOne

bool co2Error = false;

bool isCO2Error(){
  return co2Error;
}


String getTableCO2(){
  return "co2";
}

const unsigned char cmd_get_sensor[] =
{
    0xff, 0x01, 0x86, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x79
};
unsigned char dataRevice[9];
int CO2temp;
int CO2PPM;
 
bool dataRecieve(void)
{
    byte data[9];
    int i = 0;
 
    //transmit command data
    for(i=0; i<sizeof(cmd_get_sensor); i++)
    {
        Serial1.write(cmd_get_sensor[i]);
    }
    delay(10);
    //begin reveiceing data
    if(Serial1.available())
    {
        while(Serial1.available())
        {
            for(int i=0;i<9; i++)
            {
                data[i] = Serial1.read();
            }
        }
    }
 
#if DEBUG
    for(int j=0; j<9; j++)
    {
        Serial.print(data[j]);
        Serial.print(" ");
    }
    Serial.println("");
#endif
 
    if((i != 9) || (1 + (0xFF ^ (byte)(data[1] + data[2] + data[3]
    + data[4] + data[5] + data[6] + data[7]))) != data[8])
    {
        return false;
    }
    CO2PPM = (int)data[2] * 256 + (int)data[3];
    CO2temp = (int)data[4] - 40;
 
    return true;
}

void setupCO2(){
  Serial1.begin(9600);
}

String co2Reading(){
  co2Error = false;
  int i = 0;

  while ( !dataRecieve() && i != 5 ){ i++; }
  
  if(i == 5)
  {
    co2Error = true;
  }
  else {
    addStringVariable(getTableCO2(),getTableCO2());
    addOtherVariable(getTableCO2()+"temp", (String)CO2temp);
    //addStringVariable("temp_unit", "C");
    addOtherVariable(getTableCO2()+"co2", (String)CO2PPM);
    //addStringVariable("co2_unit", "ppm");
  }
  

  return getJSON(false);
}


