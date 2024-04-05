#include <Wire.h>

#define TOF10120_ADDRESS 0x52 // Address of the TOF10120 sensor

void setup() {
  Wire.begin(); // Initialize I2C communication
  Serial.begin(9600); // Initialize serial communication
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
  
  // Print distance measurement
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  
  // Check if an object is within 200 cm
  if (distance_cm <= 200) {
    Serial.println("Object detected within 200 cm");
  } else {
    Serial.println("No object within 200 cm");
  }
  
  delay(1000); // Delay before next measurement
}
