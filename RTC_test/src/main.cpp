#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

void setup () {
  Serial.begin(9600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC lost power, lets set the time!");
  }
  
  //Following line sets the RTC with an explicit date & time
  rtc.adjust(DateTime(2016, 4, 26, 9, 10, 11));
}

void loop () {
  DateTime timeNow = rtc.now();
  Serial.print("Aktualni cas ");
  Serial.print(timeNow.hour());
  Serial.print(':');
  Serial.print(timeNow.minute());
  Serial.print(':');
  Serial.print(timeNow.second());
  Serial.print(", ");
  Serial.print(timeNow.day());
  Serial.print('.');
  Serial.print(timeNow.month());
  Serial.print('.');
  Serial.print(timeNow.year());
  Serial.println();
  Serial.println();

  String time = String(timeNow.year()) + "-" + String(timeNow.month()) + "-" + String(timeNow.day()) + "-" + String(timeNow.hour()) + "-" + String(timeNow.minute());
  Serial.println(time);

  delay(2000);
}