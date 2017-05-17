void initTemperature() {
  targetTemperature = 65;
  currentTemperature = 65;
  initSampling();
}

void initSampling() {
  pollingIndex = 0;
  temperaturePollingCache = targetTemperature;
}

void pollTemperature(boolean &hasData, float &temperature) {
  
  // Read the temperature data
  temperaturePollingCache += readTemperaturePin();
  
  // If we have enough samples
  // reset sampling data
  // and manage the relay
  if (pollingIndex >= SAMPLE_COUNT) {
    float dF = convertAndAverageData();
    initSampling();
    hasData = true;
    temperature = dF;
  } else {
    pollingIndex++;
    hasData = false;
    temperature = 0;
  }
}

void recordRecords() {
  if (currentTemperature > allTimeHigh) {
    allTimeHigh = currentTemperature;
  }
  if (currentTemperature < allTimeLow) {
    allTimeLow = currentTemperature;
  }
}

float convertAndAverageData() {
  float sampledAverage = temperaturePollingCache / (float) pollingIndex;
  sampledAverage *= 9;
  sampledAverage /= 5;
  sampledAverage += 32;
  
  return sampledAverage;
}
  
float readTemperaturePin() {
  //returns the temperature from one DS18S20 in DEG Celsius

  byte data[12];
  byte addr[8];

  if ( !sensorController.search(addr)) {
      //no more sensors on chain, reset search
      sensorController.reset_search();
      return -1000;
  }

  if (OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }

  sensorController.reset();
  sensorController.select(addr);
  sensorController.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = sensorController.reset();
  sensorController.select(addr);
  sensorController.write(0xBE); // Read Scratchpad


  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = sensorController.read();
  }

  sensorController.reset_search();

  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;

  return TemperatureSum;
}
