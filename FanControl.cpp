// Do not remove the include below
#include "FanControl.h"
#include "components/Pin.h"
#include "components/DHT11.h"
#include "components/Relay.h"
#include "components/Fan.h"
#include "components/Button.h"
#include "util/EepromLogger.h"
#include "util/ValueWatcher.h"
#include "util/Timer.h" //TODO DEBUG ��� �����
#include "Room.h"

using namespace components;
using namespace util;

DHT11 *dht = new DHT11(new Pin(5));
AnalogSensor *mqSensor1 = new AnalogSensor(new Pin(A6), 500);
AnalogSensor *mqSensor2 = new AnalogSensor(new Pin(A4), 500);
AnalogSensor *lightSensor1 = new AnalogSensor(new Pin(A7), 900);
AnalogSensor *lightSensor2 = new AnalogSensor(new Pin(A5), 900);
Relay *relay1 = new Relay(new Pin(4));
Relay *relay2 = new Relay(new Pin(6));
Fan *fan1 = new Fan(relay1);
Fan *fan2 = new Fan(relay1);
Room bathroom;
Room privy;

Button btn1 = Button(new Pin(7)); //TODO DEBUG ��� �����
Button btn2 = Button(new Pin(8)); //TODO DEBUG ��� �����

Timer logTimer;

EepromLogger *tempLogger;
EepromLogger *humidLogger;
EepromLogger *smokeLogger1;
EepromLogger *smokeLogger2;

ValueWatcher *tempWatcher;
ValueWatcher *humidWatcher;
ValueWatcher *smokeWatcher1;
ValueWatcher *smokeWatcher2;

uint8_t temperature;
uint8_t humidity;
int16_t air1;
int16_t air2;

void setup() {
	bathroom.setLightSensor(lightSensor1);
	bathroom.setMqSensor(mqSensor1);
	dht->setHumidityThreshold(85);
	dht->setTemperatureThreshold(30);
	mqSensor1->setThreshold(250);
	bathroom.setDht(dht);
	bathroom.setFan(fan1);

	privy.setLightSensor(lightSensor2);
	privy.setMqSensor(mqSensor2);
	mqSensor2->setThreshold(250);
	privy.setFan(fan2);

	Serial.begin(9600);  //TODO debug
	tempLogger  = new EepromLogger(0, 100, 2, 1024);
	humidLogger = new EepromLogger(200, 100, 2, 1024);
	smokeLogger1 = new EepromLogger(400, 100, 2, 1024);
	smokeLogger2 = new EepromLogger(600, 100, 2, 1024);

	tempWatcher = new ValueWatcher(tempLogger, 60,
	        LogType::VALUE_FALLING);
	humidWatcher = new ValueWatcher(humidLogger, 60,
	        LogType::VALUE_FALLING);
	smokeWatcher1 = new ValueWatcher(smokeLogger1, 30,
	        LogType::VALUE_FALLING);
    smokeWatcher2 = new ValueWatcher(smokeLogger2, 30,
            LogType::VALUE_FALLING);

	logTimer.setSecondsInterval(1); //TODO DEBUG ��� �����
}

void loop() {
    btn1.execute(); //TODO DEBUG ��� �����
    btn2.execute(); //TODO DEBUG ��� �����

	bathroom.serve();
	privy.serve();
	if (logTimer.isTimeOut()) {
	    if (bathroom.getDht()->read()) {
	        humidity = bathroom.getDht()->getHumidity();
	        temperature = bathroom.getDht()->getTemperature();
//	        tempWatcher->log(temperature);
//	        humidWatcher->log(humidity);
	    } else {
	        Serial.println("DHT READING ERROR");
	    }
	    air1 = bathroom.getMqSensor()->read();
//	    smokeWatcher->log(air);
    }

	if (Serial.available()) {
	    char c = Serial.read();
        if (c == '1') {
            tempLogger->printLog();
            humidLogger->printLog();
            smokeLogger1->printLog();
            smokeLogger2->printLog();
        } else if (c == '2') {
            tempLogger->printChangesLog();
            humidLogger->printChangesLog();
            smokeLogger1->printChangesLog();
            smokeLogger2->printChangesLog();
        } else if (c == '3') {
            tempLogger->clearLog();
            humidLogger->clearLog();
            smokeLogger1->clearLog();
            smokeLogger2->clearLog();
        } else if (c == '4') {
            Serial.print("temp: ");  //TODO debug
            Serial.println(temperature);  //TODO debug
            Serial.print("humdty: ");  //TODO debug
            Serial.println(humidity);  //TODO debug
            Serial.print("air1: ");  //TODO debug
            Serial.println(air1);  //TODO debug
            Serial.print("air2: ");  //TODO debug
            Serial.println(air2);  //TODO debug
            Serial.println("-----------------------");  //TODO debug
        }
    }
}
