#include <Arduino.h>

#include "components/Pin.h"
#include "components/DHT11.h"
#include "components/Relay.h"
#include "components/Fan.h"
#include "Room.h"

using namespace components;

DHT11 *dht = new DHT11(new Pin(5));
AnalogSensor *mqSensor = new AnalogSensor(new Pin(A6), 300);
AnalogSensor *lightSensor = new AnalogSensor(new Pin(A7), 900);
Relay *relay = new Relay(new Pin(4));
Fan *fan = new Fan(relay);
Room bathroom = Room();

void setup() {
    bathroom.setLightSensor(lightSensor);
    bathroom.setMqSensor(mqSensor);
    dht->setHumidityThreshold(70);
    dht->setTemperatureThreshold(27);
    bathroom.setDht(dht);
    bathroom.setFan(fan);
    Serial.begin(9600);  //TODO debug
}

void loop() {
    bathroom.serve();
    Serial.println("-----------------------");  //TODO debug
    delay(5000); //TODO debug
}
