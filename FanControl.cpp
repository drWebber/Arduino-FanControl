#include "FanControl.h"
#include "components/Pin.h"
#include "components/DHT11.h"
#include "components/Relay.h"
#include "components/Fan.h"
#include "components/Button.h"
#include "util/EepromLogger.h" //TODO DEBUG ��� �����
#include "util/ValueWatcher.h" //TODO DEBUG ��� �����
#include "util/Timer.h" //TODO DEBUG ��� �����
#include "Room.h"

using namespace components;
using namespace util;

DHT11 *dht = new DHT11(new Pin(5), 10);
AnalogSensor *mqSensor1 = new AnalogSensor(new Pin(A6), 500);
AnalogSensor *mqSensor2 = new AnalogSensor(new Pin(A4), 500);
AnalogSensor *lightSensor1 = new AnalogSensor(new Pin(A7), 900);
AnalogSensor *lightSensor2 = new AnalogSensor(new Pin(A5), 900);
Relay *relay1 = new Relay(new Pin(4));
Relay *relay2 = new Relay(new Pin(6));
Fan *fan1 = new Fan(relay1);
Fan *fan2 = new Fan(relay2);
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

bool erased = false; //TODO LOGGER

void setup() {
    Serial.begin(9600);  //TODO debug

    dht->setHumidityThreshold(85);
    dht->setTemperatureThreshold(30);

    mqSensor1->setThreshold(250);
    mqSensor2->setThreshold(250);

	bathroom.setLightSensor(lightSensor1);
	bathroom.setMqSensor(mqSensor1);
    bathroom.setDht(dht);
	bathroom.setFan(fan1);
    bathroom.setFanControlButton(&btn2);

	privy.setLightSensor(lightSensor2);
	privy.setMqSensor(mqSensor2);
	privy.setFan(fan2);
    privy.setFanControlButton(&btn2);

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
    bathroom.getDht()->execute();

    bathroom.serve();
    privy.serve();

    if (btn1.isHolded() && !erased) {
        erased = true;
        tempLogger->clearLog();
        humidLogger->clearLog();
        smokeLogger1->clearLog();
        smokeLogger2->clearLog();
    }

    //TODO DELETE LOGGER BELOW
    if (btn1.getPreviousState()) {
        if (logTimer.isTimeOut()) {
            digitalWrite(13, HIGH);
            if (!bathroom.getDht()->isError()) {
                humidity = bathroom.getDht()->getHumidity();
                temperature = bathroom.getDht()->getTemperature();
                air1 = bathroom.getMqSensor()->read();
                air2 = bathroom.getMqSensor()->read();
            } else {
                Serial.println("DHT READING ERROR");
            }
            erased = false;
            tempWatcher->log(temperature);
            humidWatcher->log(humidity);
            smokeWatcher1->log(air1);
            smokeWatcher2->log(air2);
        } else {
            digitalWrite(13, LOW);
        }
    }

    if (!btn1.getPreviousState()) {
        digitalWrite(13, LOW);
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
            Serial.print("temp: ");
            Serial.println(temperature);
            Serial.print("humdty: ");
            Serial.println(humidity);
            Serial.print("air1: ");
            Serial.println(air1);
            Serial.print("air2: ");
            Serial.println(air2);
            Serial.println("-----------------------");
        }
    }
}
