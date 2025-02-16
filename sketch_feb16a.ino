#include "thingProperties.h"

// Define HC-SR04 sensor pins
const int trigPin = 9;
const int echoPin = 10;

// Alarm threshold (distance in cm)
const int alarmThreshold = 10;

void setup() {
    Serial.begin(115200);
    delay(1500);

    // Initialize Arduino IoT Cloud
    initProperties();
    ArduinoCloud.begin(ArduinoIoTPreferredConnection);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    Serial.println("Ultrasonic Sensor Alarm System Started!");
}

void loop() {
    ArduinoCloud.update();  // Update IoT cloud connection
    readUltrasonic();       // Read distance from sensor
    checkAlarm();           // Check if distance is below threshold
    delay(1000);            // Delay for stability
}

// Function to read distance from HC-SR04
void readUltrasonic() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    long duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2; // Convert to cm

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
}

// Function to check if distance is below threshold and trigger alarm
void checkAlarm() {
    if (distance < alarmThreshold) {
        alarmState = true;
        Serial.println("⚠ ALERT: Object too close! Alarm Triggered.");
    } else {
        alarmState = false;
    }
}

// Callback function for when 'distance' variable changes
void onDistanceChange() {
    Serial.print("Distance changed: ");
    Serial.println(distance);
}

// Callback function for when 'alarmState' variable changes
void onAlarmStateChange() {
    Serial.print("Alarm state changed: ");
    Serial.println(alarmState ? "ON" : "OFF");
}