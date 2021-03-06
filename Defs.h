// Define digital pins
#define RELAY_PIN 2
#define TEMPERATURE_PIN 4
#define LED_PIN 13

// Define analog pins
#define TARGET_PIN 0
#define SCREEN_PIN 1

// Define resistors
#define R_THERM 4700
#define R_FIXED 4700

// Define thermistor values
#define V_IN 3.3
#define B 3977
#define T0 298
#define R0 4700

// Define hysteresis in degrees F
#define HYS 2

// Define sampling values
#define SAMPLE_COUNT 100

// Define pot values
#define MAX_TEMPERATURE (float) 70.0
#define MIN_TEMPERATURE (float) 40.0

// Define error values
#define ERROR_HIGH_TEMP 212
#define ERROR_LOW_TEMP 32

// Define debugging
#define DEBUG false

// Define analog
#define MAX_ANALOG 1023

// Define screens
#define MAX_SCREENS 3
