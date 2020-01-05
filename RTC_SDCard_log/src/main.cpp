// Hodiny reálného času DS1307

// připojení knihoven
#include <Wire.h>
#include "RTClib.h"
#include <SPI.h>
#include <SD.h>

RTC_DS1307 rtc;

const int chipSelect = D4;


void printTime();
String formattedTime();
String formattedTimeSec();
String fName(String file);

String fileName = ""; 
int counter = 0;

void setup () {
  Serial.begin(115200);
  
  //RTC setup
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC lost power, lets set the time!");
  }

  //SDCard setup
  Serial.print("Initializing SD card...");
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized."); 

  fileName = formattedTime(); 
  

}

void loop () {  
  File SDCard = SD.open(fileName, FILE_WRITE);

  String dataString = String(fName(formattedTimeSec())) + "," + String(counter);

  if (SDCard) {
    SDCard.println(dataString);
    SDCard.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }  
  
  counter++;
  delay(2000);
}



void printTime()
{
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
}
String formattedTime()
{
  DateTime timeNow = rtc.now();
  return (String(timeNow.year()) + "-" + String(timeNow.month()) + "-" + String(timeNow.day()) + "-" + String(timeNow.hour()) + "-" + String(timeNow.minute()));
}


String formattedTimeSec()
{
  DateTime timeNow = rtc.now();
  return (String(timeNow.year()) + "-" + String(timeNow.month()) + "-" + String(timeNow.day()) + "-" + String(timeNow.hour()) + "-" + String(timeNow.minute()) + "-" + String(timeNow.second()));
}

String fName(String file)
{
  return String(String(file) + ".txt");
}