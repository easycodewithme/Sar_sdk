// Uart
// lib dependencies:
// arduino.h
// arduinojson.h

#include <Arduino.h>
#include <ArduinoJson.h>

// Relay control pins
#define RELAY_INFLATE 26  // IN1: inflate solenoid
#define RELAY_DEFLATE 27  // IN2: deflate solenoid

// JSON buffer size
const size_t JSON_BUFFER_SIZE = 256;
char jsonBuffer[JSON_BUFFER_SIZE];

// Status update interval (milliseconds)
const uint32_t STATUS_INTERVAL_MS = 200;

// Track whether default (both relays OFF) has been applied
bool default_settings_applied = true;

// Current state: 0 = home, 1 = grasping, -1 = releasing
int8_t current_state = 0;

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_INFLATE, OUTPUT);
  pinMode(RELAY_DEFLATE, OUTPUT);

  // Default: both solenoids OFF (HIGH = relay OFF for NC type)
  digitalWrite(RELAY_INFLATE, HIGH);
  digitalWrite(RELAY_DEFLATE, HIGH);

  Serial.println("{\"status\":\"ready\",\"message\":\"Soft Gripper initialized\"}");
}

void loop() {


  static uint32_t last_status_ms = 0;
  uint32_t now = millis();

  // 1) Handle incoming JSON
  if (Serial.available()) {
    static size_t index = 0;
    char c = Serial.read();
    if (c == '\n') {
      jsonBuffer[index] = '\0';
      processJSONCommand(jsonBuffer);
      index = 0;
      memset(jsonBuffer, 0, JSON_BUFFER_SIZE);
    } else if (index < JSON_BUFFER_SIZE - 1) {
      jsonBuffer[index++] = c;
    }
  }

  // 2) Periodically send status
  if (now - last_status_ms >= STATUS_INTERVAL_MS) {
    sendStatusFeedback();
    last_status_ms = now;
  }
}

void processJSONCommand(const char* json) {
  // Revert to safe state before handling new input
  if (!default_settings_applied) {
    home();
    delay(50);
  }

  // Parse JSON
  StaticJsonDocument<JSON_BUFFER_SIZE> doc;
  DeserializationError error = deserializeJson(doc, json);
  if (error) {
    Serial.print("{\"status\":\"error\",\"message\":\"Invalid JSON: ");
    Serial.print(error.c_str());
    Serial.println("\"}");
    return;
  }

  JsonObject input = doc["input"];
  if (input.isNull()) {
    Serial.println("{\"status\":\"error\",\"message\":\"Missing input object\"}");
   - return;
  }

  // Handle dropdown command (one of home / grasp / release)
  if (input["home"] == true) {
    home();
    current_state = 0;
  } else if (input["grasp"] == true) {
    grasp();
    current_state = 1;
  } else if (input["release"] == true) {
    release();
    current_state = -1;
  } else {
    Serial.println("{\"status\":\"error\",\"message\":\"Unrecognized or missing command\"}");
    return;
  }

  default_settings_applied = false;
  sendStatusFeedback();
}

void grasp() {
  digitalWrite(RELAY_INFLATE, LOW);   // Enable inflate solenoid
  digitalWrite(RELAY_DEFLATE, HIGH);  // Disable deflate solenoid
}

void release() {
  digitalWrite(RELAY_INFLATE, HIGH);  // Disable inflate solenoid
  digitalWrite(RELAY_DEFLATE, LOW);   // Enable deflate solenoid
}

void home() {
  digitalWrite(RELAY_INFLATE, HIGH);  // Both OFF
  digitalWrite(RELAY_DEFLATE, HIGH);
}

void sendStatusFeedback() {
  StaticJsonDocument<JSON_BUFFER_SIZE> doc;
  JsonObject output = doc.createNestedObject("output");

  const char* state_str = (current_state == 1) ? "grasping" :
                          (current_state == -1) ? "releasing" : "home";
  output["state"] = state_str;
  output["inflate_relay"] = digitalRead(RELAY_INFLATE);
  output["deflate_relay"] = digitalRead(RELAY_DEFLATE);

  serializeJson(doc, Serial);
  Serial.println();
}