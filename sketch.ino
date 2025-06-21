#include "ModestIoT.h"
#include "AutomaticIrrigationDevice.h"
#include "MQTTManager.h"

// Configuración WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqttServer = "test.mosquitto.org";
const uint16_t mqttPort = 1883;
const char* mqttTopic = "iot/irrigation/data/iot-solutions64";
// Intervalos de tiempo
unsigned long lastSensorUpdate = 0;
unsigned long lastDataSend = 0;
unsigned long lastGetThreshold = 0;
const unsigned long SENSOR_UPDATE_INTERVAL = 1000; // 1 segundos
const unsigned long SEND_DATA_INTERVAL = 15000;  // 15 segundos
const unsigned long GET_THRESHOLD_INTERVAL = 60000; // 1 minuto

MQTTManager mqttManager(ssid, password, mqttServer, mqttPort, mqttTopic);
AutomaticIrrigationDevice device(&mqttManager);

void setup() {
  Serial.begin(115200);
  Serial.println("Dispositivo de riego automático iniciado");

  // Inicializar WiFi
  mqttManager.begin();
}

void loop() {
  mqttManager.handle();  // Siempre mantener la conexión activa

  unsigned long currentTime = millis();

  // Actualizar sensores cada X segundos
  if (currentTime - lastSensorUpdate >= SENSOR_UPDATE_INTERVAL) {
    lastSensorUpdate = currentTime;
    device.updateSensors();
  }

  // Enviar datos cada X segundos
  if (currentTime - lastDataSend >= SEND_DATA_INTERVAL) {
    lastDataSend = currentTime;
    device.sendSensorData();
  }

  // Obtener limites de temperatura y humedad
  if (currentTime - lastDataSend >= GET_THRESHOLD_INTERVAL) {
    lastGetThreshold = currentTime;
    device.getThresholdData();
  }

  // Delay para evitar sobrecarga
  delay(50);
}
