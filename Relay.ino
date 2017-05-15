float manageRelay(float dF) {
  if (dF > (targetTemp + HYS)) {
    // If we are above boiling or below freezing we have a problem.
    if (dF < ERROR_HIGH_TEMP && dF > ERROR_LOW_TEMP) {
      digitalWrite(RELAY_PIN, HIGH);
    } else {
      Serial.print("Possible probe error. Defaulting of off state.");
      digitalWrite(RELAY_PIN, LOW);
    }
  } else if (dF < (targetTemp + HYS)) {
    digitalWrite(RELAY_PIN, LOW);
  }
  
  // Use the onboard LED to determine relay status
  int relayStatus = digitalRead(RELAY_PIN);
  digitalWrite(LED_PIN, relayStatus);
}
