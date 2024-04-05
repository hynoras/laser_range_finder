#include <Wire.h>

#define TOF10120_ADDRESS 0x52 // Address of the TOF10120 sensor

void setup() {
  // Initialize I2C communication for TOF10120 sensor
  Wire.begin();
  
  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Request distance measurement from the TOF10120 sensor
  Wire.beginTransmission(TOF10120_ADDRESS);
  Wire.write(0x00); // Register address for distance measurement
  Wire.endTransmission();
  
  // Read distance measurement (2 bytes)
  Wire.requestFrom(TOF10120_ADDRESS, 2);
  int distance_raw = (Wire.read() << 8) | Wire.read();
  
  // Convert distance to centimeters
  float distance_cm = distance_raw * 0.01; // Each unit is 1 cm
  
  // Print distance measurement for debugging
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  
  // Transmit distance measurement over Bluetooth
  transmitOverBluetooth(distance_cm);
  
  delay(1000); // Delay before next measurement
}

void transmitOverBluetooth(float distance_cm) {
  // Convert float distance to string
  String distanceString = String(distance_cm);
  
  // Send distance data over serial to Bluetooth module
  Serial.println(distanceString);
}
