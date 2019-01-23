
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_BME280.h>
#include <Wire.h>
#define IP "http://192.168.43.251:3001/api/newreading" 


ESP8266WiFiMulti WiFiMulti;
Adafruit_BME280 sensor;
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
Wire.begin();
if(!sensor.begin(0x76)){
  Serial.println("Error: Sensor not found");
}
WiFi.mode(WIFI_STA);
WiFiMulti.addAP("Pixel_3","88888888");
}

void loop() {
  // put your main code here, to run repeatedly:
StaticJsonBuffer<JSON_OBJECT_SIZE(4)>  jbuffer;
String output = "";
JsonObject& data = jbuffer.createObject();

data["name"] = "KarlWiljam";
data["temperature"] = sensor.readTemperature();
data["pressure"] = sensor.readPressure();
data["humidity"] = sensor.readHumidity();

data.prettyPrintTo(Serial);
data.printTo(output);
//Serial.println(sensor.readTemperature());
//Serial.println(sensor.readPressure());
//Serial.println(sensor.readHumidity());

if(WiFiMulti.run() == WL_CONNECTED){
  Serial.println("Connection established, local IP: ");
  Serial.println(WiFi.localIP());
  HTTPClient http;

  http.begin(IP);
  http.addHeader("Content-Type", "application/json");

  int httpcode = http.POST(output);
  if(httpcode == HTTP_CODE_OK){
    Serial.println("Toimii :D");
  }else{
    Serial.println("Ei toimi :c");
    Serial.println(httpcode);
  }
  

}
  Serial.println("...");
  delay(5000);
}
