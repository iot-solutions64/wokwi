# Diagrama de clases

```
@startuml Diagrama de clases de HydroSmart

' Interfaces
interface EventHandler {
    + onEvent()
}

interface CommandHandler {
    + handleCommand()
}

' Clases abstractas
abstract class Sensor {
    # pin: int
    # handler: EventHandler
    + onEvent()
    + setHandler()
}

abstract class Actuator {
    # pin: int
    # handler: CommandHandler
    + handleCommand()
    + setHandler()
}

abstract class Device {
    + onEvent()
    + handleCommand()
}

' Clases concretas
class DHT22Sensor {
    - humidity: float
    - temperature: float
    + onEvent()
    + getHumidity()
    + getTemperature()

}

class IrrigationActuator {
    - status: boolean
    + handleCommand()
    + turnOn()
    + turnOff()
}

class AutomaticIrrigationDevice {
    - dht22sensor: DHT22Sensor
    - irrigationactuator: IrrigationActuator
    + onEvent()
    + handleCommand()
}

' Relaciones de Implentacion de interfaces
EventHandler <|.. Sensor
CommandHandler <|.. Actuator
EventHandler <|.. Device
CommandHandler <|.. Device

' Relaciones de Herencia
Sensor <|-- DHT22Sensor
Actuator <|-- IrrigationActuator
Device <|-- AutomaticIrrigationDevice

' Relaciones de Composición/Agregación (dependencia)
AutomaticIrrigationDevice --> DHT22Sensor
AutomaticIrrigationDevice --> IrrigationActuator
@enduml
```