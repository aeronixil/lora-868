/*---------------------
Send sensor data from dht11 to LORA server demo
Sketch made by miliohm.com
-----------------------*/
#include "DHT.h"
#define DHTPIN 5     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11
#include <SPI.h>
#include <RH_RF95.h>

String strg = "unlimited power!!!!";

RH_RF95 rf95;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
 // Serial.println("i have the high ground");
  if (!rf95.init())
   { Serial.println("init failed");
   //  Serial.println("ive failed you anakin");
   }
  rf95.setFrequency(868.0);
 // Serial.println("iam obi wan kenobi");
}

void loop() {

String data = strg;
  
  int dataLength = data.length(); dataLength++;
  uint8_t total[dataLength]; //variable for data to send
  data.toCharArray(total, dataLength); //change type data from string ke uint8_t
  Serial.println(data);
  rf95.send(total, dataLength); //send data
  rf95.waitPacketSent();
  delay(500);
}
