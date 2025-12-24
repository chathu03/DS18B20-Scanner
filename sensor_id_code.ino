#include <OneWire.h>
#include <DallasTemperature.h>

#define SENSOR_PIN 12   // Change if needed

OneWire oneWire(SENSOR_PIN);
DallasTemperature sensors(&oneWire);

DeviceAddress tempDeviceAddress;

void setup() {
  Serial.begin(115200);
  sensors.begin();

  Serial.println("Scanning for DS18B20 sensors...");
  Serial.print("Number of sensors found: ");
  Serial.println(sensors.getDeviceCount());
  Serial.println();
}

void loop() {
  for (uint8_t i = 0; i < sensors.getDeviceCount(); i++) {
    if (sensors.getAddress(tempDeviceAddress, i)) {
      Serial.print("Sensor ");
      Serial.print(i);
      Serial.print(" ID: {");

      for (uint8_t j = 0; j < 8; j++) {
        Serial.print("0x");
        if (tempDeviceAddress[j] < 16) Serial.print("0");
        Serial.print(tempDeviceAddress[j], HEX);
        if (j < 7) Serial.print(", ");
      }
      Serial.println("}");
    } else {
      Serial.print("Unable to find address for sensor ");
      Serial.println(i);
    }
  }

  Serial.println("--------------------------------");
  delay(5000); // scan every 5 seconds
}
