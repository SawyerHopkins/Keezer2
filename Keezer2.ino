#include "Defs.h"
#include <OneWire.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Create variables
int targetTemp = 65;
int sampleIndex = 0;
float averageTemp = 0;
OneWire sensorController(TEMPERATURE_PIN);

// Create debug variables
int serialActive = false;

// Create LCD variables
int previousScreen = 0;
LiquidCrystal_I2C lcd(0x27,20,4);

void createSerialConnection() {
  if (DEBUG) {
    serialActive = true;
    Serial.begin(9600);
  }
}

void createPinConnections() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}

void setup() {
  lcd.init();
  lcd.backlight();
  createSerialConnection();
  createPinConnections();
  initTemperature();
}

void loop() {
  float temperature = 0;
  boolean hasTemperatureData = false;
  
  // Get the current status of the temperature poller
  //runTemperature(hasTemperatureData, temperature);
  
  // If we have temperature data, run the relay manager
  if (hasTemperatureData) {
    manageRelay(temperature);
  }
  
  // Update the target temperature from the pot
  readFromPot();
  
  // Write to the LCD display
  updateDisplay(temperature);
  
  // Write to debug terminal
  writeLog(temperature);
  
  delay(10);
}

void writeLog(float temperature) {
  if (serialActive) {
    Serial.print("Average Temperature: ");
    Serial.println(temperature);
    Serial.print("Relay status: ");
    Serial.println(digitalRead(RELAY_PIN));
    Serial.print("Pot value: ");
    Serial.println(analogRead(POT_PIN));
    Serial.print("Target value: ");
    Serial.println(targetTemp);
  }
}


