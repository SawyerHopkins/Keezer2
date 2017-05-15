void updateDisplay(float temperature) {
  lcd.setCursor(0, 0);
  lcd.print("Current Temperature");
  lcd.setCursor(0, 1);
  lcd.print(temperature);
  lcd.setCursor(0, 2);
  lcd.print("Target Temperature");
  lcd.setCursor(0, 3);
  lcd.print(targetTemp);
}
