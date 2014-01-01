////////// LIBRARIES //////////
//
#include <SPI.h>
#include <Ethernet.h>
#include <MemoryFree.h>
#include <dht.h>
#include "EmonLib.h"
//
////////// DEFINITIONS //////////
//
#define SEND_TIME 30000
#define DHT_PIN 5
#define VOLTAGE_PIN 0
#define CURRENT_PIN 1
#define ALARM_PIN 4
//
////////// VARIABLES //////////
//
dht dhtSensor;
float temperature;
float humidity;
int result;
boolean alarm = 0;
EnergyMonitor emon1;
float realPower1;
float apparentPower1;
float powerFactor1;
float supplyVoltage1;
float Irms1;
extern volatile unsigned long timer0_overflow_count;
//
////////// ETHERNET CONFIGURATION //////////
//
static uint8_t mac[]     = {0x90, 0xA2, 0xDd, 0xAB, 0x99, 0xFF};
static uint8_t ip[]      = {192,168,0,2};
static uint8_t subnet[]  = {255,255,255,0};
static uint8_t gateway[]  = {192,168,0,1};   
static uint8_t server[]  = {192,168,0,1};
//
////////// SETUP //////////
void setup() {
    Serial.begin(9600);
    Serial.println("\n---------------------------\n-------------------- Start:Remote_MultiProbe_Sensor_V0 --------------------\n---------------------------");
    Serial.print("Free RAM: ");
    Serial.println(freeMemory());
	pinMode(ALARM_PIN,INPUT_PULLUP);
	result = dhtSensor.read22(DHT_PIN);
	switch (result) {
		case 0:
		  Serial.println("DHTLIB_OK");
		  temperature=dhtSensor.temperature;
		  humidity=dhtSensor.humidity;
		  break;
		case -1:
		  Serial.println(F("DHTLIB_ERROR_CHECKSUM"));
		  break;
		case -2:
		  Serial.println(F("DHTLIB_ERROR_TIMEOUT"));
		  break;
	}
	emon1.voltage(VOLTAGE_PIN, 211, 1.7);
	emon1.current(CURRENT_PIN, 63);
	Ethernet.begin(mac, ip, gateway, gateway, subnet);
}
//
////////// LOOP //////////
void loop() {
	Serial.println("--------- New Loop ---------");
	Serial.print(F("Free RAM: ");
	Serial.println(freeMemory());
	Serial.print("Time since last server update (seconds): ");
	Serial.println(timer0_overflow_count/1000);
	if (alarm != !digitalRead(ALARM_PIN)) {
	  alarm = !digitalRead(ALARM_PIN);
	  if (alarm) Serial.println("External alarm is ON");
	  else Serial.println("External alarm is OFF");
	  Send_Data();
	}  
	if (timer0_overflow_count > SEND_TIME){
		timer0_overflow_count = 0;
		result=dhtSensor.read22(DHT_PIN);
		if (result == 0){
			temperature	= dhtSensor.temperature;
			humidity = dhtSensor.humidity;
			Serial.print("temperature: ");
			Serial.println(temperature);
			Serial.print("humidity: ");
			Serial.println(humidity);
		}
		else {
			Serial.println("Read sensor Error!");
			temperature	=	-99;
			humidity 	= 	-99;
		}
		emon1.calcVI(20,2000);
		realPower1       = emon1.realPower;
		apparentPower1   = emon1.apparentPower;
		powerFactor1     = emon1.powerFactor;
		supplyVoltage1   = emon1.Vrms;
		Irms1            = emon1.Irms;
		Serial.print("Voltage: ");
		Serial.println(supplyVoltage1);
		Serial.print("Current: ");
		Serial.println(Irms1);
		Serial.print("Power Factor: ");
		Serial.println(powerFactor1);
		Serial.print("Real Power: ");
		Serial.println(realPower1);
		Serial.print("Apparent Power: ");
		Serial.println(apparentPower1);
		Send_Data();	
	}
}
//
////////// FUNCTIONS //////////
void Send_Data() {
	EthernetClient client;
	Serial.println("Sending data...");
	if (client.connect(servidor,80))    {
		Serial.println("Connected...");
		client.println("POST /saveData.php HTTP/1.1");
		client.println("Host: Arduino");
		client.println("Connection: Close");
		client.println("Content-Type: application/x-www-form-urlencoded");
		client.println("Content-Length: 550");
		client.println("");
		client.print("alarm=");
		client.print(alarm);
		client.print("&temperature=");
		client.print(temperature);
		client.print("&humidity=");
		client.print(humidity);
		client.print("&current=");
		client.print(Irms1);
		client.print("&voltage=");
		client.print(supplyVoltage1);
		client.print("&pf=");
		client.print(powerFactor1);
		client.println("");
		client.stop();
		client.flush();
		Serial.println("Data Saved!");
	}
	else Serial.println("Connection Error!");
}
