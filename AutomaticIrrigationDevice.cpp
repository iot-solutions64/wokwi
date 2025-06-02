#include "AutomaticIrrigationDevice.h"
#include <Arduino.h>

AutomaticIrrigationDevice::AutomaticIrrigationDevice(
  int dht22Pin, int ledPin, int trigPin, int echoPin
) : dht22Sensor(dht22Pin, this),
    ledActuator(ledPin, false, this),
    ultrasonicSensor(trigPin, echoPin, TANK_HEIGHT_CM, TANK_AREA_CM2, this) {}

void AutomaticIrrigationDevice::on(Event event) {
  if (event == UltrasonicSensor::VOLUME_CHANGED_EVENT) {
    handleVolumeChange();
  } else if (event == DHT22Sensor::TEMPERATURE_CHANGED_EVENT || event == DHT22Sensor::HUMIDITY_CHANGED_EVENT) {
    handleEnvironmentalChange();
  }
}

void AutomaticIrrigationDevice::handle(Command command) {
  if (command == LedActuator::TOGGLE_LED_COMMAND || 
      command == LedActuator::TURN_ON_COMMAND || 
      command == LedActuator::TURN_OFF_COMMAND) {
    Serial.printf("LED state: %d\n", ledActuator.getState());
  }
}

void AutomaticIrrigationDevice::handleVolumeChange() {
  float volume = ultrasonicSensor.getVolume();
  float volumePercent = (volume / TANK_TOTAL_VOLUME_LITERS) * 100.0;

  Serial.printf("Volumen actualizado: %.2fL (%.1f%%)\n", volume, volumePercent);

  if (volumePercent <= TANK_MIN_VOLUME_THRESHOLD) {
    if (ledActuator.getState()) {
      ledActuator.handle(LedActuator::TURN_OFF_COMMAND);
      Serial.println("Nivel crítico de agua. Riego cancelado.");
    } else {
      Serial.println("Nivel crítico de agua. Riego ya está desactivado.");
    }
  }
}

void AutomaticIrrigationDevice::handleEnvironmentalChange() {
  float temperature = dht22Sensor.getTemperature();
  float humidity = dht22Sensor.getHumidity();
  float volume = ultrasonicSensor.getVolume();
  float volumePercent = (volume / TANK_TOTAL_VOLUME_LITERS) * 100.0;

  Serial.printf("Lectura ambiental -> Temp: %.2f°C | Hum: %.2f%% | Vol: %.2fL (%.1f%%)\n",
                temperature, humidity, volume, volumePercent);

  if (volumePercent <= TANK_MIN_VOLUME_THRESHOLD) {
    Serial.println("Nivel de agua crítico. Se omite evaluación ambiental.");
    return;
  }

  if (temperature >= TEMPERATURE_THRESHOLD || humidity <= HUMIDITY_THRESHOLD) {
    if (!ledActuator.getState()) {
      ledActuator.handle(LedActuator::TURN_ON_COMMAND);
      Serial.println("Condición anómala: Activando riego.");
    }
  } else {
    if (ledActuator.getState()) {
      ledActuator.handle(LedActuator::TURN_OFF_COMMAND);
      Serial.println("Condición normal: Riego desactivado.");
    }
  }
}

DHT22Sensor& AutomaticIrrigationDevice::getDHT() {
  return dht22Sensor;
}

LedActuator& AutomaticIrrigationDevice::getLed() {
  return ledActuator;
}

UltrasonicSensor& AutomaticIrrigationDevice::getUltrasonic() {
  return ultrasonicSensor;
}