//#include <HTTPClient.h>
#include "Arduino.h"

#include "WiFi.h"

int button_call_api = 8;
String url = "http://localhost:5656/ocpu/library/OGarraDocker/R/GetAllSQLiteData";


void setup() {
  pinMode(button_call_api, INPUT);

  Serial.begin(9600);
}

void loop() {
  bool call_api = digitalRead(button_call_api);
  Serial.println(call_api);

  // if (call_api == 1) {}

  // Initialize the client library
  HTTPClient http;
  http.begin(url);

  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST("");

  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);
    
  // Free resources
  http.end();



  // if there are incoming bytes available
  // from the server, read them and print them:
  // while (client.available()) {
  //   char c = client.read();
  //   Serial.println(c);
  //   delay(5000);
  //   Serial.println("Ta aqui?");
  // }

  delay(5000);
}