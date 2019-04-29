#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <TimedAction.h>
#include "WiFiEsp.h"
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

//wifi
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(6, 7); // RX, TX
#endif

byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char ssid[] = "OnePlus 6";        // your network SSID (name)
char pass[] = "neilsphone";       // your network password
//char ssid[] = "HUAWEI-B525-51CC";        // your network SSID (name)
//char pass[] = "Connacht1";
int status = WL_IDLE_STATUS;     // the Wifi radio's status

//mySQL
IPAddress server_addr(192,168,43,211);  // IP of the MySQL *server* here
char user[] = "player";              // MySQL user login username
char password[] = "magic";        // MySQL user login password

//GPS
SoftwareSerial mySerial(3,2);
Adafruit_GPS GPS(&mySerial);

#define GPSECHO  false

//For GPS interupt
boolean usingInterrupt = false;
void useInterrupt(boolean);
//For GPS 
//void GPSLocation();
// for impacts
void impacts();
int magnitude = 0; //get magnitude of the 3 axis for total g force impact.
void printWifiStatus();

char INSERT_SQL[] = "INSERT INTO playerinfo.impacts (impacts) VALUES (%d)";
char query[128];

WiFiEspClient client;
MySQL_Connection conn((Client *)&client);

void setup() {
  Serial.begin(115200); 
////   9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
//  GPS.begin(9600);
// //  Set the update rate
//  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
//  // For the parsing code to work nicely, have time to sort thru the data and print it out.
//  useInterrupt(true);
//  delay(1000);

   // initialize serial for ESP module
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);
  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
  }
  Serial.println("You're connected to the network");
  //printWifiStatus();
  delay(5000);

  Serial.println("Connecting to database...");
  if (conn.connect(server_addr, 3306, user, password)) {
    delay(1000);
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    sprintf(query, INSERT_SQL, magnitude);
    cur_mem->execute(query);
    delete cur_mem;
    Serial.println("Data recorded.");
  }
  else
    Serial.println("Connection failed.");
  conn.close();
}

//A timed action to interupt after 1 second and print GPSLocation()
//TimedAction GPSThread = TimedAction(5000,GPSLocation); 

uint32_t timer = millis();

void loop(){

  //GPSThread.check();
  //impacts();
  
  
  
}
