void updateDisplay(float temperature) {
  // Use a pot to scan screens like a radio
  short currentScreen = (analogRead(SCREEN_PIN) * MAX_SCREENS) / (MAX_ANALOG + 1);
  
  // When we change screen do a full clear
  if (currentScreen != previousScreen) {
    lcd.clear();
  }
  
  switch (currentScreen) {
    case 0:
      temperatureScreen(temperature);
      break;
    case 1:
      runtimeScreen();
      break;
  }
  
  
  previousScreen = currentScreen;
}

void temperatureScreen(float temperature) {
  lcd.setCursor(0, 0);
  lcd.print("Current Temperature");
  lcd.setCursor(0, 1);
  lcd.print(temperature);
  lcd.setCursor(0, 2);
  lcd.print("Target Temperature");
  lcd.setCursor(0, 3);
  lcd.print(targetTemp);
}

void runtimeScreen() {
  unsigned long now = (millis() / 1000);
  unsigned short seconds = now % 60;
  unsigned short minutes = (now / 60) % 60;
  unsigned short hours = (now / 3600) % 24;
  unsigned short days = now / 86400;
  
  lcd.setCursor(0, 2);
  lcd.print("Current Runtime");
  lcd.setCursor(0, 3);
  lcd.print(makeRuntimeString(days));
  lcd.print(":");
  lcd.print(makeRuntimeString(hours));
  lcd.print(":");
  lcd.print(makeRuntimeString(minutes));
  lcd.print(":");
  lcd.print(makeRuntimeString(seconds));
}

String makeRuntimeString(unsigned short value) {
  if (value < 10) {
    return "0" + String(value);
  } else {
    return String(value);
  }
}
