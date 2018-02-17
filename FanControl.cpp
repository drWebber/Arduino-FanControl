// Do not remove the include below
#include "FanControl.h"
#include "components/Pin.h"
#include "components/DHT11.h"
#include "components/Relay.h"
#include "components/Fan.h"
#include "util/EepromLogger.h"
#include "util/ValueWatcher.h"
#include "Room.h"

using namespace components;
using namespace util;

DHT11 *dht = new DHT11(new Pin(5));
AnalogSensor *mqSensor = new AnalogSensor(new Pin(A6), 300);
AnalogSensor *lightSensor = new AnalogSensor(new Pin(A7), 900);
Relay *relay = new Relay(new Pin(4));
Fan *fan = new Fan(relay);
Room bathroom = Room();

EepromLogger *tempLogger;
EepromLogger *humidLogger;
EepromLogger *smokeLogger;

ValueWatcher *tempWatcher;
ValueWatcher *humidWatcher;
ValueWatcher *smokeWatcher;


void setup() {
	bathroom.setLightSensor(lightSensor);
	bathroom.setMqSensor(mqSensor);
	dht->setHumidityThreshold(70);
	dht->setTemperatureThreshold(27);
	bathroom.setDht(dht);
	bathroom.setFan(fan);

	Serial.begin(9600);  //TODO debug
	tempLogger  = new EepromLogger(0, 200);
	humidLogger = new EepromLogger(200, 200);
	smokeLogger = new EepromLogger(400, 200);

	tempWatcher = new ValueWatcher(tempLogger, 30,
	        LogType::VALUE_FALLING);
	humidWatcher = new ValueWatcher(humidLogger, 30,
	        LogType::VALUE_FALLING);
	smokeWatcher = new ValueWatcher(smokeLogger, 30,
	        LogType::VALUE_FALLING);
}

void loop() {
	bathroom.serve();

	delay(250);
	if (bathroom.getDht()->read()) {
	    uint8_t humidity = bathroom.getDht()->getHumidity();
	    uint8_t temperature = bathroom.getDht()->getTemperature();
	    Serial.print("temp: ");
	    Serial.println(temperature);
        Serial.print("humdty: ");
        Serial.println(humidity);
        tempWatcher->log(temperature);
        humidWatcher->log(humidity);
	} else {
        Serial.println("DHT READING ERROR");
	}
	smokeWatcher->log(bathroom.getMqSensor()->read());
	Serial.println("-----------------------");  //TODO debug

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
        }
    }

	delay(1000); //TODO debug
}
