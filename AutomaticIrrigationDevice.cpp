#include "AutomaticIrrigationDevice.h"
#include <Arduino.h>

AutomaticIrrigationDevice::AutomaticIrrigationDevice(int dht22Pin)
    : dht22sensor(dht22Pin, this) {}

void AutomaticIrrigationDevice::on(Event event) {
  /*
    if (event == Button::BUTTON_PRESSED_EVENT) {
        led.handle(Led::TOGGLE_LED_COMMAND);
    }
    */
}

void AutomaticIrrigationDevice::handle(Command command) {
  /*
    if (command == Led::TOGGLE_LED_COMMAND || 
        command == Led::TURN_ON_COMMAND || 
        command == Led::TURN_OFF_COMMAND) {
        Serial.printf("LED state: %d\n", led.getState());
    }
    */
}