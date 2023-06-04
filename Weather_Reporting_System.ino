#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

//BMP280 Sensor Setup

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11 
#define BMP_CS 10

Adafruit_BMP280 bmp;

WiFiClient client;

//HTML webpage in form of h file
#include "index.h" 

// DHT Sensor Setup
#include "DHTesp.h"
#define DHTpin 02
DHTesp dht;

// RainDrop Sensor Setup

const int raindropPin = A0;

//wifi ssid and password
const char* ssid = "EED_N11";
const char* password = "eed@n11N";

ESP8266WebServer server(80); //server on port 80

void handleRoot(){
  String s = MAIN_page; //reads HTML Contents
  server.send(200,"text/html",s); //send web page
}

void handleADC(){
  //DHT SENSOR CODE

  int pressure = bmp.readPressure();

  int altitude = bmp.readAltitude(1013.25);

  int rainValue = analogRead(A0);
  int rain = map(rainValue, 0, 1023, 100, 0);
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  String data = "{\"Rain\":\""+String(rain)+"\",\"Pressure\":\""+String(pressure)+"\",\"Altitude\":\""+String(altitude)+"\", \"Temperature\":\""+ String(temperature) +"\", \"Humidity\":\""+ String(humidity) +"\"}";

  server.send(200, "text/plane", data);
  Serial.println("Humidity: ");
  Serial.print(humidity);

  Serial.println("  Temperature: ");
  Serial.print(temperature);
  Serial.print("'C");

  Serial.println("  Rain: ");
  Serial.print(rain);
  Serial.print("%");

  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");
 
  Serial.print("Approx altitude = ");
  Serial.print(bmp.readAltitude(1013.25)); // this should be adjusted to your local forcase
  Serial.println(" m");

  
}


void setup() {
 Serial.begin(9600);

 Serial.begin(9600);
 Serial.println(F("BMP280 test"));
 if (!bmp.begin(0x76)) {
 Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while(1);
  }
  
 Serial.println();

 dht.setup(DHTpin, DHTesp::DHT11); 

  
WiFi.begin(ssid, password); //Connect to your WiFi router
Serial.println("");
 
// Wait for connection
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
 
//If connection successful show IP address in serial monitor
Serial.println("");
Serial.print("Connected to ");
Serial.println(ssid);
Serial.print("IP address: ");
Serial.println(WiFi.localIP()); //IP address assigned to your ESP

server.on("/", handleRoot); //Which routine to handle at root location. This is display page
server.on("/readADC", handleADC); //This page is called by java Script AJAX
 
server.begin(); //Start server
Serial.println("HTTP server started");
}

void loop(){
  server.handleClient(); //Handle client requests
}
