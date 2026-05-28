#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi and MQTT Setup
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_server = "broker.hivemq.com";
const char* mqtt_topic = "yourunique/smart_light/status"; // Must match Kit 1!

// Pin Configurations for the 2 LEDs
const int LED_A = D1;
const int LED_B = D2;

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

// Callback function handles incoming messages
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");
  
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);

  // Control LEDs based on the received message
  if (message == "ON") {
    digitalWrite(LED_A, HIGH);
    digitalWrite(LED_B, HIGH);
    Serial.println("Remote Lights turned ON");
  } else if (message == "OFF") {
    digitalWrite(LED_A, LOW);
    digitalWrite(LED_B, LOW);
    Serial.println("Remote Lights turned OFF");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-Subscriber-";
    clientId += String(random(0, 0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe(mqtt_topic); // Subscribe to the topic
      Serial.println("Subscribed to topic successfully");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); // Keep the connection alive and handle callbacks
}
