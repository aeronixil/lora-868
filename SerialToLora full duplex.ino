

#include <SPI.h>
#include <RH_RF95.h>

RH_RF95 rf95;

// Singleton instance of the radio driver

int led = 9;
String strg = "unlimited power!!!!";

void setup() {
  Serial.begin(9600);
  Serial.println("i have the high ground");
  if (!rf95.init())
   { Serial.println("init failed");
     Serial.println("ive failed you anakin");
   }
  rf95.setFrequency(868.0);
  Serial.println("iam obi wan kenobi");
}

void loop()
{
  
  if (rf95.available())
  {
    uplink_loraReceive();
  }
  while(Serial.available()) 
   {
    Serial.println("transmitting ");
   strg = Serial.readString();
   uplink_loraTransmit(strg);
   }
}

void uplink_loraTransmit(String data)
{
  
  int dataLength = data.length(); dataLength++;
  uint8_t total[dataLength]; //variable for data to send
  data.toCharArray(total, dataLength); //change type data from string ke uint8_t
  Serial.println(data);
  rf95.send(total, dataLength); //send data
  rf95.waitPacketSent();
  
}

void uplink_loraReceive()
{
  Serial.println("lightning mcqueen");
    // Should be a message for us now   
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf95.recv(buf, &len))
    {
      digitalWrite(led, HIGH);
//      RH_RF95::printBuffer("request: ", buf, len);
      Serial.print("got request: ");
      Serial.println((char*)buf);
//      Serial.print("RSSI: ");
//      Serial.println(rf95.lastRssi(), DEC);
      
      // Send a reply
//      uint8_t data[] = "";
//      rf95.send(data, sizeof(data));
//      rf95.waitPacketSent();
//      Serial.println("");
//       digitalWrite(led, LOW);
    }
    else
    {
      Serial.println("recv failed");
    }
}
