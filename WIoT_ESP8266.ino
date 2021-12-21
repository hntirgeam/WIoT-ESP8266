/*

This sketch is written for WIoT project that can be found here: https://github.com/hntirgeam/WIoT-Logger

*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <Adafruit_Sensor.h>                
#include <Adafruit_BME280.h>                  // https://github.com/adafruit/Adafruit_BME280_Library

#include "MHZ19.h"                            // https://github.com/WifWaf/MH-Z19
#include <Wire.h>
#include <SoftwareSerial.h>

#define RX_PIN D6                             // MH-Z19B RX pin. If compiling on linux cause errors here, try using 12  
#define TX_PIN D5                             // MH-Z19B TX pin                                                 and 14
#define MHZ19_BAUDRATE 9600                   // Should not be changed

#define SEALEVELPRESSURE_HPA (1013.25)

#define WIFI_SSID ""                          // Your Wi-Fi name
#define WIFI_PASS ""                          // Your Wi-Fi password
#define BASE_URL  "http://x.x.x.x:x/records/" // Local or remote url 
#define API_KEY ""                            // Device API_KEY (you'll receive it after device creation)

#define UPDATE_TIME 1000                      // Time between requests

unsigned long getDataTimer = 0;

Adafruit_BME280 bme;
MHZ19 myMHZ19;
SoftwareSerial mySerial(RX_PIN, TX_PIN);

HTTPClient http;
WiFiClient wifi_client;

void setup()
{
  Serial.begin(115200);

  connectWifi();

  Serial.println("WiFi Connected!");
  Serial.print("IP: ");
  Serial.print(WiFi.localIP());

  if (!bme.begin(0x76))
  {
    Serial.println("Could not find BME280. Check wiring!");
    while (1);
  }

  mySerial.begin(MHZ19_BAUDRATE);

  myMHZ19.begin(mySerial);
  myMHZ19.autoCalibration(false);
}

void loop()
{
  if (millis() - getDataTimer >= UPDATE_TIME && WiFi.status() == WL_CONNECTED)
  {
    float temp, f_temp, humid, pressure;
    int co2;

    getValues(temp, f_temp, humid, pressure, co2);
    int response_code = sendValues(temp, humid, pressure, co2);

    Serial.print("Response code: ");
    Serial.println(response_code);

    getDataTimer = millis();
  }
}

void getValues(float & temp, float & f_temp, float & humid, float & pressure, int & co2) 
{
  co2 = myMHZ19.getCO2();

  temp = bme.readTemperature();
  f_temp = 1.8 * temp + 32;

  humid = bme.readHumidity();
  pressure = bme.readPressure() / 100.0F;
}

int sendValues(const float & temp, const float & humid, const float & pressure, const int & co2)
{
  http.begin(wifi_client, BASE_URL);
  http.addHeader("Content-Type", "application/json");

  String msg = "";

  msg += "{";
  msg += "\"api_key\":\"";  msg += API_KEY;   msg += "\"";  msg += ",";
  msg += "\"temp\":";       msg += temp;      msg += ",";
  msg += "\"humidity\":";   msg += humid;     msg += ",";
  msg += "\"pressure\":";   msg += pressure;  msg += ",";
  msg += "\"CO2\":";        msg += co2;
  msg += "}";

  int response_code = http.POST(msg);
  http.end();

  return response_code;
}

void connectWifi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("*");
  }
  Serial.println();
}
