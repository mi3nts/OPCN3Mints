#include <Arduino.h>
// #include <devicesMints.h>
// #include <jobsMints.h>
//
// #include <Wire.h>
// #include <Adafruit_HTU21DF.h>
// #include <Adafruit_INA219.h>
 #include "OPCN3Mints.h"


// Adafruit_HTU21DF htu = Adafruit_HTU21DF();
// Adafruit_BMP280 bme;
// Adafruit_INA219 ina219;
// uint32_t currentFrequency;

// bool serialOut = true;

#define CS 10
OPCN3Mints OPCN3(CS);
// String inputString = "";         // a String to hold incoming data
// bool stringComplete = false;  // whether the string is complete
bool OPCN3Online;

void setup() {

  Serial.begin(9600);
  Serial.println("Serial Port Open");

//  initializeSerialMints();
//  initializeHTU21DMints();
//  initializeBMP280Mints();

//  inputString.reserve(200);
//  SerialUSB.begin(9600);

 OPCN3Online = OPCN3.initialize();
 if(OPCN3Online){
 Serial.println("OPC Initialized");
 }else{
     Serial.println("OPC Not Initialized");
 }

   delay(1000);
}


// the loop routine runs over and over again forever:
void loop() {

    if(OPCN3Online)
    {
      delay(10000);
      OPCN3.readHistogramData();
     }

      // delay(5000);
      // OPCN3.readPMData();
      //
   //   // // }
   //  float  lk = 12.2392;
   //  String lks = String(lk,4);
   //  Serial.println(lks);
   //  // String lkt = {"sskjfsf","fjfsadffg"};
   //  // sensorPrintMints("HTU21D",lkt,2);
   //
   // String ordinal[5] = { "first", "second", "third", "fourth", "fifth"};
   //
   //
   //  sensorPrintMints("String sensor",ordinal,5);

}



//
