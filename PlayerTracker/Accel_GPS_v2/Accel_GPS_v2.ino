#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <TimedAction.h>

SoftwareSerial mySerial(3,2);
Adafruit_GPS GPS(&mySerial);

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
  
}

//A timed action to interupt after 1 second and print GPSLocation()
TimedAction GPSThread = TimedAction(1000,GPSLocation); 

uint32_t timer = millis();

void loop(){
  if(GPS.fix = 0) {
    Serial.println("waiting for fix");
    }
  GPSThread.check();
  impacts();
  
}
