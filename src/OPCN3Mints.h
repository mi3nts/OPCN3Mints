#ifndef OPCN3_MINTS_H
#define OPCN3_MINTS_H

#include <Arduino.h>
#include <SPI.h>

class OPCN3Mints
{
private:
    // attributes
    uint8_t alphaSlavePin;

public:

  OPCN3Mints(uint8_t chipSelect);
  // Alpha Sensor Functions
  void begin();
  bool initialize();
  void beginTransfer();
  void endTransfer();
  void printBytesRead(byte initial[],byte dataIn[], int sizeOfArray) ;
  struct fanDigitalPotShutdownState setFanDigitalPotShutdownState(bool status);
  struct laserDigitalPotShutdownState setLaserDigitalPotShutdownState(bool status);
  struct highLowGainState setHighLowGainState(bool status);
  struct DACandPowerStatus readDACandPowerStatus();
  struct informationString readInformationString();
  struct serialNumber readSerialNumber();
  struct firmwareVersion readFirmwareVersion();
  struct configurationVariables readConfigurationVariables();
  struct histogramData readHistogramData() ;
  struct pmData readPMData() ;
  bool resetHistogram();
  void printMintsBegin();
  void printMintsEnd();
  bool comparator(byte arrayOne[], byte arraTwo[], int size);
};



    struct fanDigitalPotShutdownState
    {
    bool fanOn;
    bool valid;
    };

    struct laserDigitalPotShutdownState
    {
    bool laserOn;
    bool valid;
    };


    struct highLowGainState
    {
    bool highLow;
    bool valid;
    };

    struct DACandPowerStatus
    {
    uint8_t fanOn;
    uint8_t laserDACOn;
    uint8_t fanDACVal;
    uint8_t laserDACVal;
    uint8_t laserSwitch;
    uint8_t gainAndAutoGainToggleSetting;
    bool valid;
    };

    struct informationString
    {
    String information;
    bool valid;
    };

    struct serialNumber
    {
    String serial;
    bool valid;
    };

    struct firmwareVersion
    {
    uint8_t major;
    uint8_t minor;
    bool valid;
    };

    struct configurationVariables
    {

    uint16_t binBoundriesADC0;
    uint16_t binBoundriesADC1;
    uint16_t binBoundriesADC2;
    uint16_t binBoundriesADC3;
    uint16_t binBoundriesADC4;
    uint16_t binBoundriesADC5;
    uint16_t binBoundriesADC6;
    uint16_t binBoundriesADC7;
    uint16_t binBoundriesADC8;
    uint16_t binBoundriesADC9;
    uint16_t binBoundriesADC10;
    uint16_t binBoundriesADC11;
    uint16_t binBoundriesADC12;
    uint16_t binBoundriesADC13;
    uint16_t binBoundriesADC14;
    uint16_t binBoundriesADC15;
    uint16_t binBoundriesADC16;
    uint16_t binBoundriesADC17;
    uint16_t binBoundriesADC18;
    uint16_t binBoundriesADC19;
    uint16_t binBoundriesADC20;
    uint16_t binBoundriesADC21;
    uint16_t binBoundriesADC22;
    uint16_t binBoundriesADC23;
    uint16_t binBoundriesADC24;


    uint16_t binBoundriesDiametor0;
    uint16_t binBoundriesDiametor1;
    uint16_t binBoundriesDiametor2;
    uint16_t binBoundriesDiametor3;
    uint16_t binBoundriesDiametor4;
    uint16_t binBoundriesDiametor5;
    uint16_t binBoundriesDiametor6;
    uint16_t binBoundriesDiametor7;
    uint16_t binBoundriesDiametor8;
    uint16_t binBoundriesDiametor9;
    uint16_t binBoundriesDiametor10;
    uint16_t binBoundriesDiametor11;
    uint16_t binBoundriesDiametor12;
    uint16_t binBoundriesDiametor13;
    uint16_t binBoundriesDiametor14;
    uint16_t binBoundriesDiametor15;
    uint16_t binBoundriesDiametor16;
    uint16_t binBoundriesDiametor17;
    uint16_t binBoundriesDiametor18;
    uint16_t binBoundriesDiametor19;
    uint16_t binBoundriesDiametor20;
    uint16_t binBoundriesDiametor21;
    uint16_t binBoundriesDiametor22;
    uint16_t binBoundriesDiametor23;
    uint16_t binBoundriesDiametor24;

    uint16_t binWeightings0;
    uint16_t binWeightings1;
    uint16_t binWeightings2;
    uint16_t binWeightings3;
    uint16_t binWeightings4;
    uint16_t binWeightings5;
    uint16_t binWeightings6;
    uint16_t binWeightings7;
    uint16_t binWeightings8;
    uint16_t binWeightings9;
    uint16_t binWeightings10;
    uint16_t binWeightings11;
    uint16_t binWeightings12;
    uint16_t binWeightings13;
    uint16_t binWeightings14;
    uint16_t binWeightings15;
    uint16_t binWeightings16;
    uint16_t binWeightings17;
    uint16_t binWeightings18;
    uint16_t binWeightings19;
    uint16_t binWeightings20;
    uint16_t binWeightings21;
    uint16_t binWeightings22;
    uint16_t binWeightings23;

    uint16_t pmDiametorA;
    uint16_t pmDiametorB;
    uint16_t pmDiametorC;

    uint16_t maximumTimeOfFlight;
    uint16_t AMSamplingIntervalCount;
    uint16_t AMIdleIntervalCount;
    uint16_t AMMaxDataArraysInFile;

    uint8_t AMOnlySavePMData;
    uint8_t AMFanOnInIdle;

    bool valid;
    };


    struct histogramData
    {


    uint16_t binCount0  ;
    uint16_t binCount1  ;
    uint16_t binCount2  ;
    uint16_t binCount3  ;
    uint16_t binCount4  ;
    uint16_t binCount5  ;
    uint16_t binCount6  ;
    uint16_t binCount7  ;
    uint16_t binCount8  ;
    uint16_t binCount9  ;
    uint16_t binCount10 ;
    uint16_t binCount11 ;
    uint16_t binCount12 ;
    uint16_t binCount13 ;
    uint16_t binCount14 ;
    uint16_t binCount15 ;
    uint16_t binCount16 ;
    uint16_t binCount17 ;
    uint16_t binCount18 ;
    uint16_t binCount19 ;
    uint16_t binCount20 ;
    uint16_t binCount21 ;
    uint16_t binCount22 ;
    uint16_t binCount23 ;

    uint8_t bin1TimeToCross  ;
    uint8_t bin3TimeToCross  ;
    uint8_t bin5TimeToCross  ;
    uint8_t bin7TimeToCross  ;

    uint16_t samplingPeriod ;
    uint16_t sampleFlowRate ;
    uint16_t temperature    ;
    uint16_t humidity       ;

    float pm1     ;
    float pm2_5   ;
    float pm10   ;

    uint16_t rejectCountGlitch       ;
    uint16_t rejectCountLongTOF      ;
    uint16_t rejectCountRatio        ;
    uint16_t rejectCountOutOfRange   ;
    uint16_t fanRevCount             ;
    uint16_t laserStatus             ;
    uint16_t checkSum                ;
    bool valid;
    };

    struct pmData
    {
      float pm1    ;
      float pm2_5  ;
      float pm10   ;
      uint16_t checkSum ;
      bool valid;

  };

#endif
