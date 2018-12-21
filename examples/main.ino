#include <Arduino.h>
#include "OPCN3Mints.h"

#define CS 10
OPCN3Mints OPCN3(CS);
bool OPCN3Online;

void setup() {

  Serial.begin(9600);
  Serial.println("Serial Port Open");

 OPCN3Online = OPCN3.initialize();
 if(OPCN3Online)
  {
  Serial.println("OPC Initialized");
  }else
  {
  Serial.println("OPC Not Initialized");
  }
  delay(1000);
}

// the loop routine runs over and over again forever:
void loop()
 {
 if(OPCN3Online)
 {
  delay(10000);
  OPCN3.readHistogramData();
 }

}
