/**
 * DIY Sous-Vide Temperature Control using Arduino
 * 
 * Description:
 * This code uses a Keypad, a waterproof DS18B20 sensor, and relays
 * to control the temperature of a DIY Sous-Vide cooking setup.
 * 
 * Author: jjroth89
 * Date: January 2023
 * 
 * @author jjroth89
 * @version 0.3.2
 */

#include <OneWire.h>
#include <DallasTemperature.h>

// Define DEBUG mode to TRUE. If FALSE, all serial print commands will be removed when compiling, thus disabling them.
#define DEBUG 1

#if DEBUG == 1
#define dbp(x, precision) Serial.print(x, precision)
#define dblp(x, precision) Serial.println(x, precision)
#define db(x) Serial.print(x)
#define dbl(x) Serial.println(x)
#endif

// Define OneWire bus, heat source and water pump pins
#define ONE_WIRE_BUS A0
#define HEAT_RELAY_PIN A1

// Set incubator target temperature
const int targetTemp = 34;

// Setup a OneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our OneWire reference to the Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

void setup() {
  delay(1500),        // Prevent garbage from first serial monitor run
  Serial.begin(9600);

  //! "Clears" the serial monitor for better viewing
  #if DEBUG == 1
  for (int i = 0; i < 60; i++) {
    dbl();
  }
  #endif
  dbl("SERIAL PORT INITIALIZED");

  // Start up the sensor's library
  sensors.begin();
  dbl("TEMPERATURE SENSORS INITIALIZED");


  // Configure the relay pins as outputs
  pinMode(HEAT_RELAY_PIN, OUTPUT);
  dbl("RELAY PINS INITIALIZED");

  dbl("BOOT COMPLETE");
  dbl();
}

void loop() {
sensors.requestTemperatures();
//db("Current temperature: ");
//db(sensors.getTempCByIndex(0));
//dbl("ºC");
//db("Target temperature: ");
//db(targetTemp);
//db("ºC - ");
//if (sensors.getTempCByIndex(0) < targetTemp) {
//  dbl("Heating ON");
//  dbl();
//  digitalWrite(HEAT_RELAY_PIN, HIGH);
//} else {
//  dbl("Heating OFF");
//  dbl();
//  digitalWrite(HEAT_RELAY_PIN, LOW);

dbl(sensors.getTempCByIndex(0));

delay(5000);
}