/*
 * Made by Tobias Brasch, s113618@student.dtu.dk
 * Communication file, uses the gsm part and a the sim card 
 * to connect to the internet and post data to server that
 * is specified in the SITE_URL parameter.
 */

//Libraries
#include <LGPRS.h>
#include <LGPRSClient.h>

//Variable used in this file
#define SITE_URL "dtu-smartcity.freundtaagaard.com"
#define PORT 3000
#define ACTION "POST"


LGPRSClient client;


/*
 * Establishes a connection to the server.
 * 
 * returns a bool.
 */
bool connectToServer() {
  while (!LGPRS.attachGPRS("internet", NULL, NULL))
  {
    Serial.println("Waiting for SIM card!");
    delay(1000);
  }
  if (!client.connect(SITE_URL, PORT))
  {
    Serial.println("Couldn't connect to server!");
    return false;
  }
  return true;
}

/*
 * Sending a request to the server.
 * 
 * data, the json containing data to be posted to server.
 * table, the table the data should be posted to.
 */
void post(String data, String table) {
  Serial.print("Sending " ACTION " request to " + table + ": ");
  client.println("" ACTION " /" + table + " HTTP/1.1");
  client.println("Host: " SITE_URL ":" + (String)PORT + "");
  client.println("Content-Type: application/json");
  client.println("Content-Length: " + String(data.length()));
  client.println();
  client.println(data);
  client.println();
  client.println((char)26);
  Serial.println("Done!");
  Serial.println();
}

/*
 * 
 * returns the response from the server.
 */
String response() {
  int v;
  bool a = false;
  String response = "";
  while (true) {
    while (client.available())
    {
      a = true;
      v = client.read();
      if (v < 0)
        break;
      response += (char)v;
    }
    if (v < 0 || !client.available() && a)
      break;
  }
  return response;
}

/*
 * Disconnects from the server.
 */
void disconnectServer() {
  client.stop();
}

/*
 * Posts the id to the server, consider using post method
 * instead or giving it a better name.
 * 
 * returns the new unit uuid.
 */
String idGenerator(){
  String data = getJSON(false);
  Serial.print("Sending " ACTION " request to units: ");
  client.println("" ACTION " /units HTTP/1.1");
  client.println("Host: " SITE_URL ":" + (String)PORT + "");
  client.println("Content-Type: application/json");
  client.println("Content-Length: " + String(data.length()));
  client.println("Prefer: return=representation");
  client.println();
  client.println(data);
  client.println();
  client.println((char)26);
  Serial.println("Done!");
  Serial.println();

  String r = response();
  return r.substring(r.indexOf("uuid", 0)+8,r.indexOf("uuid", 0)+8+36);
}

