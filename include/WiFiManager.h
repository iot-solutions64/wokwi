#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include <HTTPClient.h>
#include "ICommunication.h"

class WiFiManager : public ICommunication {
private:
    const char* ssid;
    const char* password;
    String serverUrl;
    unsigned long lastReconnectAttempt;
    const unsigned long reconnectInterval;
    String rxBuffer; // buffer simple para recibir datos simulados

public:
    WiFiManager(const char* ssid, const char* password, const String& serverUrl);

    void begin() override;
    void handle() override;
    bool isConnected() override;
    String getAddress() override;

    bool sendData(const String& data) override;
    bool hasData() override;
    String receiveData() override;
};

#endif