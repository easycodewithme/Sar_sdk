// basic testing
// lib dependency :
// arduino.h

#include <Arduino.h>

// Relay control pins
#define RELAY_INFLATE 26  // IN1: inflate solenoid
#define RELAY_DEFLATE 27  // IN2: deflate solenoid

// Current state: 0 = home, 1 = grasping, 2 = releasing
int current_state = 0;

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_INFLATE, OUTPUT);
  pinMode(RELAY_DEFLATE, OUTPUT);

  // Default: both relays OFF (HIGH = OFF for NC relay module)
  home();

  Serial.println("Soft Gripper ready. Type:");
  Serial.println("1 = Grasp, 2 = Release, 0 = Home");
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();

    switch (cmd) {
      case '1':
        grasp();
        Serial.println("Grasping...");
        current_state = 1;
        break;
      case '2':
        release();
        Serial.println("Releasing...");
        current_state = 2;
        break;
      case '0':
        home();
        Serial.println("Returned to Home");
        current_state = 0;
        break;
      default:
        Serial.println(" Use 1 = Grasp, 2 = Release, 0 = Home");
        break;
    }
  }
}

void grasp() {
  digitalWrite(RELAY_INFLATE, LOW);   // Turn ON inflate
  digitalWrite(RELAY_DEFLATE, HIGH);  // Turn OFF deflate
}

void release() {
  digitalWrite(RELAY_INFLATE, HIGH);  // Turn OFF inflate
  digitalWrite(RELAY_DEFLATE, LOW);   // Turn ON deflate
}

void home() {
  digitalWrite(RELAY_INFLATE, HIGH);  // Both OFF
  digitalWrite(RELAY_DEFLATE, HIGH);
}