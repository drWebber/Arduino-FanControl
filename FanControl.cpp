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
AnalogSensor *mqSensor = new AnalogSensor(new Pin(A6), 500);
AnalogSensor *lightSensor = new AnalogSensor(new Pin(A7), 900);
Relay *relay = new Relay(new Pin(4));
Fan *fan = new Fan(relay);
Room bathroom;

Button btn1 = Button(new Pin(7)); //TODO DEBUG ��� �����
Button btn2 = Button(new Pin(8)); //TODO DEBUG ��� �����

Timer logTimer;

EepromLogger *tempLogger;
EepromLogger *humidLogger;
EepromLogger *smokeLogger;

ValueWatcher *tempWatcher;
ValueWatcher *humidWatcher;
ValueWatcher *smokeWatcher;

uint8_t temperature;
uint8_t humidity;
int16_t air;

void setup() {
	bathroom.setLightSensor(lightSensor);
	bathroom.setMqSensor(mqSensor);
	dht->setHumidityThreshold(85);
	dht->setTemperatureThreshold(27);
	bathroom.setDht(dht);
	bathroom.setFan(fan);

	Serial.begin(9600);  //TODO debug
	tempLogger  = new EepromLogger(0, 100, 2, 1024);
	humidLogger = new EepromLogger(200, 100, 2, 1024);
	smokeLogger = new EepromLogger(400, 100, 2, 1024);

	tempWatcher = new ValueWatcher(tempLogger, 60,
	        LogType::VALUE_FALLING);
	humidWatcher = new ValueWatcher(humidLogger, 60,
	        LogType::VALUE_FALLING);
	smokeWatcher = new ValueWatcher(smokeLogger, 30,
	        LogType::VALUE_FALLING);

	logTimer.setSecondsInterval(1); //TODO DEBUG ��� �����
}

void loop() {
    btn1.execute(); //TODO DEBUG ��� �����
    btn2.execute(); //TODO DEBUG ��� �����

	bathroom.serve();
	if (logTimer.isTimeOut()) {
	    if (bathroom.getDht()->read()) {
	        humidity = bathroom.getDht()->getHumidity();
	        temperature = bathroom.getDht()->getTemperature();
//	        tempWatcher->log(temperature);
//	        humidWatcher->log(humidity);
	    } else {
	        Serial.println("DHT READING ERROR");
	    }
	    air = bathroom.getMqSensor()->read();
//	    smokeWatcher->log(air);
    }

	if (Serial.available()) {
	    int8_t s = Serial.read();
        if (s == 0x31) { // 1
            tempLogger->printLog();
            humidLogger->printLog();
            smokeLogger->printLog();
        } else if (s == 0x32) { //2
            tempLogger->printChangesLog();
            humidLogger->printChangesLog();
            smokeLogger->printChangesLog();
        } else if (s == 0x33) { //3
            tempLogger->clearLog();
            humidLogger->clearLog();
            smokeLogger->clearLog();
        } else if (s == 0x34) { //4
            Serial.print("temp: ");  //TODO debug
            Serial.println(temperature);  //TODO debug
            Serial.print("humdty: ");  //TODO debug
            Serial.println(humidity);  //TODO debug
            Serial.print("air: ");  //TODO debug
            Serial.println(air);  //TODO debug
            Serial.println("-----------------------");  //TODO debug
        }
    }
}
