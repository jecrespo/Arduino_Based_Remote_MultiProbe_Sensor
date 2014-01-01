Arduino_Based_Remote_MultiProbe_Sensor
======================================
Remote_MultiProbe_Sensor_V0

Purpose: MultiProbe remote sensor to measure any analog or digital signal like temperature, humidity, power consumption, voltage, external alarm,... everything you can imagine.
This example, is written for read temperature, humidity and power consumption, also is configured an external alarm reading for a voltage free contact.
On every loop probe data is collected and every 30 seconds data are saved in a database.

Version Control
Version 0 - Initial Version.

TODO LIST: N/A

HARDWARE
--------

Designed for ARDUINO ETHERNET R3 (http://arduino.cc/en/Main/ArduinoBoardEthernet)
Compiled with Arduino 1.0.5 (http://arduino.cc/en/Main/Software)
Microcontroller				ATmega328
Operating Voltage			5V
Digital I/O Pins				14 (of which 4 provide PWM output)
Analog Input Pins			6
DC Current per I/O Pin		40 mA
Flash Memory					32 KB (ATmega328) of which 0.5 KB used by bootloader
SRAM							2 KB (ATmega328)
EEPROM						1 KB (ATmega328)
Clock Speed					16 MHz
Embedded Ethernet Controller	W5100 TCP/IP 

ADDITIONAL HARDWARE
-------------------

One DHT22 temperature and humidity probe (http://www.adafruit.com/datasheets/DHT22.pdf)
An open-hardware energy monitoring Arduino compatible - emonTx Shield v1 (http://openenergymonitor.org/emon/emontxshield)
A Non-invasive clip-on CT current sensor (for AC current only) (http://shop.openenergymonitor.com/100a-max-clip-on-current-sensor-ct/)
AC-AC Power Supply Adapter for AC voltage sensor. Input 220 VAC - Output 9VAC

HARDWARE PINS USED/RESERVED
---------------------------
 
Arduino Pins reserved 	10 to 13 used for SPI (reserved for interfacing with the Ethernet module)
    										4 used for SD card (Slave Select)
      									2 Ethernet W5100 interrupt (when bridged)
                				Temperature & Humidity 	3 for DHT22 signal wire
                				External Alarm			    5 voltage free external alarm
                				Voltage sensor			    A0 (analog input)
                				Current sensor			    A1 (analog input)

LIBRARIES USED
--------------

SPI (Standard Library) - for communicating with devices using the Serial Peripheral Interface (SPI) Bus
Ethernet (Standard Library) - for connecting to the internet using Ethernet Module
MemoryFree - determine the amount of memory currently available (http://playground.arduino.cc/Code/AvailableMemory)
dht - class for measuring temperature and humidity with DHT11, DHT21 and DHT22 sensors (http://playground.arduino.cc/Main/DHTLib)
emonLib - Electricity monitoring library (https://github.com/openenergymonitor/EmonLib)
