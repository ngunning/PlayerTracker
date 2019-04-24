#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <TimedAction.h>

#include "WiFiEsp.h"

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(6, 7); // RX, TX
#endif

char ssid[] = "OnePlus 6";
char pass[] = "neilsphone";  
//char ssid[] = "HUAWEI-B525-51CC";
//char pass[] = "Connacht1";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status
char server[] = "192.168.43.213";
unsigned long lastConnectionTime = 0;         // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 500L; // delay between updates, in milliseconds( 500 milliseconds)
// Initialize the Ethernet client object
WiFiEspClient client;

SoftwareSerial mySerial(3,2); //GPS serial pins
Adafruit_GPS GPS(&mySerial);

#define GPSECHO  false

//For wifi
void printWifiStatus();
void httpRequest();
//For GPS interupt
boolean usingInterrupt = false;
void useInterrupt(boolean);
//For GPS 
void GPSLocation();
// for impacts
float magnitude = 0; //get magnitude of the 3 axis for total g force impact.
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


  Serial1.begin(9600);    // initialize serial for ESP module
  // initialize ESP module
  WiFi.init(&Serial1);
  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }
  Serial.println("You're connected to the network");
  printWifiStatus();
}

//A timed action to interupt after 1 second and print GPSLocation()
TimedAction GPSThread = TimedAction(1000,GPSLocation); 

uint32_t timer = millis();

void loop(){
  impacts();
  // if there's incoming data from the net connection send it out the serial port
  // this is for debugging purposes only
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }
  // if 500 milliseconds have passed since your last connection,
  // then connect again and send data
  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest();
  }
  //GPSThread.check();
  
  
}
