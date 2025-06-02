#ifndef LED_H
#define LED_H

#include "Actuator.h"
#include <Arduino.h>

class LedActuator : public Actuator {
private:
  bool state;
public:
  static const int TOGGLE_LED_COMMAND_ID = 0;
  static const int TURN_ON_COMMAND_ID = 1;
  static const int TURN_OFF_COMMAND_ID = 2;
  static const Command TOGGLE_LED_COMMAND;
  static const Command TURN_ON_COMMAND;
  static const Command TURN_OFF_COMMAND;

  LedActuator(int pin, bool initialState = false, CommandHandler* commandHandler = nullptr);
  void handle(Command command) override;
  bool getState() const;
  void setState(bool newState);
};

#endif