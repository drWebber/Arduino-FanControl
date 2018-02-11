#include <Arduino.h>

#include "components/Pin.h"
#include "components/DHT11.h"
#include "components/Relay.h"
#include "components/Fan.h"

using namespace components;

DHT11 *dht = new DHT11(new Pin(5));
AnalogSensor *mqSensor = new AnalogSensor(new Pin(A6), 300);
AnalogSensor *lightSensor = new AnalogSensor(new Pin(A7), 900);
Relay *relay = new Relay(new Pin(4));
Fan fan = Fan(relay);

void setup() {
    fan.setLightSensor(lightSensor);
    fan.setMqSensor(mqSensor);
    dht->setHumidityThreshold(70);
    dht->setTemperatureThreshold(27);
    fan.setDht(dht);
    Serial.begin(9600);  //TODO debug
}

void loop() {
    fan.serve();
    Serial.println("-----------------------");  //TODO debug
    delay(5000); //TODO debug
}
