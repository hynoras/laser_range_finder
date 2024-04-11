#include <Wire.h>
#include "VL53L1X.h"

VL53L1X sensor;

void setup() {
  Serial.begin(9600);
  
  // Initialize I2C communication
  Wire.begin();
  
  // Wait for serial monitor to open
  while (!Serial);

  // Initialize the VL53L1X sensor
  if (!sensor.init()) {
    Serial.println("Failed to initialize sensor!");
    while (1);
  }
  
  // Set distance mode (Long range, High speed)
  sensor.setDistanceMode(VL53L1X::Long);
  
  // Start continuous measurements
  sensor.startContinuous(100); // Measurement interval: 100 ms
}

void loop() {
  // Read distance measurement
  uint16_t distance_mm = sensor.read();
  
  // Print distance to serial monitor
  Serial.print("Distance: ");
  Serial.print(distance_mm);
  Serial.println(" mm");
  
  delay(1000); // Delay between measurements
}
