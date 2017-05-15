void readFromPot() {
  int range = MAX_TEMPERATURE - MIN_TEMPERATURE;
  // Create a percentage based on the current pin value
  float percentage = (float) analogRead(POT_PIN) / (float) MAX_ANALOG;
  float aboveMin = (float) range * percentage;
  
  // Double check we dont have a negative number
  if (aboveMin < 0) {
    aboveMin *= -1;
  }
  
  // Set the target temperature to the min value plus some positive offset
  targetTemp = MIN_TEMPERATURE + ((int) aboveMin);
}
