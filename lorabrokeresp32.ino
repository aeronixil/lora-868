


#include <WiFi.h>
#include <PubSubClient.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <WiFiManager.h>  


// Replace the next variables with your SSID/Password combination
//const char* ssid = "REPLACE_WITH_YOUR_SSID";
//const char* password = "REPLACE_WITH_YOUR_PASSWORD";

// Add your MQTT Broker IP address, example:
//const char* mqtt_server = "10.32.1.67";
const char* mqtt_server = "43.204.75.88";
#define RXD2 16
#define TXD2 17

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
String str;



// LED Pin
const int ledPin = 4;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Serial Txd is on pin: "+String(TX));
  Serial.println("Serial Rxd is on pin: "+String(RX));
  Serial2.println("commisioning serial2");
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  //status = bme.begin();  

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  Serial.println("mqtt creds set");
  client.setCallback(callback);

  pinMode(ledPin, OUTPUT);
}

void setup_wifi() {

//  WiFi.mode(WIFI.STA);
  WiFi.disconnect(true);
  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP");
  Serial.println("uplink sucsessful");

      

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
 // Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    //Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }

  Serial.println(messageTemp);
  Serial2.println(messageTemp);
  //Serial.println();
//  Serial.println("oh");
//  Serial.println(messageTemp);
//  Serial.println("ha");
//  if(messageTemp == "on")
//  {
//    digitalWrite(25, HIGH);
//    
//  }
//  if(messageTemp == "off")
//  {
//    digitalWrite(25, LOW);
//  }
//  

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client123")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("topic_uno");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(2000);
    }
  }
}
//use this function to send messages to the mesh network

// use this function to send messages to the mqtt network
void uplink_mqtt_publish(String topic, String message)
{
  //client.publish(topic,message);
  //uncomment this
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
  if(Serial.available())
  {
    str = Serial.readString();
    client.publish("batman",str.c_str());
    Serial.println("published data");
  }

  
   
    
  }
}
