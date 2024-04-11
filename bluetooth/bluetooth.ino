#include <SoftwareSerial.h>

SoftwareSerial bluetoothSerial(10, 11); // RX, TX pins on Arduino

const int maxConnectionAttempts = 5; // Maximum number of connection attempts
const unsigned long reconnectInterval = 5000; // Interval between reconnection attempts (in milliseconds)
const unsigned long connectionTimeout = 10000; // Maximum time to wait for successful connection (in milliseconds)
unsigned long lastReconnectTime = 0; // Timestamp of the last reconnection attempt
unsigned long connectStartTime = 0; // Timestamp of the start of connection attempt

void setup() {
  Serial.begin(9600); // Initialize serial communication for debugging
  bluetoothSerial.begin(9600); // Initialize software serial communication with Bluetooth module
  
  // Wait for the Bluetooth module to initialize
  delay(1000);
  
  // Establish Bluetooth connection
  connectToBluetooth();
}

void loop() {
  // Check if data is available from the Bluetooth module
  if (bluetoothSerial.available()) {
    // Read data from the Bluetooth module
    char data = bluetoothSerial.read();
    
    // Process the received data as needed
    // For example, you can perform actions based on the received data
    
    // Echo back the received data for debugging
    Serial.print("Received data: ");
    Serial.println(data);
  }
  
  // Attempt reconnection if Bluetooth connection is lost
  if (!bluetoothSerial && millis() - lastReconnectTime >= reconnectInterval) {
    Serial.println("Bluetooth connection lost. Reconnecting...");
    reconnectToBluetooth(); // Attempt to reconnect
    lastReconnectTime = millis(); // Update last reconnect time
  }
  
  // Check if connection attempt has timed out
  if (!bluetoothSerial && millis() - connectStartTime >= connectionTimeout) {
    Serial.println("Connection attempt timed out. Retrying...");
    reconnectToBluetooth(); // Retry connection
    connectStartTime = millis(); // Reset connection start time
  }
}

void connectToBluetooth() {
  int attempt = 0;
  while (attempt < maxConnectionAttempts) {
    Serial.println("Connecting to Bluetooth...");
    // Send AT commands to JDY24M module to configure it for communication
    bluetoothSerial.println("AT+NAME=Bluetooth"); // Set Bluetooth name, replace YourBluetoothName with desired name
    delay(500);
    bluetoothSerial.println("AT+ROLE=1"); // Set as slave/peripheral
    delay(500);
    bluetoothSerial.println("AT+RESET"); // Reset module
    delay(500);
    
    // Check if the connection was successful
    if (bluetoothSerial) {
      Serial.println("Bluetooth connected successfully.");
      break; // Exit the loop if connection is successful
    } else {
      Serial.println("Failed to connect to Bluetooth. Retrying...");
      attempt++; // Increment connection attempt counter
    }
  }
  
  if (attempt == maxConnectionAttempts) {
    Serial.println("Reached maximum connection attempts. Please check your hardware and try again.");
    while (true); // Loop indefinitely if maximum connection attempts are reached
  }
}

void reconnectToBluetooth() {
  // End current Bluetooth connection
  bluetoothSerial.end();
  delay(1000); // Delay before re-initialization
  bluetoothSerial.begin(9600); // Re-initialize serial communication with Bluetooth module
  connectToBluetooth(); // Re-establish Bluetooth connection
}
