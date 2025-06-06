#include "ModestIoT.h"
#include "AutomaticIrrigationDevice.h"
#include "WiFiManager.h"

// Configuración WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const String edgeApiUrl = "https://localhost:3000/device/data";
// Intervalos de tiempo
unsigned long lastSensorUpdate = 0;
unsigned long lastDataSend = 0;
const unsigned long SENSOR_UPDATE_INTERVAL = 2000; // 2 segundos
const unsigned long SEND_DATA_INTERVAL = 30000;  // 30 segundos

WiFiManager wifiManager(ssid, password, edgeApiUrl);
AutomaticIrrigationDevice device(&wifiManager);

void setup() {
  Serial.begin(115200);
  Serial.println("Dispositivo de riego automático iniciado");

  // Inicializar WiFi
  wifiManager.begin();
}

void loop() {
  wifiManager.handle();  // Siempre mantener la conexión activa

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

  // Delay para evitar sobrecarga
  delay(50);
}