/*
 * Made by Tobias Brasch, s113618@student.dtu.dk
 * Used to create JSON strings for easier management of the
 * data that should be sent to the server.
 */

//Variables use in this file
String JSON = "{}";

/*
 * Reset the JSON variable
 */
void resetJSON(){
  JSON = "{}";
}

/*
 * Sets the JSON string, should not be used, might be 
 * removed.
 */
void setJSON(String object){
  JSON = object;
}

/*
 * Gets the JSON and adds the unit uuid based on thee bool
 * given to the method.
 * 
 * returns the JSON.
 */
String getJSON(bool withId){
  if(withId){
    addStringVariable("unit_uuid", UUID);
  }
  return JSON;
}

/*
 * Adds a string variable to the JSON string.
 */
void addStringVariable(String name, String value){
  int l = JSON.length();
  if(l == 2){
    JSON = "{\"" + name + "\": \"" + value + "\"}";
  }
  else if(l > 2){
    JSON.remove(l-1);
    JSON = JSON + ", \"" + name + "\": \"" + value + "\"}";
  }
}

/*
 * Adds int, float, bool or json variable to the JSON string.
 */
void addOtherVariable(String name, String value){
  int l = JSON.length();
  if(l == 2){
    JSON = "{\"" + name + "\": " + value + "}";
  }
  else if(l > 2){
    JSON.remove(l-1);
    JSON = JSON + ", \"" + name + "\": " + (String)value + "}";
  }
}


