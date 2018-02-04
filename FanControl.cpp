#include <Arduino.h>

#include "util/Timer.h"
#include "components/Pin.h"
#include "components/DHT11.h"

using namespace components;

Pin dhtPin = Pin(5);
DHT11 dht = DHT11(dhtPin, 10);

void setup() {
    dht.setPin(dhtPin);
    Serial.begin(9600); /* debug */
}

void loop() {
    if (dht.read()) {
        Serial.println(dht.getTemperature());
    }
    delay(500);
}
