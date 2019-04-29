/****** Impacts Code ********/

void impacts() {
  int scale = 200; // 200 (±200g) for ADXL377
  // Get raw accelerometer data for each axis
  int rawX = analogRead(A0);
  int rawY = analogRead(A1);
  int rawZ = analogRead(A2);
  
  // Scale accelerometer ADC readings into common units
  // Scale map on 3.3V microcontroller
  float scaledX, scaledY, scaledZ; // Scaled values for each axis
  

 /*
  * voltage ca..:  0V...............1.65...............3.3    
  * analog  ca     0                512                1023
  */
  // mapf(value,minumum in,maximum out,the scale <-200g to +200g>)
  scaledX = mapf(rawX, 0, 1023, -scale, scale);
  scaledY = mapf(rawY, 0, 1023, -scale, scale);
  scaledZ = mapf(rawZ, 0, 1023, -scale, scale);

  //calculating the total G force of the impact
  magnitude = sqrt((scaledX*scaledX)+(scaledY*scaledY)+(scaledZ*scaledZ));

  // between 10g and 20g there is a high number of reading which are irrelevant as they are low impacts
  // being recieved over short periods in a large area. 
//  if(magnitude > 10 && magnitude < 20){
//    Serial.println("&&&&&&&&&&&&&&&&&&&&&&&");
//    Serial.println("Player 1:");
//    Serial.print(magnitude); Serial.println("g");
//    Serial.println("Low impact under 20g");
//    Serial.println("&&&&&&&&&&&&&&&&&&&&&&&");
//  }
//  if(magnitude >= 20 && magnitude < 30){
//    Serial.println("&&&&&&&&&&&&&&&&&&&&&&&");
//    Serial.println("Player 1:");
//    Serial.print(magnitude); Serial.println("g");
//    Serial.println("Low impact between 20g and 30g");
//    Serial.println("&&&&&&&&&&&&&&&&&&&&&&&");
//  }
//  if(magnitude >= 30 && magnitude < 40){
//    Serial.println("&&&&&&&&&&&&&&&&&&&&&&&");
//    Serial.println("Player 1:");
//    Serial.print(magnitude); Serial.println("g");
//    Serial.println("Medium impact between 30g and 40g");
//    Serial.println("&&&&&&&&&&&&&&&&&&&&&&&");
//  }
//  if(magnitude >= 40 && magnitude < 50){
//    Serial.println("&&&&&&&&&&&&&&&&&&&&&&&");
//    Serial.println("Player 1:");
//    Serial.print(magnitude); Serial.println("g");
//    Serial.println("Medium impact between 40g and 50g");
//    Serial.println("Monitor players behavour");
//    Serial.println("&&&&&&&&&&&&&&&&&&&&&&&");
//  }
//  if(magnitude >= 50 && magnitude < 60){
//    Serial.println("&&&&&&&&&&&&&&&&&&&&&&&");
//    Serial.println("Player 1:");
//    Serial.print(magnitude); Serial.println("g");
//    Serial.println("High impact between 50g and 60g");
//    Serial.println("Monitor players behavour");
//    Serial.println("&&&&&&&&&&&&&&&&&&&&&&&");
//  }
//  if(magnitude >= 60 && magnitude < 70){
//    Serial.println("&&&&&&&&&&&&&&&&&&&&&&&");
//    Serial.println("Player 1:");
//    Serial.print(magnitude); Serial.println("g");
//    Serial.println("High impact between 60g and 70g");
//    Serial.println("Monitor players behavour, has recieved a high impact");
//    Serial.println("&&&&&&&&&&&&&&&&&&&&&&&");
//  }
//  if(magnitude >= 70 && magnitude < 80){
//    Serial.println("&&&&&&&&&&&&&&&&&&&&&&&");
//    Serial.println("Player 1:");
//    Serial.print(magnitude); Serial.println("g");
//    Serial.println("High impact between 70g and 80g");
//    Serial.println("Monitor players behavour, has recieved a high impact. Please check players health");
//    Serial.println("&&&&&&&&&&&&&&&&&&&&&&&");
//  }
//  if(magnitude >= 80 && magnitude < 90){
//    Serial.println("&&&&&&&&&&&&&&&&&&&&&&&");
//    Serial.println("Player 1:");
//    Serial.print(magnitude); Serial.println("g");
//    Serial.println("High impact between 80g and 90g");
//    Serial.println("Monitor players behavour, has recieved a high impact. Please check players health");
//    Serial.println("&&&&&&&&&&&&&&&&&&&&&&&");
//  }
//  if(magnitude >= 90 && magnitude < 100){
//    Serial.println("&&&&&&&&&&&&&&&&&&&&&&&");
//    Serial.println("Player 1:");
//    Serial.print(magnitude); Serial.println("g");
//    Serial.println("Extreame impact between 90g and 100g");
//    Serial.println("Monitor players behavour, has recieved an Extreame impact. This player may have a concussion");
//    Serial.println("&&&&&&&&&&&&&&&&&&&&&&&");
//  }
//  if(magnitude >= 100){
//    Serial.println("&&&&&&&&&&&&&&&&&&&&&&&");
//    Serial.println("Player 1:");
//    Serial.print(magnitude); Serial.println("g");
//    Serial.println("Extreame impact over 100g");
//    Serial.println("Player has recieved an Extreame impact. This player may have a concussion");
//    Serial.println("&&&&&&&&&&&&&&&&&&&&&&&");
//  }
  delay(1);
}

// Same functionality as Arduino's standard map function, except using floats
float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
