#include "DHT22Sensor.h"
#include <Arduino.h>

DHT22Sensor::DHT22Sensor(int pin, EventHandler* eventHandler)
    : Sensor(pin, eventHandler) {
    pinMode(pin, INPUT);
}