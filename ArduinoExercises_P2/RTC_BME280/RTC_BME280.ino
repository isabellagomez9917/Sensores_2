//for RTC
#include "Wire.h"
#include "RTC.h"

//for BME280
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <SPI.h>
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5
#define SEALEVELPRESSURE_HPA (1013.25)

byte datos [7];

Adafruit_BME280 bme(BME_CS); // hardware SPI
RTC rtc = RTC(50, 59, 11, 1, 20, 4, 21); // set RTC

void setup() {
  Serial.begin(9600);
  unsigned status = bme.begin();
}

void loop() {
  byte prueba [7];
  if (Serial.available() > 0) {
    Serial.read();
    if (rtc.isWorking()) {
      rtc.displayTime(); // display the real-time clock data on the Serial Monitor
      datos [0] = rtc.second;
      datos [1] = rtc.minute;
      datos [2] = rtc.hour; 
    }
    sendValaues(bme.readHumidity());
    Serial.write(datos, 7);
  }
}

void sendValaues(float num) {
  static uint8_t arr[4] = {0};
  memcpy(arr, (uint8_t *)&num, 4);
  datos [3] = arr[0];
  datos [4] = arr[1];
  datos [5] = arr[2];
  datos [6] = arr[3];
}

void printValues() {
  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");
  Serial.println();
}
