#include "Defs.h"
#include <Wire.h> 
#include <OneWire.h>
#include <LiquidCrystal_I2C.h>

// Create variables
short pollingIndex = 0;
float targetTemperature = 65;
float currentTemperature = 0;
float temperaturePollingCache = 0;
OneWire sensorController(TEMPERATURE_PIN);

// Create records variables
float allTimeHigh = ERROR_LOW_TEMP;
float allTimeLow = ERROR_HIGH_TEMP;

// Create LCD variables
short currentScreen = 0;
LiquidCrystal_I2C lcd(0x27,20,4);

void createSerialConnection() {
  Serial.begin(9600);
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
  preUpdate();
  update();
  postUpdate();
  delay(10);
}

void preUpdate() {
  float newTemperature = 0;
  boolean hasTemperatureData = false;
  
  // Get the current status of the temperature poller
  pollTemperature(hasTemperatureData, newTemperature);
  
  // If we have new temperature data, set it.
  if (hasTemperatureData) {
    currentTemperature = newTemperature; 
  }
}

void update() {
  // Manage the relay state
  manageRelay();
  
  // Records temperature records
  recordRecords();
  
  // Update the target temperature from the pot
  readFromPot();
  
  // Write to the LCD display
  updateDisplay();
}

void postUpdate() {
  // Write to debug terminal
  writeLog();
}


void writeLog() {
  if (DEBUG) {
    Serial.print("Average Temperature: ");
    Serial.println(currentTemperature);
    Serial.print("Relay status: ");
    Serial.println(digitalRead(RELAY_PIN));
    Serial.print("Pot value: ");
    Serial.println(analogRead(TARGET_PIN));
    Serial.print("Target value: ");
    Serial.println(targetTemperature);
  }
}


