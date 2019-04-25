#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <TimedAction.h>
#include "WiFiEsp.h"

SoftwareSerial mySerial(3,2);
Adafruit_GPS GPS(&mySerial);
// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(6, 7); // RX, TX
#endif

/************************** Wifi *********************/
char ssid[] = "OnePlus 6";
char pass[] = "neilsphone";  
int status = WL_IDLE_STATUS;     // the Wifi radio's status

//char server[] = "192.168.43.213";
char server[] = "arduino.cc";
unsigned long lastConnectionTime = 0;         // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10000L; // delay between updates, in milliseconds


WiFiEspClient client; // Initialize the client object

/*****************************************************/

#define GPSECHO  false

//For GPS interupt
boolean usingInterrupt = false;
void useInterrupt(boolean);
//For GPS 
void GPSLocation();
// for impacts
void impacts();
int scale = 200; // 200 (±200g) for ADXL377


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  // For the parsing code to work nicely, have time to sort thru the data and print it out.
  useInterrupt(true);
  delay(1000);

  /**************/
  Serial1.begin(9600);                  // initialize serial for ESP module
  WiFi.init(&Serial1);                  // initialize ESP module
  while ( status != WL_CONNECTED) {     // attempt to connect to WiFi network
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);    // Connect to WPA/WPA2 network
  }
  Serial.println("You're connected to the network");
  printWifiStatus();
  
}

//A timed action to interupt after 1 second and print GPSLocation()
TimedAction GPSThread = TimedAction(1000,GPSLocation); 
//A timed action to interupt after 10 seconds and sends data to pi
TimedAction WiFiThread = TimedAction(10000,httpRequest); 

uint32_t timer = millis();

void loop(){
  
//  while (client.available()) {
//    char c = client.read();
//    Serial.write(c);
//  }
  WiFiThread.check();
  GPSThread.check();
  impacts();
  
}

void httpRequest()
{
  Serial.println();
    
  // close any connection before send a new request
  // this will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection
  if (client.connect(server, 80)) {
    Serial.println("Connecting...");
    
    // send the HTTP PUT request
     client.println("POST /data HTTP/1.1");
  client.println("Host: 192.168.43.213:8000");
  client.println("Cache-Control: no-cache");
  client.println("Content-Type: application/x-www-form-urlencoded");
  client.print("Content-Length:"+content.length());
  

    // note the time that the connection was made
    lastConnectionTime = millis();
  }
  else {
    // if you couldn't make a connection
    Serial.println("Connection failed");
  }
}


void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
