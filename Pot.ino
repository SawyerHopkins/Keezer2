void readFromPot() {
  float range = MAX_TEMPERATURE - MIN_TEMPERATURE;
  // Create a percentage based on the current pin value
  float percentage = (float) analogRead(TARGET_PIN) / (float) MAX_ANALOG;
  float aboveMin = range * percentage;
  aboveMin = floorf(aboveMin * 10) / 10;
  
  // Double check we dont have a negative number
  if (aboveMin < 0) {
    aboveMin *= -1;
  }
  
  // Set the target temperature to the min value plus some positive offset
  targetTemperature = MIN_TEMPERATURE + aboveMin;
}
