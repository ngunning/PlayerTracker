/************* WiFi ******************/

void httpRequest()
{
  Serial.println();
    
  // close any connection before send a new request
  // this will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection
  if (client.connect(server, 8000)) {
    Serial.println("Connecting...");
    
  // Make the HTTP request
  String content = "location=" + String(GPS.latitudeDegrees) +" "+ String(GPS.longitudeDegrees) + "&impacts="+ String(magnitude);
  client.println("POST /data HTTP/1.1");
  client.println("Host: 192.168.43.213:8000");
  client.println("Cache-Control: no-cache");
  client.println("Content-Type: application/x-www-form-urlencoded");
  client.print("Content-Length:"+content.length());
  //client.println(content.length());
  client.println();
  client.println(content);

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
