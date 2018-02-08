#include <Arduino.h>

#include "util/Timer.h"
#include "components/Pin.h"
#include "components/DHT11.h"
#include "components/Relay.h"

using namespace components;

DHT11 dht = DHT11(new Pin(5), 10);
Relay relay = Relay(new Pin(4));

void setup() {
    Serial.begin(9600); /* debug */
}

void loop() {
    if (dht.read()) {
        Serial.println(dht.getTemperature());
    }
//    delay(500);
//    relay.turnOn();
//    delay(500);
//    relay.turnOff();
}
