#include <Arduino.h>
#include <WiFiNINA.h>
#include <Firebase_Arduino_WiFiNINA.h>

#define FIREBASE_HOST "trafficmechansim-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH  "y6dwiJd7aBuAlQkqyY1ONMwlRwZY6U25KwLnuQ4T"
const char* ssid = "POCO X3 Pro";
const char* pass = "1234567890";

FirebaseData fbData;
String fbPath = "/light/light"; // Modify this to match your Firebase path

// Define constants for traffic light states
const String RED = "RED";
const String BLUE = "BLUE";
const String GREEN = "GREEN";
const String OFF = "OFF";

void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  connectToWiFi();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, ssid, pass);
  Firebase.reconnectWiFi(true);

  setTrafficLightState(OFF); // Set the initial state to "OFF" when the Arduino starts
}

void loop()
{
  String lightState = getTrafficLightState();

  if (lightState == RED || lightState == BLUE || lightState == GREEN || lightState == OFF)
  {
    controlTrafficLight(lightState);
  }
  else
  {
    Serial.println("Error: Invalid state received");
  }
}

void connectToWiFi()
{
  while (WiFi.begin(ssid, pass) != WL_CONNECTED)
  {
    Serial.print(".");
    delay(5000);
  }

  Serial.print("Connected to WiFi network: ");
  Serial.println(ssid);
  Serial.print("Local IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void setTrafficLightState(String state)
{
  if (Firebase.setString(fbData, fbPath, state))
  {
    Serial.print("Firebase state set to: ");
    Serial.println(state);
  }
  else
  {
    Serial.print("Error setting Firebase state: ");
    Serial.println(fbData.errorReason());
  }
}

String getTrafficLightState()
{
  if (Firebase.getString(fbData, fbPath))
  {
    return fbData.stringData();
  }
  else
  {
    Serial.print("Error fetching Firebase state: ");
    Serial.println(fbData.errorReason());
    return "ERROR"; // Return an error value as a String
  }
}

void controlTrafficLight(String state)
{
  if (state == RED)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    Serial.println("RED LED ON");
  }
  else if (state == BLUE)
  {
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    Serial.println("BLUE LED ON");
  }
  else if (state == GREEN)
  {
    digitalWrite(3, LOW);
    digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
    Serial.println("GREEN LED ON");
  }
  else if (state == OFF)
  {
    digitalWrite(3, LOW);
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
    Serial.println("Traffic light OFF");
  }
  else
  {
    Serial.println("Invalid state");
  }
}