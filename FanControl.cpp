#include <Arduino.h>
#include "component/Sensor.h"
#include "component/Relay.h"
#include "util/Timer.h"

Relay relay;
Timer timer;
Sensor photoSensor;

void setup() {
    relay.setDataPin(13, OUTPUT);
    photoSensor.setDataPin(7, INPUT);
    photoSensor.setEventThreshold(900);
    timer.setSecondsInterval(5);
    Serial.begin(9600); /* debug */
}

void loop() {
    if (photoSensor.isEvent()) {
        relay.swithcOn();
    } else {
        relay.swithcOff();
    }
}
