//use arduino mega, rs485 module
// DE/RE to pin 45
// DO to pin 18 ,  RO to pin 19
#include <HardwareSerial.h> // Include HardwareSerial library
#include <dds238.h>         // Include dds238 library

#define DERE_PIN 45          // Define the control pin for DE/RE

// Create an instance of the dds238 class using the HardwareSerial
dds238 dds238(Serial, 9600, DERE_PIN); // Use Serial for dds238 communication

void setup() {
  Serial.begin(115200);    // Initialize Serial for debugging
  Serial.begin(9600);      // Initialize HardwareSerial for DDS238 communication
  pinMode(DERE_PIN, OUTPUT); // Set DE/RE pin as output
  digitalWrite(DERE_PIN, LOW); // Set to receive mode initially
  dds238.begin();          // Initialize DDS238 communication
}

void loop() {
  // Set to transmit mode before sending data
  digitalWrite(DERE_PIN, HIGH);
  
  // Read and scale the voltage
  float voltage = dds238.readVal(dds238_VOLTAGE, 2) / 10.0; // Scale the voltage
  Serial.print("Voltage: ");
  Serial.print(voltage, 2); // Display voltage
  Serial.println(" V");

  delay(50);

  // Read and scale the frequency
  float frequency = dds238.readVal(dds238_FREQUENCY, 2) / 100.0; // Scale the frequency
  Serial.print("Frequency: ");
  Serial.print(frequency, 2); // Display frequency
  Serial.println(" Hz");

  // Set to receive mode after transmission
  digitalWrite(DERE_PIN, LOW); 
  delay(1000); // Wait a while before the next loop
}
