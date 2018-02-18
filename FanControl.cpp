// Do not remove the include below
#include "FanControl.h"
#include "components/Pin.h"
#include "components/DHT11.h"
#include "components/Relay.h"
#include "components/Fan.h"
#include "components/Button.h"
#include "util/EepromLogger.h"
#include "util/ValueWatcher.h"
#include "util/Timer.h" //TODO DEBUG ÄËß ËÎÃÎÂ
#include "Room.h"

using namespace components;
using namespace util;

uint8_t cntr = 0; //TODO DEBUG

DHT11 *dht = new DHT11(new Pin(5));
AnalogSensor *mqSensor = new AnalogSensor(new Pin(A6), 500);
AnalogSensor *lightSensor = new AnalogSensor(new Pin(A7), 900);
Relay *relay = new Relay(new Pin(4));
Fan *fan = new Fan(relay);
Room bathroom = Room();

Button btn1 = Button(new Pin(7)); //TODO DEBUG ÄËß ËÎÃÎÂ
Button btn2 = Button(new Pin(8)); //TODO DEBUG ÄËß ËÎÃÎÂ

Timer loggTimer = Timer();

EepromLogger *tempLogger;
EepromLogger *humidLogger;
EepromLogger *smokeLogger;

ValueWatcher *tempWatcher;
ValueWatcher *humidWatcher;
ValueWatcher *smokeWatcher;


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

	loggTimer.setSecondsInterval(1); //TODO DEBUG ÄËß ËÎÃÎÂ
}

void loop() {
    btn1.execute(); //TODO DEBUG ÄËß ËÎÃÎÂ
    btn2.execute(); //TODO DEBUG ÄËß ËÎÃÎÂ

	bathroom.serve();
	if (loggTimer.isTimeOut()) {
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
	    int16_t air = bathroom.getMqSensor()->read();
	    smokeWatcher->log(air);
	    Serial.print("air: ");
	    Serial.println(air);
	    Serial.println("-----------------------");  //TODO debug
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
        }
    }
}
