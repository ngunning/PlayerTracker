/******************************************************************************
ADXL377_example.ino
Simple example for using the ADXL377 accelerometer breakout.
Jordan McConnell @ SparkFun Electronics
3 July 2014
https://github.com/sparkfun/ADXL377_Breakout
This example collects raw accelerometer data from the ADXL377 sensor using
analog reads and then converts it into common units (g's) and prints the
result to the Serial Monitor.
Developed/Tested with:
Arduino Uno
Arduino IDE 1.0.5
This code is beerware.
Distributed as-is; no warranty is given. 
******************************************************************************/

// Make sure these two variables are correct for your setup
int scale = 200; // 3 (±3g) for ADXL337, 200 (±200g) for ADXL377
int Xref = 334;
int Yref = 334;
int Zref = 334;
boolean micro_is_5V = true; // Set to true if using a 5V microcontroller such as the Arduino Uno, false if using a 3.3V microcontroller, this affects the interpretation of the sensor data

void setup()
{
  // Initialize serial communication at 115200 baud
  Serial.begin(115200);
}

// Read, scale, and print accelerometer data
void loop()
{
  // Get raw accelerometer data for each axis
  int rawX = analogRead(A0);
  int rawY = analogRead(A1);
  int rawZ = analogRead(A2);
  
  
  // Scale accelerometer ADC readings into common units
  // Scale map depends on if using a 5V or 3.3V microcontroller
  float scaledX, scaledY, scaledZ; // Scaled values for each axis
  scaledX = (((rawX - Xref)*3.223)/6.5);
  scaledY = (((rawY - Yref)*3.223)/6.5);
  scaledZ = (((rawZ - Zref)*3.223)/6.5);

  if(scaledX >= 7 || scaledY >= 7 || scaledZ >= 7){
    Serial.print("X: "); Serial.print(scaledX); Serial.println(" g");
    Serial.print("Y: "); Serial.print(scaledY); Serial.println(" g");
    Serial.print("Z: "); Serial.print(scaledZ); Serial.println(" g");
  }
  else{}
 
  
 /* // Print out raw X,Y,Z accelerometer readings
  Serial.print("X: "); Serial.println(rawX);
  Serial.print("Y: "); Serial.println(rawY);
  Serial.print("Z: "); Serial.println(rawZ);
  //Serial.println();

  // Print out scaled X,Y,Z accelerometer readings
  Serial.print("X: "); Serial.print(scaledX); Serial.println(" g");
  Serial.print("Y: "); Serial.print(scaledY); Serial.println(" g");
  Serial.print("Z: "); Serial.print(scaledZ); Serial.println(" g");
  */
  delay(10); // Minimum delay of 2 milliseconds between sensor reads (500 Hz)
}

// Same functionality as Arduino's standard map function, except using floats
float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
