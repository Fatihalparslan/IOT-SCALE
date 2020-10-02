#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
int rxPin = D6;                                               //ESP8266 RX pini
int txPin = D5;                                               //ESP8266 TX pini
SoftwareSerial esp(rxPin, txPin);                             //Seri haberleşme pin ayarlarını yapıyoruz.
//Enter your wifi credentials
const char* ssid = "TurkTelekom_T32AD";
const char* wifi_password = "gpvqvx0q";

const char* mqtt_server = "192.168.1.102";
const char* mqtt_topic = "test";
const char* mqtt_username = "fatih";
const char* mqtt_password = "alparslan";
// The client id identifies the ESP8266 device. Think of it a bit like a hostname (Or just a name, like Greg).
const char* clientID = "Client ID";
  float x;
  char strng[100];
WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient);
void setup() {
  Serial.begin(9600);
  esp.begin(9600);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect to the WiFi
  WiFi.begin(ssid, wifi_password);

  // Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Debugging - Output the IP Address of the ESP8266
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // put your setup code here, to run once:
  if (client.connect(clientID, mqtt_username, mqtt_password)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
  }
}

void loop() {

while (esp.available() > 0) {
    String Data = esp.readStringUntil('\r');
if(Data!="\n"){
    if (client.publish(mqtt_topic,Data.c_str())) {
    }
    else {
      Serial.println("Message failed to send. Reconnecting to MQTT Broker and trying again");
      client.connect(clientID, mqtt_username, mqtt_password);
      delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
      client.publish(mqtt_topic,Data.c_str());
    }
  }
}
}
