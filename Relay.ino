float manageRelay() {
  if (currentTemperature > (targetTemperature + HYS)) {
    // If we are above boiling or below freezing we have a problem.
    if (currentTemperature < ERROR_HIGH_TEMP) {
      digitalWrite(RELAY_PIN, HIGH);
    } else {
      Serial.print("Possible probe error. Defaulting of off state.");
      digitalWrite(RELAY_PIN, LOW);
    }
  } else if (currentTemperature < (targetTemperature - HYS)) {
    if (currentTemperature > ERROR_LOW_TEMP) {
      digitalWrite(RELAY_PIN, LOW);
    } else {
      Serial.print("Possible probe error. Defaulting of off state.");
      digitalWrite(RELAY_PIN, LOW);
    }
  }
  
  // Use the onboard LED to determine relay status
  int relayStatus = digitalRead(RELAY_PIN);
  digitalWrite(LED_PIN, relayStatus);
}
