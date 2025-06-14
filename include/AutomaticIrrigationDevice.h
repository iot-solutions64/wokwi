#ifndef AUTOMATIC_IRRIGATION_DEVICE_H
#define AUTOMATIC_IRRIGATION_DEVICE_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>

#include "Device.h"
#include "DHT22Sensor.h"
#include "LedActuator.h"
#include "UltrasonicSensor.h"
#include "ICommunication.h"

class AutomaticIrrigationDevice : public Device {
private:
  DHT22Sensor dht22Sensor;
  LedActuator ledActuator;
  UltrasonicSensor ultrasonicSensor;
  ICommunication* comm; // Comunicación (WiFiManager, MQTTManager u otra)

  float temperatureThreshold = 30.0; // °C
  float humidityThreshold = 25.0;    // %
  static constexpr float TANK_MIN_VOLUME_THRESHOLD = 5.0; // %
  static constexpr float TANK_HEIGHT_CM = 100.0;       // cm
  static constexpr float TANK_AREA_CM2 = 1000.0;       // cm²
  static constexpr float TANK_TOTAL_VOLUME_LITERS = (TANK_HEIGHT_CM * TANK_AREA_CM2) / 1000.0;
  static constexpr const char* IRRIGATION_STATUS_ENDPOINT = "https://endpoint.com/irrigation/status";
  static constexpr const char* IRRIGATION_THRESHOLDS_ENDPOINT = "https://endpoint.com/irrigation/thresholds";
  float calculateTankVolumePercent(float distanceCm);
  int validateIrrigationConditions();

public:
  static const int DHT22_PIN = 18;
  static const int LED_PIN = 19;
  static const int TRIGGER_PIN = 14;
  static const int ECHO_PIN = 12;

  AutomaticIrrigationDevice(
    ICommunication* communication,
    int dht22Pin = DHT22_PIN,
    int ledPin = LED_PIN,
    int trigPin = TRIGGER_PIN,
    int echoPin = ECHO_PIN
  );

  void on(Event event) override;
  void handle(Command command) override;
  void handleVolumeChange();
  void handleEnvironmentalChange();

  void updateSensors();
  void sendSensorData();
  void getThresholdData();

  DHT22Sensor& getDHT();
  LedActuator& getLed();
  UltrasonicSensor& getUltrasonic();
};

#endif
