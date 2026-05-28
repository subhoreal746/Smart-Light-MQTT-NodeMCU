#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi and MQTT Setup
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_server = "broker.hivemq.com";
const char* mqtt_topic = "yourunique/smart_light/status"; // Change this!

// Pin Configurations
const int LDR_PIN = A0;
const int LED_PIN = D1;

// Threshold for darkness (0 to 1024). Lower means darker.
const int DARKNESS_THRESHOLD = 400; 

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-Publisher-";
    clientId += String(random(0, 0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Read LDR Value
  int ldrValue = analogRead(LDR_PIN);
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // Check threshold and publish state
  if (ldrValue < DARKNESS_THRESHOLD) {
    digitalWrite(LED_PIN, HIGH); // Turn on local light
    client.publish(mqtt_topic, "ON");
    Serial.println("Status Published: ON");
  } else {
    digitalWrite(LED_PIN, LOW);  // Turn off local light
    client.publish(mqtt_topic, "OFF");
    Serial.println("Status Published: OFF");
  }

  delay(2000); // Send data every 2 seconds
}
