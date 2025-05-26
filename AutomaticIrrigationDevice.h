#ifndef TOGGABLE_LED_DEVICE_H
#define TOGGABLE_LED_DEVICE_H

#include "Device.h"
#include "DHT22Sensor.h"

class AutomaticIrrigationDevice : public Device {
private:
    DHT22Sensor dht22sensor;

public:
    static const int DHT22_PIN = 26;

    AutomaticIrrigationDevice(int dht22Pin = DHT22_PIN);
    void on(Event event) override;
    void handle(Command command) override;
};

#endif