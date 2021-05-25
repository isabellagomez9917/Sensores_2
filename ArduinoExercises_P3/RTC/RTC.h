#ifndef RTC_h
#define RTC_h

#include "Arduino.h"

class RTC
{
  public:
    RTC(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year);
    void displayTime();
    bool isWorking();
    byte second;
    byte minute;
    byte hour;
    byte dayOfWeek;
    byte dayOfMonth;
    byte month;
    byte year;

  private:
    void setDS1307time();
    byte decToBcd(byte val);
    byte bcdToDec(byte val);
    void printBinary(byte inByte);
    byte funcionando;

};

#endif
