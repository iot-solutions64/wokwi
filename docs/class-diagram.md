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

interface ICommunication {
    + begin()
    + handle()
    + isConnected()
    + getAddress()
    + sendData(data: string)
    + hasData()
    + receiveData()
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
    - dht: DHTesp
    + onEvent()
    + getHumidity()
    + getTemperature()
    + updateData()
}

class UltrasonicSensor {
    - triggerPin: int
    - echoPin: int
    - tankHeight: float
    - tankArea: float
    - currentVolume: float
    + onEvent()
    + getDistance()
    + getWaterHeigh()
    + getVolume()
    + updateData()
}

class LedActuator {
    - state: boolean
    + handleCommand()
    + turnOn()
    + turnOff()
}

class AutomaticIrrigationDevice {
    - dht22Sensor: DHT22Sensor
    - ledActuator: LedActuator
    - ultrasonicSensor: UltrasonicSensor
    - comm: ICommunication
    - calculateTankVolumePercent(float distanceCm)
    + onEvent()
    + handleCommand()
    + handleVolumeChange()
    + handleEnviromentalChange()
    + getLed()
    + getDHT()
    + getUltrasonic()
    + updateSensors()
    + sendSensorData()
}

class MQTTManager {
    - ssid: char*
    - password: char*
    - mqttServer: char*
    - mqttPort: uint16_t
    - mqttTopic: char*
    - rxBuffer: string
    - lastReconnectAttempt: long
    - reconnectInterval: long
    - reconnect()
    - setData(data: string)
    + begin()
    + handle()
    + isConnected()
    + getAddress()
    + sendData(data: string)
    + hasData()
    + receiveData()
}

' Relaciones de implementación de interfaces
EventHandler <|.. Sensor
CommandHandler <|.. Actuator
EventHandler <|.. Device
CommandHandler <|.. Device
ICommunication <|.. MQTTManager

' Relaciones de herencia
Sensor <|-- DHT22Sensor
Sensor <|-- UltrasonicSensor
Actuator <|-- LedActuator
Device <|-- AutomaticIrrigationDevice

' Relaciones de composición/agregación (dependencia)
AutomaticIrrigationDevice --> DHT22Sensor
AutomaticIrrigationDevice --> UltrasonicSensor
AutomaticIrrigationDevice --> LedActuator
AutomaticIrrigationDevice --> ICommunication

@enduml
```