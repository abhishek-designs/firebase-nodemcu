
/* Connecting to firebase */
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#define led D5
#define led2 D6

WiFiClient client;
const char* ssid = "vivo 1726";
const char* password = "abhishek8221";
const char* dbHost = "ledifi-iot-default-rtdb.firebaseio.com";
const char* dbPassword = "3CfnBhOXt6T1rMSRXM6z3YQ4p1muyxNS15PiUtpk";

FirebaseData firebaseData;

void setup() {
    Serial.begin(115200);
    pinMode(led, OUTPUT);
    pinMode(led2, OUTPUT);
    // Connecting to a access point
    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print("..");
        delay(150);
    }
    Serial.println("Connected to WiFi");
    digitalWrite(led, HIGH);

    Firebase.begin(dbHost, dbPassword);
    Serial.println("Connected to Firebase");
    digitalWrite(led, LOW);
    Firebase.reconnectWiFi(true);
}

void loop() {
    boolean ledCmdFound = Firebase.getInt(firebaseData,"LED_STATUS");
    if(ledCmdFound) {
      int isLedOn = firebaseData.intData();

      if(isLedOn) {
        digitalWrite(led2, HIGH);
      } else {
        digitalWrite(led2, LOW);
      }
    } else {
      Serial.println("Error occured in firebase");
      String err = firebaseData.errorReason();
    }
}