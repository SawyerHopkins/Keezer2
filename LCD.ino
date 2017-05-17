void updateDisplay() {
  // Use a pot to scan screens like a radio
  short newScreen = (analogRead(SCREEN_PIN) * MAX_SCREENS) / (MAX_ANALOG + 1);
  
  // When we change screen do a full clear
  if (currentScreen != newScreen) {
    lcd.clear();
  }
  
  // Update the current screen
  switch (newScreen) {
    case 0:
      temperatureScreen();
      break;
    case 1:
      runtimeScreen();
      break;
    case 2:
      recordsScreen();
      break;
  }
  
  currentScreen = newScreen;
}

void temperatureScreen() {
  lcd.setCursor(0, 0);
  lcd.print("Current Temperature");
  lcd.setCursor(0, 1);
  lcd.print(currentTemperature);
  lcd.setCursor(0, 2);
  lcd.print("Target Temperature");
  lcd.setCursor(0, 3);
  lcd.print(targetTemperature);
}

void runtimeScreen() {
  unsigned long now = (millis() / 1000);
  unsigned short seconds = now % 60;
  unsigned short minutes = (now / 60) % 60;
  unsigned short hours = (now / 3600) % 24;
  unsigned short days = now / 86400;
  
  lcd.setCursor(0, 0);
  lcd.print("Current Runtime");
  lcd.setCursor(0, 1);
  lcd.print(makeRuntimeString(days));
  lcd.print(":");
  lcd.print(makeRuntimeString(hours));
  lcd.print(":");
  lcd.print(makeRuntimeString(minutes));
  lcd.print(":");
  lcd.print(makeRuntimeString(seconds));
  lcd.setCursor(0, 2);
  lcd.print("Relay state: ");
  if (digitalRead(RELAY_PIN)) {
    lcd.print("on ");
  } else {
    lcd.print("off");
  }
}

void recordsScreen() {
  lcd.setCursor(0, 0);
  lcd.print("Temperature Records");
  lcd.setCursor(0, 1);
  lcd.print("High: ");
  lcd.print(allTimeHigh);
  lcd.setCursor(0, 2);
  lcd.print("Low: ");
  lcd.print(allTimeLow);
}

String makeRuntimeString(unsigned short value) {
  if (value < 10) {
    return "0" + String(value);
  } else {
    return String(value);
  }
}
