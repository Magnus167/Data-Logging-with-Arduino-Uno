
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"

const int chipSelect = 10;
RTC_Millis rtc;
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");


  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");

    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");

}

void loop() {
  DateTime now = rtc.now();
  delay(5000); // You can replace the delay with the amount you need. Be mindful of te fact that it will be in milliseconds.
  // make a string for assembling the data to log:
  String dataString = "";

  // read three sensors and append to the string:
  int analogPin = 0; // 0 here is just arbitary pin number. You need to replace this with your own analog pin number.
  int sensor = analogRead(0);
  dataString = String(sensor);

  dataString += ","  + String(now.year(), DEC) + "_" + String(now.month(), DEC) + "_" + String(now.day(), DEC) + "_" + String(now.hour(), DEC) + ":" + String(now.minute(), DEC) + ":" + String(now.second(), DEC) ;




  File dataFile = SD.open("datalog.txt", FILE_WRITE); //be mindful of the fact that "datalog.txt" is the filename of the TXT file you want to log the data into. It needs to be created before you begin the long.

  // if the file is available, write to it:
  if (dataFile ) {

    dataFile.println(dataString);

    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}







