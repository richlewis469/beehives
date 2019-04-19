/*
  SD card basic file example
 */
#include <SPI.h>

#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

// #include <SD.h>
#include <SdFat.h>
SdFat SD;

File myFile;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  if (SD.exists("example.txt")) {
    Serial.println("example.txt exists.");
  } else {
    Serial.println("example.txt doesn't exist.");
  }

  // open a new file and write date to it:
  Serial.println("Creating example.txt...");
  myFile = SD.open("example.txt", FILE_WRITE);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
  } else {
    DateTime now = rtc.now();  
    myFile.print(now.year(), DEC);
    myFile.print('/');
    myFile.print(now.month(), DEC);
    myFile.print('/');
    myFile.print(now.day(), DEC);
    myFile.print(" (");
    myFile.print(daysOfTheWeek[now.dayOfTheWeek()]);
    myFile.print(") ");
    myFile.print(now.hour(), DEC);
    myFile.print(':');
    myFile.print(now.minute(), DEC);
    myFile.print(':');
    myFile.print(now.second(), DEC);
    myFile.print(" - Arduino Powered On.");
    myFile.println();
  }
    
  myFile.close();

  // Check to see if the file exists:
  if (SD.exists("example.txt")) {
    Serial.println("example.txt exists.");
  } else {
    Serial.println("example.txt doesn't exist.");
  }

}

void loop() {
  // nothing happens after setup finishes.
}
