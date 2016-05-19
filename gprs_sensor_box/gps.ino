/*
 * Made by Tobias Brasch, s113618@student.dtu.dk
 * Finds the current location using the gps part, that came
 * with the device.
 */

//Libraries
#include <LGPS.h>            // LinkIt GPS Library
#include <LDateTime.h>

//Variables used in this file
String Location = "";

gpsSentenceInfoStruct info;

/*
 * returns the name of the table used for stoing gps info.
 */
String getTableGPS(){
  return "gps";
}

/*
 * Finds the current position, this method might take time
 * since it has to get a GPS fix first. Should only be run
 * a few times a day.
 * 
 * returns JSON string containing position information.
 */
String getCurrentPosition()
{
  //Serial.println("Starting GPS");
  startGPS();
  //Serial.println("Waiting for satellites");
  waitForSatellite();
  //Serial.println("Finding position");
  Location = getLocation();
  //Serial.println("Stopping location");
  stopGPS();
  return Location;
}

/*
 * return Location
 */
String readGPS(){
  return Location;
}

/*
 * Start the GPS part
 */
void startGPS()
{
  LGPS.powerOn();
}

/*
 * Stops the GPS part
 */
void stopGPS()
{
  LGPS.powerOff();
}

/*
 * Waits for a GPS fix
 */
void waitForSatellite()
{
  LGPS.getData(&info);
  char* GPGGAstr = (char*)info.GPGGA;
  int tmp, num = 0, timer = 0;
  
  while(num == 0)
  
  {
    delay(1000);
    
    LGPS.getData(&info);
    GPGGAstr = (char*)info.GPGGA;
    
    if(((String)GPGGAstr).length() > 0 && GPGGAstr[0] == '$')
    {
      tmp = getComma(7, GPGGAstr);
      num = getIntNumber(&GPGGAstr[tmp]);
      if(timer == 50 || num != 0)
        break;
      timer++;
      Serial.println("Waiting for sattelites! " + (String)timer + ". run");
      continue;
    }
  }
}

/*
 * Checks if location can be parsed.
 * 
 * returns JSON string
 */
String getLocation(){
  LGPS.getData(&info);
  LGPS.getData(&info);
  if (!ParseLocation((char*)info.GPGGA)) {  // This is where we break out needed location information
    Serial.println("Couldn't find location!");
  }
  return getJSON(false);
}

/*
 * Parses the GPGGA to a lat and lng JSON file, these are
 * at the moment not accurate enough. The calculation used 
 * should be changed.
 * 
 * returns bool for if a GPS fix were found in the GPGGA.
 */
boolean ParseLocation(char* GPGGAstr)
// Refer to http://www.gpsinformation.org/dale/nmea.htm#GGA
// Sample data: $GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47
{

  //Converting the GPGGA to a string
  String GPSstring = String(GPGGAstr);

  addStringVariable(getTableGPS(),getTableGPS());
  
  addStringVariable(getTableGPS()+"gpgga",GPSstring);

  //Finding the latitude
  String latTmp = GPSstring.substring(getComma(2,GPGGAstr),getComma(3,GPGGAstr)-1);
  char latArray[latTmp.length()];
  latTmp.substring(2,latTmp.length()).toCharArray(latArray,latTmp.length());
  float latValue = ((latTmp.substring(0,2).toInt()*100000)+((atof(latArray)*100000)/60))/100000;
  if(GPSstring.substring(getComma(3,GPGGAstr),getComma(4,GPGGAstr)-1) == "S")
    latValue = latValue*(-1);
  String(latValue,6).toCharArray(latArray,latTmp.length());
  String latitude = String(atof(latArray),6);

  addOtherVariable(getTableGPS()+"lat",(String)latitude);
  
  //Finding the longitude
  String lngTmp = GPSstring.substring(getComma(4,GPGGAstr),getComma(5,GPGGAstr)-1);
  char lngArray[lngTmp.length()];
  lngTmp.substring(3,lngTmp.length()).toCharArray(lngArray,lngTmp.length());
  float lngValue = ((lngTmp.substring(0,3).toInt()*100000)+((atof(lngArray)*100000)/60))/100000;
  if(GPSstring.substring(getComma(5,GPGGAstr),getComma(6,GPGGAstr)-1) == "W")
    lngValue = lngValue*(-1);
  String(lngValue,6).toCharArray(lngArray,lngTmp.length());
  String longitude = String(atof(lngArray),6);
  
  addOtherVariable(getTableGPS()+"lng",(String)longitude);
  
  return 1;
}

/*
 * getComma and getIntNumber is at the moment only used to
 * find how many sattelites were found in the GPGGAstr.
 * 
 * getComma returns the index of number num comma
 * getIntNumber returns the value at the comma.
 * 
 * These are taken from LGPS example provided by the 
 * library
 */
unsigned char getComma(unsigned char num,const char *str){
  unsigned char i,j = 0;
  int len=strlen(str);
  for(i = 0;i < len;i ++)
  {
     if(str[i] == ',')
      j++;
     if(j == num)
      return i + 1; 
  }
  return 0; 
}
double getIntNumber(const char *s){
  char buf[10];
  unsigned char i;
  double rev;
  
  i=getComma(1, s);
  i = i - 1;
  strncpy(buf, s, i);
  buf[i] = 0;
  rev=atoi(buf);
  return rev; 
}


