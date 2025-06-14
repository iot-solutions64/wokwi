#include "AutomaticIrrigationDevice.h"

AutomaticIrrigationDevice::AutomaticIrrigationDevice(
  ICommunication* communication,
  int dht22Pin,
  int ledPin,
  int trigPin,
  int echoPin
) : dht22Sensor(dht22Pin, this),
    ledActuator(ledPin, false, this),
    ultrasonicSensor(trigPin, echoPin, TANK_HEIGHT_CM, TANK_AREA_CM2, this),
    comm(communication)
{}

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
      Serial.print("Nivel crítico de agua. Riego cancelado.");
    } else {
      Serial.print("Nivel crítico de agua. Riego ya está desactivado.");
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
    Serial.print("Nivel de agua crítico. Se cancela el riego.");
    return;
  }
  bool hasInvalidLocalConditions = (temperature >= temperatureThreshold || humidity <= humidityThreshold);
  int edgeResult = validateIrrigationConditions();
  bool shouldIrrigate = false;

  switch (edgeResult) {
    case 0: // Edge dice no regar
      Serial.print("Edge API indica no regar.");
      shouldIrrigate = false;
      break;
    case 1: // Edge dice regar
      shouldIrrigate = true;
      break;
    case 2: // Error en el endpoint
    default:
      Serial.print("Edge API no disponible. Usando solo condiciones locales.");
      shouldIrrigate = hasInvalidLocalConditions;
      break;
  }
  if (shouldIrrigate) {
    if (!ledActuator.getState()) {
      ledActuator.handle(LedActuator::TURN_ON_COMMAND);
      Serial.print("Condición anómala: Activando riego.");
    }
  } else {
    if (ledActuator.getState()) {
      ledActuator.handle(LedActuator::TURN_OFF_COMMAND);
      Serial.print("Condición normal: Riego desactivado.");
    }
  }
}

void AutomaticIrrigationDevice::updateSensors() {
  dht22Sensor.updateData();
  ultrasonicSensor.updateData();
}

void AutomaticIrrigationDevice::sendSensorData() {
  if (comm && comm->isConnected()) {
    float temp = dht22Sensor.getTemperature();
    float hum = dht22Sensor.getHumidity();
    float volume = ultrasonicSensor.getVolume();

    JsonDocument data;
    data["temperature"] = temp;
    data["humidity"] = hum;
    data["volume"] = volume;
    String resource;
    serializeJson(data, resource);
  }
}

void AutomaticIrrigationDevice::getThresholdData() {
  if (comm && comm->isConnected()) {
    if (!comm) return;

    String response = comm->receiveData(IRRIGATION_THRESHOLDS_ENDPOINT);
    if (response.isEmpty()) {
      Serial.print("Error recuperando datos de los limites para validacion local.");
      return;
    }

    JsonDocument data;
    DeserializationError error = deserializeJson(data, response);
    if (error) {
        Serial.print("Error parsing JSON: ");
        Serial.println(error.c_str());
        return;
    }
    // Set thresholds
    temperatureThreshold = data["temperature_max"];
    humidityThreshold = data["humidity_min"];

    Serial.print("Valores de validacion local actualizados.");
    return;
  }
}

int AutomaticIrrigationDevice::validateIrrigationConditions() {
    if (!comm) return 2;

    String response = comm->receiveData(IRRIGATION_STATUS_ENDPOINT);
    if (response.isEmpty()) return 2;

    JsonDocument data;
    DeserializationError error = deserializeJson(data, response);
    if (error) {
        Serial.print("Error parsing JSON: ");
        Serial.println(error.c_str());
        return 2;
    }

    bool shouldIrrigate = data["active"];
    Serial.printf("Respuesta Edge API para riego: %s\n", shouldIrrigate ? "ACTIVAR" : "NO ACTIVAR");
    return shouldIrrigate ? 1 : 0;
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