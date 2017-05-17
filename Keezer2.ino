#include "Defs.h"
#include <OneWire.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Create variables
float oldTemp = 0;
int targetTemp = 65;
int sampleIndex = 0;
float averageTemp = 0;
float allTimeHigh = ERROR_LOW_TEMP;
float allTimeLow = ERROR_HIGH_TEMP;
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
  runTemperature(hasTemperatureData, temperature);
  
  // If we have temperature data, run the relay manager
  if (hasTemperatureData) {
    Serial.print("Current Temp: ");
    Serial.println(temperature);
    Serial.print("Target Temp: ");
    Serial.println(targetTemp);
    manageRelay(temperature);
    // Records temperature records
    recordRecords(temperature);
    // Record the current average temperature for future loops
    oldTemp = temperature;
  }
  
  // Update the target temperature from the pot
  readFromPot();
  
  // Write to the LCD display
  updateDisplay(oldTemp);
  
  // Write to debug terminal
  // writeLog(oldTemp);
  
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


