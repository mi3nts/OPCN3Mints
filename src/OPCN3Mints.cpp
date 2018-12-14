/***************************************************************************
  OPCN3Mints
  ---------------------------------
  Written by: Lakitha Omal Harindha Wijeratne
  - for -
  Mints: Multi-scale Integrated Sensing and Simulation
  ---------------------------------
  Date: November 29th, 2018
  ---------------------------------
  This library is written for the Alphasense OPCN3 optical particle counter.
  ----------------> http://www.alphasense.com/WEB1213/wp-content/uploads/2018/02/OPC-N3.pdf
  --------------------------------------------------------------------------
  https://github.com/mi3nts
  http://utdmints.info/

 ***************************************************************************/

#include "OPCN3Mints.h"
#include <Arduino.h>
#include <SPI.h>
/***************************************************************************
 PRIVATE FUNCTIONS
 ***************************************************************************/

 OPCN3Mints::OPCN3Mints(uint8_t chipSelect){
  alphaSlavePin  = chipSelect;
 }

// Alpha Sensor Functions
 void OPCN3Mints::begin()
{
    printMintsBegin();
    Serial.println("Initiating SPI ");
    SPI.begin(alphaSlavePin);
    SPI.setBitOrder(MSBFIRST);
    delay(1000);
    pinMode(alphaSlavePin,OUTPUT);
    digitalWrite(alphaSlavePin,HIGH);
    SPI.setDataMode(alphaSlavePin, 0);
    SPI.setClockDivider(alphaSlavePin,168);
    delay(400);
    Serial.println("---------------------------- ");
    printMintsEnd();

}


bool OPCN3Mints::initialize(){

        delay(1000);
        begin();
        delay(1000);
        readDACandPowerStatus();
        delay(1000);
        readInformationString();
        delay(1000);
        readSerialNumber();
        delay(1000);
        readFirmwareVersion();
        delay(1000);
        readConfigurationVariables();
        delay(10000);
        struct fanDigitalPotShutdownState fanState = setFanDigitalPotShutdownState(true);
        delay(1000);
        struct laserDigitalPotShutdownState laserState = setLaserDigitalPotShutdownState(true);
        delay(1000);
        struct highLowGainState gainState =  setHighLowGainState(true);
        delay(1000);
        bool reset = resetHistogram() ;
        return (fanState.valid&&reset)&&(laserState.valid&&gainState.valid);

  }







  struct fanDigitalPotShutdownState OPCN3Mints::setFanDigitalPotShutdownState(bool status) {

        printMintsBegin();
        Serial.println("Setting Fan Digital Pot Shutdown State");
        int  size = 1;
        byte validator[2] = {0X31,0XF3};
        byte dataIn[size];
        byte initial[2];
        byte inputByte  =  0X03;;

        if(status){
            Serial.println("Turning Fan On");
            beginTransfer();
            initial[0] = SPI.transfer(alphaSlavePin,inputByte);
            delay(10);
            initial[1] = SPI.transfer(alphaSlavePin,inputByte);
            delayMicroseconds(10);
            dataIn[0] = SPI.transfer(alphaSlavePin,0X03);
            endTransfer();
        }else{

          Serial.println("Turning Fan Off");
          beginTransfer();
          initial[0] = SPI.transfer(alphaSlavePin,inputByte);
          delay(10);
          initial[1] = SPI.transfer(alphaSlavePin,inputByte);
          delayMicroseconds(10);
          dataIn[0] = SPI.transfer(alphaSlavePin,0X02);
          endTransfer();
        }



       printBytesRead(initial,dataIn,size);


       fanDigitalPotShutdownState dataOutput;
       dataOutput.valid        = comparator(validator, initial,2);
       dataOutput.fanOn        = status;




     Serial.print("Validity: ");
     Serial.println(dataOutput.valid);
     Serial.print(dataOutput.fanOn);    Serial.print(" ");
     printMintsEnd();

       return dataOutput;
    }


    struct laserDigitalPotShutdownState OPCN3Mints::setLaserDigitalPotShutdownState(bool status) {

          printMintsBegin();
          Serial.println("Setting Laser Digital Pot Shutdown State");
          int  size = 1;
          byte validator[2] = {0X31,0XF3};
          byte dataIn[size];
          byte initial[2];
          byte inputByte  =  0X03;;

          if(status){
             Serial.println("Turning Laser On");
             beginTransfer();
             initial[0] = SPI.transfer(alphaSlavePin,inputByte);
             delay(10);
             initial[1] = SPI.transfer(alphaSlavePin,inputByte);
             delayMicroseconds(10);
             dataIn[0] = SPI.transfer(alphaSlavePin,0X05);
             endTransfer();
          }else{
            Serial.println("Turning Laser Off");
            beginTransfer();
            initial[0] = SPI.transfer(alphaSlavePin,inputByte);
            delay(10);
            initial[1] = SPI.transfer(alphaSlavePin,inputByte);
            delayMicroseconds(10);
            dataIn[0] = SPI.transfer(alphaSlavePin,0X04);
            endTransfer();
          }

         printBytesRead(initial,dataIn,size);


         laserDigitalPotShutdownState dataOutput;
         dataOutput.valid          = comparator(validator, initial,2);
         dataOutput.laserOn        = status;

       Serial.print("Validity: ");
       Serial.println(dataOutput.valid);
       Serial.print(dataOutput.laserOn);    Serial.print(" ");
       printMintsEnd();

         return dataOutput;
      }



      struct highLowGainState OPCN3Mints::setHighLowGainState(bool status) {

            printMintsBegin();
            Serial.println("Setting Gain State");
            int  size = 1;
            byte validator[2] = {0X31,0XF3};
            byte dataIn[size];
            byte initial[2];
            byte inputByte  =  0X03;;

            if(status){
               Serial.println("Setting a High Gain");
               beginTransfer();
               initial[0] = SPI.transfer(alphaSlavePin,inputByte);
               delay(10);
               initial[1] = SPI.transfer(alphaSlavePin,inputByte);
               delayMicroseconds(10);
               dataIn[0] = SPI.transfer(alphaSlavePin,0X07);
               endTransfer();
            }else{
              Serial.println("Setting a Low Gain");
              beginTransfer();
              initial[0] = SPI.transfer(alphaSlavePin,inputByte);
              delay(10);
              initial[1] = SPI.transfer(alphaSlavePin,inputByte);
              delayMicroseconds(10);
              dataIn[0] = SPI.transfer(alphaSlavePin,0X06);
              endTransfer();
            }

           printBytesRead(initial,dataIn,size);


           highLowGainState dataOutput;
           dataOutput.valid          = comparator(validator, initial,2);
           dataOutput.highLow           = status;

         Serial.print("Validity: ");
         Serial.println(dataOutput.valid);
         Serial.print(dataOutput.highLow);    Serial.print(" ");
         printMintsEnd();

        return  dataOutput;
        }


struct DACandPowerStatus OPCN3Mints::readDACandPowerStatus() {
printMintsBegin();
      Serial.println("Reading DAC and Power Status");
      int  size = 6;
      byte inputByte =  0X13;
      byte validator[2] = {0X31,0XF3};
      byte dataIn[size];
      byte initial[2];


      beginTransfer();
      initial[0] = SPI.transfer(alphaSlavePin,inputByte);
      delay(10);
      initial[1] = SPI.transfer(alphaSlavePin,inputByte);
      for (int i = 0 ; i<size; i++)
          {
          delayMicroseconds(10);
          dataIn[i] = SPI.transfer(alphaSlavePin,inputByte);
          }

     endTransfer();
     printBytesRead(initial,dataIn,size);


   DACandPowerStatus dataOutput;
   memcpy(&dataOutput, &dataIn, sizeof(dataOutput));
   dataOutput.valid  = comparator(validator, initial,2);

   Serial.print("Validity: ");
   Serial.println(dataOutput.valid);
   Serial.print(dataOutput.fanOn);    Serial.print(" ");
   Serial.print(dataOutput.laserDACOn);  Serial.print(" ");
   Serial.print(dataOutput.fanDACVal );  Serial.print(" ");
   Serial.print(dataOutput.laserDACVal);  Serial.print(" ");
   Serial.print(dataOutput.laserSwitch );  Serial.print(" ");
   Serial.print(dataOutput.gainAndAutoGainToggleSetting);  Serial.print(" ");
   printMintsEnd();

     return dataOutput;
  }


struct informationString OPCN3Mints::readInformationString() {
printMintsBegin();
        Serial.println("Reading Information String");
        int  size = 60;
        byte inputByte =  0X3F;
        byte validator[2] = {0X31,0XF3};
        byte dataIn[size];
        byte initial[2];
        String info = "";
        beginTransfer();
        initial[0] = SPI.transfer(alphaSlavePin,inputByte);
        delay(10);
        initial[1] = SPI.transfer(alphaSlavePin,inputByte);
        for (int i = 0 ; i<size; i++)
            {
            delayMicroseconds(10);
            dataIn[i] = SPI.transfer(alphaSlavePin,inputByte);
            }

       endTransfer();
       printBytesRead(initial,dataIn,size);

       for (int i = 0; i < 60; i++){
         info += String((char)dataIn[i]);
      }

     informationString dataOutput;
     dataOutput.valid        = comparator(validator, initial,2);
     dataOutput.information  = info;

     Serial.print("Validity: ");
     Serial.print(dataOutput.valid)      ;   Serial.println(" ");
     Serial.print(dataOutput.information);   Serial.print(" ");
     printMintsEnd();

    return dataOutput;
    }


struct serialNumber OPCN3Mints::readSerialNumber() {
printMintsBegin();
            Serial.println("Reading Serial Number");
            int  size = 60;
            byte inputByte =  0X10;
            byte validator[2] = {0X31,0XF3};
            byte dataIn[size];
            byte initial[2];
            String info = "";
            beginTransfer();
            initial[0] = SPI.transfer(alphaSlavePin,inputByte);
            delay(10);
            initial[1] = SPI.transfer(alphaSlavePin,inputByte);
            for (int i = 0 ; i<size; i++)
                {
                delayMicroseconds(10);
                dataIn[i] = SPI.transfer(alphaSlavePin,inputByte);
                }

           endTransfer();
           printBytesRead(initial,dataIn,size);

           for (int i = 0; i < size; i++){
             info += String((char)dataIn[i]);
          }

           serialNumber dataOutput;
           dataOutput.valid   = comparator(validator, initial,2);
           dataOutput.serial  = info;
          //

         Serial.print("Validity: ");
         Serial.print(dataOutput.valid) ;  Serial.println(" ");
         Serial.print(dataOutput.serial);  Serial.print(" ");
         printMintsEnd();

return dataOutput;

}




struct firmwareVersion OPCN3Mints::readFirmwareVersion() {
printMintsBegin();
            Serial.println("Reading Firmaware Version");
            int  size = 2;
            byte inputByte =  0X12;
            byte validator[2] = {0X31,0XF3};
            byte dataIn[size];
            byte initial[2];
            String info = "";
            beginTransfer();
            initial[0] = SPI.transfer(alphaSlavePin,inputByte);
            delay(10);
            initial[1] = SPI.transfer(alphaSlavePin,inputByte);
            for (int i = 0 ; i<size; i++)
                {
                delayMicroseconds(10);
                dataIn[i] = SPI.transfer(alphaSlavePin,inputByte);
                }

           endTransfer();
           printBytesRead(initial,dataIn,size);


           firmwareVersion dataOutput;

            memcpy(&dataOutput, &dataIn, sizeof(dataOutput));
            dataOutput.valid  = comparator(validator, initial,2);

         Serial.print("Validity: ");
         Serial.print(dataOutput.valid)  ; Serial.println(" ");
         Serial.print(dataOutput.major);   Serial.print(" ");
         Serial.print(dataOutput.minor);   Serial.print(" ");
         printMintsEnd();

return  dataOutput;

}



struct configurationVariables OPCN3Mints::readConfigurationVariables() {
printMintsBegin();
  Serial.println("Reading Configuration Variables");
  int  size = 163;
  byte inputByte =  0X3C;
  byte validator[2] = {0X31,0XF3};
  byte dataIn[size];
  byte initial[2];
  String info = "";
  beginTransfer();
  initial[0] = SPI.transfer(alphaSlavePin,inputByte);
  delay(10);
  initial[1] = SPI.transfer(alphaSlavePin,inputByte);
  for (int i = 0 ; i<size; i++)
    {
        delayMicroseconds(10);
        dataIn[i] = SPI.transfer(alphaSlavePin,inputByte);
    }

  endTransfer();
  printBytesRead(initial,dataIn,size);

 configurationVariables dataOutput;

 memcpy(&dataOutput, &dataIn, sizeof(dataOutput));
 dataOutput.valid  = comparator(validator, initial,2);

 Serial.print("Validity: ");
 Serial.println(dataOutput.valid);
 Serial.println("Bin Boundries ADC");
 Serial.print(dataOutput.binBoundriesADC0);Serial.print(" ");
 Serial.print(dataOutput.binBoundriesADC1);Serial.print(" ");
 Serial.print(dataOutput.binBoundriesADC2);Serial.print(" ");
 Serial.print(dataOutput.binBoundriesADC3);Serial.print(" ");
 Serial.print(dataOutput.binBoundriesADC4);Serial.print(" ");
 Serial.print(dataOutput.binBoundriesADC5);Serial.print(" ");
 Serial.print(dataOutput.binBoundriesADC6);Serial.print(" ");
 Serial.print(dataOutput.binBoundriesADC7);Serial.print(" ");
 Serial.print(dataOutput.binBoundriesADC8);Serial.print(" ");
 Serial.print(dataOutput.binBoundriesADC9);Serial.println(" ");
 Serial.print(dataOutput.binBoundriesADC10);Serial.print(" ");
 Serial.print(dataOutput.binBoundriesADC11);Serial.print(" ");
 Serial.print(dataOutput.binBoundriesADC12);Serial.print(" ");
 Serial.print(dataOutput.binBoundriesADC13);Serial.print(" ");
 Serial.print(dataOutput.binBoundriesADC14);Serial.print(" ");
 Serial.print(dataOutput.binBoundriesADC15);Serial.print(" ");
 Serial.print(dataOutput.binBoundriesADC16);Serial.print(" ");
 Serial.print(dataOutput.binBoundriesADC17);Serial.print(" ");
 Serial.print(dataOutput.binBoundriesADC18);Serial.print(" ");
 Serial.print(dataOutput.binBoundriesADC19);Serial.println(" ");
 Serial.print(dataOutput.binBoundriesADC20);Serial.print(" ");
 Serial.print(dataOutput.binBoundriesADC21);Serial.print(" ");
 Serial.print(dataOutput.binBoundriesADC22);Serial.print(" ");
 Serial.print(dataOutput.binBoundriesADC23);Serial.print(" ");
 Serial.print(dataOutput.binBoundriesADC24);Serial.println(" ");

Serial.println("-------------------------------------------------");
Serial.println("Bin Boundries Diametors");
       Serial.print(dataOutput.binBoundriesDiametor0);Serial.print(" ");
       Serial.print(dataOutput.binBoundriesDiametor1);Serial.print(" ");
       Serial.print(dataOutput.binBoundriesDiametor2);Serial.print(" ");
       Serial.print(dataOutput.binBoundriesDiametor3);Serial.print(" ");
       Serial.print(dataOutput.binBoundriesDiametor4);Serial.print(" ");
       Serial.print(dataOutput.binBoundriesDiametor5);Serial.print(" ");
       Serial.print(dataOutput.binBoundriesDiametor6);Serial.print(" ");
       Serial.print(dataOutput.binBoundriesDiametor7);Serial.print(" ");
       Serial.print(dataOutput.binBoundriesDiametor8);Serial.print(" ");
       Serial.print(dataOutput.binBoundriesDiametor9);Serial.println(" ");
       Serial.print(dataOutput.binBoundriesDiametor10);Serial.print(" ");
       Serial.print(dataOutput.binBoundriesDiametor11);Serial.print(" ");
       Serial.print(dataOutput.binBoundriesDiametor12);Serial.print(" ");
       Serial.print(dataOutput.binBoundriesDiametor13);Serial.print(" ");
       Serial.print(dataOutput.binBoundriesDiametor14);Serial.print(" ");
       Serial.print(dataOutput.binBoundriesDiametor15);Serial.print(" ");
       Serial.print(dataOutput.binBoundriesDiametor16);Serial.print(" ");
       Serial.print(dataOutput.binBoundriesDiametor17);Serial.print(" ");
       Serial.print(dataOutput.binBoundriesDiametor18);Serial.print(" ");
       Serial.print(dataOutput.binBoundriesDiametor19);Serial.println(" ");
       Serial.print(dataOutput.binBoundriesDiametor20);Serial.print(" ");
       Serial.print(dataOutput.binBoundriesDiametor21);Serial.print(" ");
       Serial.print(dataOutput.binBoundriesDiametor22);Serial.print(" ");
       Serial.print(dataOutput.binBoundriesDiametor23);Serial.print(" ");
       Serial.print(dataOutput.binBoundriesDiametor24);Serial.println(" ");

Serial.println("-------------------------------------------------");
Serial.println("Bin Weights");
       Serial.print(dataOutput.binWeightings0);Serial.print(" ");
       Serial.print(dataOutput.binWeightings1);Serial.print(" ");
       Serial.print(dataOutput.binWeightings2);Serial.print(" ");
       Serial.print(dataOutput.binWeightings3);Serial.print(" ");
       Serial.print(dataOutput.binWeightings4);Serial.print(" ");
       Serial.print(dataOutput.binWeightings5);Serial.print(" ");
       Serial.print(dataOutput.binWeightings6);Serial.print(" ");
       Serial.print(dataOutput.binWeightings7);Serial.print(" ");
       Serial.print(dataOutput.binWeightings8);Serial.print(" ");
       Serial.print(dataOutput.binWeightings9);Serial.println(" ");
       Serial.print(dataOutput.binWeightings10);Serial.print(" ");
       Serial.print(dataOutput.binWeightings11);Serial.print(" ");
       Serial.print(dataOutput.binWeightings12);Serial.print(" ");
       Serial.print(dataOutput.binWeightings13);Serial.print(" ");
       Serial.print(dataOutput.binWeightings14);Serial.print(" ");
       Serial.print(dataOutput.binWeightings15);Serial.print(" ");
       Serial.print(dataOutput.binWeightings16);Serial.print(" ");
       Serial.print(dataOutput.binWeightings17);Serial.print(" ");
       Serial.print(dataOutput.binWeightings18);Serial.print(" ");
       Serial.print(dataOutput.binWeightings19);Serial.println(" ");
       Serial.print(dataOutput.binWeightings20);Serial.print(" ");
       Serial.print(dataOutput.binWeightings21);Serial.print(" ");
       Serial.print(dataOutput.binWeightings22);Serial.print(" ");
       Serial.print(dataOutput.binWeightings23);Serial.println(" ");
Serial.println("-------------------------------------------------");
Serial.println("PM Diametors");
       Serial.print(dataOutput.pmDiametorA);Serial.print(" ");
       Serial.print(dataOutput.pmDiametorB);Serial.print(" ");
       Serial.print(dataOutput.pmDiametorC);Serial.println(" ");
Serial.println("-------------------------------------------------");
Serial.println("PM MSLNS");
       Serial.print(dataOutput.maximumTimeOfFlight);Serial.print(" ");
       Serial.print(dataOutput.AMSamplingIntervalCount);Serial.print(" ");
       Serial.print(dataOutput.AMIdleIntervalCount);Serial.print(" ");
       Serial.print(dataOutput.AMMaxDataArraysInFile);Serial.print(" ");
       Serial.print(dataOutput.AMOnlySavePMData);Serial.print(" ");
       Serial.print(dataOutput.AMFanOnInIdle);Serial.print(" ");

printMintsEnd();

return  dataOutput;

}


struct histogramData OPCN3Mints::readHistogramData() {
  printMintsBegin();
  Serial.println("Reading Histogram Data ");
  int  size = 86;
  byte inputByte =  0X30;
  byte validator[2] = {0X31,0XF3};
  byte dataIn[size];
  byte initial[2];
  String info = "";
  beginTransfer();
  initial[0] = SPI.transfer(alphaSlavePin,inputByte);
  delay(10);
  initial[1] = SPI.transfer(alphaSlavePin,inputByte);
  for (int i = 0 ; i<size; i++)
    {
        delayMicroseconds(10);
        dataIn[i] = SPI.transfer(alphaSlavePin,inputByte);
    }

  endTransfer();
  printBytesRead(initial,dataIn,size);

 histogramData dataOutput;

 memcpy(&dataOutput, &dataIn, sizeof(dataOutput));
 dataOutput.valid  = comparator(validator, initial,2);

 Serial.print("Validity: ");
 Serial.println(dataOutput.valid);
 Serial.println("Bin Counts");
 Serial.print(dataOutput.binCount0);Serial.print(" ");
 Serial.print(dataOutput.binCount1);Serial.print(" ");
 Serial.print(dataOutput.binCount2);Serial.print(" ");
 Serial.print(dataOutput.binCount3);Serial.print(" ");
 Serial.print(dataOutput.binCount4);Serial.print(" ");
 Serial.print(dataOutput.binCount5);Serial.print(" ");
 Serial.print(dataOutput.binCount6);Serial.print(" ");
 Serial.print(dataOutput.binCount7);Serial.print(" ");
 Serial.print(dataOutput.binCount8);Serial.print(" ");
 Serial.print(dataOutput.binCount9);Serial.println(" ");
 Serial.print(dataOutput.binCount10);Serial.print(" ");
 Serial.print(dataOutput.binCount11);Serial.print(" ");
 Serial.print(dataOutput.binCount12);Serial.print(" ");
 Serial.print(dataOutput.binCount13);Serial.print(" ");
 Serial.print(dataOutput.binCount14);Serial.print(" ");
 Serial.print(dataOutput.binCount15);Serial.print(" ");
 Serial.print(dataOutput.binCount16);Serial.print(" ");
 Serial.print(dataOutput.binCount17);Serial.print(" ");
 Serial.print(dataOutput.binCount18);Serial.print(" ");
 Serial.print(dataOutput.binCount19);Serial.println(" ");
 Serial.print(dataOutput.binCount20);Serial.print(" ");
 Serial.print(dataOutput.binCount21);Serial.print(" ");
 Serial.print(dataOutput.binCount22);Serial.print(" ");
 Serial.print(dataOutput.binCount23);Serial.println(" ");

Serial.println("-------------------------------------------------");
Serial.println("Time To Cross");
 Serial.print(dataOutput.bin1TimeToCross);Serial.print(" ");
 Serial.print(dataOutput.bin3TimeToCross);Serial.print(" ");
 Serial.print(dataOutput.bin5TimeToCross);Serial.print(" ");
 Serial.print(dataOutput.bin7TimeToCross);Serial.println(" ");

 Serial.println("-------------------------------------------------");
 Serial.println("Sampling Period");
 Serial.println(dataOutput.samplingPeriod);
 Serial.println("-------------------------------------------------");
 Serial.println("Sample Flow Rate");
 Serial.println(dataOutput.sampleFlowRate);
 Serial.println("-------------------------------------------------");
 Serial.println("Temperature");
 Serial.println(dataOutput.temperature );
 Serial.println("-------------------------------------------------");
 Serial.println("Humidity");
 Serial.println(dataOutput.humidity );
 Serial.println("-------------------------------------------------");
 Serial.println("pm1");
 Serial.println(dataOutput.pm1);
 Serial.println("-------------------------------------------------");
 Serial.println("pm2.5");
 Serial.println(dataOutput.pm2_5);
 Serial.println("-------------------------------------------------");
 Serial.println("pm10");
 Serial.println(dataOutput.pm10);
 Serial.println("-------------------------------------------------");

 Serial.println("-------------------------------------------------");
 Serial.println("MSLNS");

  Serial.print(dataOutput.rejectCountGlitch);Serial.print(" ");
  Serial.print(dataOutput.rejectCountLongTOF);Serial.print(" ");
  Serial.print(dataOutput.rejectCountRatio);Serial.print(" ");
  Serial.print(dataOutput.rejectCountOutOfRange);Serial.print(" ");
  Serial.print(dataOutput.fanRevCount);Serial.print(" ");
  Serial.print(dataOutput.laserStatus);Serial.print(" ");
  Serial.print(dataOutput.checkSum);Serial.print(" ");

printMintsEnd();

return  dataOutput;

}


struct pmData OPCN3Mints::readPMData() {
  printMintsBegin();
  Serial.println("Reading Histogram Data ");
  int  size = 14;
  byte inputByte =  0X32;
  byte validator[2] = {0X31,0XF3};
  byte dataIn[size];
  byte initial[2];
  String info = "";
  beginTransfer();
  initial[0] = SPI.transfer(alphaSlavePin,inputByte);
  delay(10);
  initial[1] = SPI.transfer(alphaSlavePin,inputByte);
  for (int i = 0 ; i<size; i++)
    {
        delayMicroseconds(10);
        dataIn[i] = SPI.transfer(alphaSlavePin,inputByte);
    }

 endTransfer();
 printBytesRead(initial,dataIn,size);
 pmData dataOutput;

  memcpy(&dataOutput, &dataIn, sizeof(dataOutput));
  dataOutput.valid  = comparator(validator, initial,2);

 Serial.print("Validity: ");
 Serial.println(dataOutput.valid);
 Serial.println("-------------------------------------------------");
 Serial.println("pm1");
 Serial.println(dataOutput.pm1);
 Serial.println("-------------------------------------------------");
 Serial.println("pm2.5");
 Serial.println(dataOutput.pm2_5);
 Serial.println("-------------------------------------------------");
 Serial.println("pm10");
 Serial.println(dataOutput.pm10);
 Serial.println("-------------------------------------------------");
 Serial.println("CheckSum");
 Serial.print(dataOutput.checkSum);Serial.print(" ");

printMintsEnd();

return  dataOutput;

}

bool OPCN3Mints::resetHistogram() {

  printMintsBegin();
  Serial.println("Resetting Histogram");
  int  size = 14;
  byte inputByte =  0X32;
  byte validator[2] = {0X31,0XF3};
  byte dataIn[size];
  byte initial[2];
  beginTransfer();
  initial[0] = SPI.transfer(alphaSlavePin,inputByte);
  delay(10);
  initial[1] = SPI.transfer(alphaSlavePin,inputByte);
  for (int i = 0 ; i<size; i++)
    {
        delayMicroseconds(10);
        dataIn[i] = SPI.transfer(alphaSlavePin,inputByte);
    }

 endTransfer();
 printBytesRead(initial,dataIn,size);
 printMintsEnd();

return  comparator(validator, initial,2);

}

bool OPCN3Mints::comparator(byte arrayOne[], byte arrayTwo[], int size)
  {

    bool valid = true;

    for (int i = 0; i < size; i++){
         if (arrayOne[i] != arrayTwo[i])
           {
            valid = false;
           }
    }

    return valid;
  }



void OPCN3Mints::beginTransfer() {

   digitalWrite(alphaSlavePin, LOW);
  delay(1);
   }

void OPCN3Mints::endTransfer() {
delay(1);
   digitalWrite(alphaSlavePin, HIGH);

}


void OPCN3Mints::printBytesRead(byte initial[], byte dataIn[], int sizeOfArray)
{
    Serial.println("--------------------------------");
    Serial.println("Printing Initial Bytes----------");
    Serial.print(initial[0],HEX);
    Serial.print(" ");
    Serial.print(initial[1],HEX);
    Serial.println("");
    Serial.println("--------------------------------");
    Serial.println("Printing Byte Array-------------");

    for (int i = 0 ; i<sizeOfArray; i++)
        {
            Serial.print(dataIn[i],HEX);
            Serial.print(" ");
            if(i%10==9)
              {
              Serial.println("");
              }
        }

  Serial.println("");
  Serial.println("--------------------------------");
}



void OPCN3Mints::printMintsBegin(){
  Serial.println("");
  Serial.println("--------------------------------");
  Serial.println("-------------MINTS--------------");

}


  void OPCN3Mints::printMintsEnd(){
    Serial.println("");
    Serial.println("-------------MINTS--------------");
    Serial.println("--------------------------------");
}
