/**
 * DIY Incubator using Arduino
 * 
 * Description:
 * This waterproof DS18B20 sensors and relays to control the temperature
 * of an incubator.
 * 
 * Author: jjroth89
 * Date: February 2023
 * 
 * @author jjroth89
 * @version 0.1.2
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

#define ONE_WIRE_BUS A0
#define RELAY_HEAT_PIN A1

// Set incubator target temperature
const int tempTargetAvg = 34;

// Declare average temperature variable
float tempAvg;

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
  pinMode(RELAY_HEAT_PIN, OUTPUT);
  dbl("RELAY PINS INITIALIZED");

  dbl("BOOT COMPLETE");
  dbl();
}

void loop() {
  sensors.requestTemperatures();
  float tempFloor = sensors.getTempCByIndex(1);
  float tempRoom = sensors.getTempCByIndex(0);

  // If the thermometer is not properly installed, its reading will return -127 and mess with the average temperature
  // Error handling for such scenarios
  if (tempFloor < -100) {
    tempAvg = tempRoom;
    dbl("ERROR: CHECK FLOOR THERMOMETER!");
  } else if (tempRoom < -100) {
    tempAvg = tempFloor;
    dbl("ERROR: CHECK ROOM THERMOMETER!");
  } else {
    tempAvg = (tempFloor + tempRoom) / 2;
  }

  db("FLOOR temperature: ");
  db(tempFloor);
  dbl("??C");
  db("ROOM temperature: ");
  db(tempRoom);
  dbl("??C");
  db("AVERAGE temperature: ");
  db(tempAvg);
  dbl("??C");
  db("TARGET temperature: ");
  db(tempTargetAvg);
  db("??C - ");
  if (tempAvg < tempTargetAvg) {
    dbl("Heating ON");
    dbl();
    digitalWrite(RELAY_HEAT_PIN, HIGH);
  } else {
    dbl("Heating OFF");
    dbl();
    digitalWrite(RELAY_HEAT_PIN, LOW);
  }

delay(60000);

}

/*
TODO - Add OLED display
TODO - Add humidity/temperature sensor
 */
