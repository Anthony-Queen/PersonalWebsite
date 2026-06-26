#include <Preferences.h>
#include <WiFi.h>
#include <WiFiClient.h>

const char* ssid = "NotGunnaTellYu";
const char* password = "BeautifulPasswd";

Preferences prefs;

const int buttonPin = 0;
const int LED = 2;
int buttonState = HIGH;
int lastButtonState = HIGH;
int Counter;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 200;

void sendToThingSpeak(int value) {
  WiFiClient client;

  String url = "nuh-uh=" + String(value);

  if (client.connect("api.thingspeak.com", 80)) {
    client.print(String("GET ") + url +
    " HTTP/1.1\r\n" +
    "Host: api.thingspeak.com\r\n" +
    "Connection: close\r\n\r\n");
  }

  client.stop();
}


void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  prefs.begin("count", false);
  Counter = prefs.getInt("count", Counter);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {
    Serial.println("Pressed!");

    ++Counter;
    prefs.putInt("count", Counter);
    sendToThingSpeak(Counter);

    delay(1000); // simple debounce replacement
  }
}
