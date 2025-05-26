#ifndef DHT22SENSOR_H
#define DHT22SENSOR_H

#include "Sensor.h"

class DHT22Sensor : public Sensor {
private:
    float humidity;
    float temperature;
public:
    DHT22Sensor(int pin, EventHandler* eventHandler = nullptr);
};

#endif