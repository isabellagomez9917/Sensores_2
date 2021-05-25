#include "Arduino.h"
#define DS1307_I2C_ADDRESS 0x68
#include "RTC.h"
#include "Wire.h"

byte RTC::decToBcd(byte val) {
  return ( (val / 10 * 16) + (val % 10) );
}

byte RTC::bcdToDec(byte val) {
  return ( (val / 16 * 10) + (val % 16) );
}

RTC::RTC(byte _second, byte _minute, byte _hour, byte _dayOfWeek, byte _dayOfMonth, byte _month, byte _year) {
  Wire.begin();
  second = _second;
  minute = _minute;
  hour = _hour;
  dayOfWeek = _dayOfWeek;
  dayOfMonth = _dayOfMonth;
  month = _month;
  year = _year;
  setDS1307time();
}

void RTC::setDS1307time() {

  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0);
  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(dayOfWeek));
  Wire.write(decToBcd(dayOfMonth));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.endTransmission();
}

void RTC::displayTime() {
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
  second = bcdToDec(Wire.read() & 0x7f);
  minute = bcdToDec(Wire.read());
  hour = bcdToDec(Wire.read() & 0x3f);
  dayOfWeek = bcdToDec(Wire.read());
  dayOfMonth = bcdToDec(Wire.read());
  month = bcdToDec(Wire.read());
  year = bcdToDec(Wire.read());
  /*
    Serial.print(hour, DEC);
    Serial.print(":");
    if (minute < 10) {
      Serial.print("0");
    }
    Serial.print(minute, DEC);
    Serial.print(":");
    if (second < 10) {
      Serial.print("0");
    }
    Serial.print(second, DEC);
    Serial.print(" ");
    Serial.print(dayOfMonth, DEC);
    Serial.print("/");
    Serial.print(month, DEC);
    Serial.print("/");
    Serial.print(year, DEC);
    Serial.print(" Day of week: ");
    switch (dayOfWeek) {
      case 1:
        Serial.println("Sunday");
        break;
      case 2:
        Serial.println("Monday");
        break;
      case 3:
        Serial.println("Tuesday");
        break;
      case 4:
        Serial.println("Wednesday");
        break;
      case 5:
        Serial.println("Thursday");
        break;
      case 6:
        Serial.println("Friday");
        break;
      case 7:
        Serial.println("Saturday");
        break;
    }*/
}

bool RTC::isWorking () {
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write (0);
  switch (Wire.endTransmission()) {
    case 0:
      Wire.requestFrom(DS1307_I2C_ADDRESS, 1);
      funcionando = Wire.read() >> 7;
      if (funcionando) {
        /*Serial.println("Not enable")*/;
        return false;
      }
      else {
        //Serial.println("Enable");
        return true;
      }
      break;
    default:
      /*Serial.println ("Not working"); //Dispositivo no dispuesto a recibir
      */ return false;
      break;
  }
}

void RTC::printBinary(byte inByte) {
  for (int b = 7; b >= 0; b--) {
    Serial.print(bitRead(inByte, b));
  }
  Serial.println();
}
