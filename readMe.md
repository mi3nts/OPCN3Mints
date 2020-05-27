# OPCN3Mints

This library is written for the [Alphasense OPC-N3](http://www.alphasense.com/WEB1213/wp-content/uploads/2018/02/OPC-N3.pdf) air qualilty monitoring sensor. 

## Alphasense OPCN3
<img src="https://github.com/mi3nts/OPCN3Mints/blob/master/res/OPCN3.JPG?raw=true" height="300"/>
</br>


## Arduino Due
<img src="https://store-cdn.arduino.cc/usa/catalog/product/cache/1/image/520x330/604a3538c15e081937dbfbd20aa60aad/A/0/A000062_featured_2.jpg" height="300"/>
</br>

The Alphasense OPCN3 is an Optical Particle counter designed to measure and record air quality data. This implimetation is designed to read particulate mattaer data from the OPCN3 with an [Arduino Due](https://store.arduino.cc/usa/arduino-due). The library can be easilly modified to be used with any Arduino supported device with an SPI interface.

### Supported functions:
- begin() : 
- initialize();
- setFanDigitalPotShutdownState(bool status);
- setLaserDigitalPotShutdownState(bool status);
- setHighLowGainState(bool status);
- readDACandPowerStatus();
- readInformationString();
- readSerialNumber();
- readFirmwareVersion();
- readConfigurationVariables();
- readHistogramData() ;
- readPMData() ;
- resetHistogram();

## Repository structure
- **/examples** - An example sketch desiged to initiate and read alpha sensor data is included here.  
- **/src**      - Source files for the OPCN3Mints library is found here.


## On a Nano 

| Nano        | OPC | OPC Pin | Color  | Nano Pin |
|-------------|-----|---------|--------|----------|
| Vcc         | Vcc | 1       | Red    |5V        |
| Sck         | Sck | 2       | Yellow |D13       |
| MISO        | SDO | 3       | Green  |D12       |
| MOSI        | SDI | 4       | Blue   |D11       |
| Digital Pin | SS  | 5       | White  |D10       |
| Gnd         | GND | 6       | Black  |Gnd       |









