# HydroSmart: Sistema de riego automático

**Versión**: 0.1

**Autores**: Equipo de IoT Solutions

**Fecha**: Mayo 2025

## Descripción general

Este proyecto utiliza **Modest IoT Nano-framework (Edición en C++) v0.1** y lo implementa para el desarrollo del sistema de regado automático de **HydroSmart**. Este dispositivo simula un sistema de riego automático utilizando un sensor de humedad y temperatura DHT22 conectado a un ESP32, destacando el diseño orientado a objetos, dirigido por eventos e inspirado en el patrón CQRS del framework.  

Se utilizo la base encontrada en el ejemplo [`ToggableLedDevice Example (C++ Edition)`](https://github.com/upc-pre-202401-si572-sandbox-IoT/toggable-led-device-cpp-sandbox).

## Requisitos

- **Hardware**: Placa de desarrollo ESP32, sensor DHT22.
- **Software**: Arduino IDE con soporte para ESP32, o [Wokwi](https://wokwi.com) para simulación.
- **Dependencia**: Modest IoT Nano-framework (Edición en C++) v0.1.

## Estructura del proyecto

```
wokwi/
├── sketch.ino
├── AutomaticIrrigationDevice.h
├── AutomaticIrrigationDevice.cpp
├── DHT22Sensor.h
├── DHT22Sensor.cpp
├── diagram.json
├── class-diagram.md
├── user-stories.md
├── wokwi-project.txt
├── libraries.txt
├── (copiados desde ToggableLedDevice Example (C++ Edition) )
│   ├── ModestIoT.h
│   ├── EventHandler.h
│   ├── CommandHandler.h
│   ├── Sensor.h
│   ├── Sensor.cpp
│   ├── Actuator.h
│   ├── Actuator.cpp
│   ├── Device.h
│   └── Device.cpp
```