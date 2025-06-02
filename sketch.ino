#include "ModestIoT.h"
#include "AutomaticIrrigationDevice.h"

AutomaticIrrigationDevice device;

void setup() {
  Serial.begin(115200);
  Serial.println("Dispositivo de riego automático iniciado");
}

void loop() {
  device.getDHT().updateData();
  device.getUltrasonic().updateData();
  delay(2000);
}
