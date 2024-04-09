#include <Wire.h>

#define TOF10120_ADDRESS 0x52 // Address of the TOF10120 sensor

bool measurementRequested = false;

void setup() {
  // Initialize I2C communication for TOF10120 sensor
  Wire.begin();
  
  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Check if a measurement is requested
  if (measurementRequested) {
    // Perform distance measurement
    int distance = measureDistance();
    
    // Send distance measurement over Bluetooth
    Serial.println(distance);
    
    // Reset measurement flag
    measurementRequested = false;
  }
  
  // Add other loop logic here if needed
}

int measureDistance() {
  // Request distance measurement from the TOF10120 sensor
  Wire.beginTransmission(TOF10120_ADDRESS);
  Wire.write(0x00); // Register address for distance measurement
  Wire.endTransmission();
  
  // Read distance measurement (2 bytes)
  Wire.requestFrom(TOF10120_ADDRESS, 2);
  int distance_raw = (Wire.read() << 8) | Wire.read();
  
  // Convert distance to centimeters
  return distance_raw * 0.01; // Each unit is 1 cm
}

void serialEvent() {
  // Read command from serial input
  String command = Serial.readStringUntil('\n');
  
  // Check if the command is "measure"
  if (command.equals("measure")) {
    // Set flag to indicate measurement is requested
    measurementRequested = true;
  }
}
