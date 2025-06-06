#include "WiFiManager.h"

WiFiManager::WiFiManager(const char* ssid, const char* password, const String& serverUrl)
    : ssid(ssid),
      password(password),
      serverUrl(serverUrl),
      lastReconnectAttempt(0),
      reconnectInterval(10000),
      rxBuffer("")
{}

void WiFiManager::begin() {
    WiFi.begin(ssid, password);
    Serial.print("Conectando a WiFi");
}

void WiFiManager::handle() {
    if (WiFi.status() != WL_CONNECTED) {
        unsigned long now = millis();
        if (now - lastReconnectAttempt > reconnectInterval) {
            Serial.println("\nIntentando reconectar a WiFi...");
            WiFi.disconnect();
            WiFi.begin(ssid, password);
            lastReconnectAttempt = now;
        }
        Serial.print(".");
    }
}

bool WiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

String WiFiManager::getAddress() {
    if (isConnected()) {
        return WiFi.localIP().toString();
    }
    return "0.0.0.0";
}

bool WiFiManager::sendData(const String& data) {
    if (!isConnected()) {
        Serial.println("No conectado a WiFi. No se pueden enviar datos.");
        return false;
    }

    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(data);
    if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("Respuesta Edge API: " + response);

        // Guardamos la respuesta en rxBuffer para simular recepción
        rxBuffer = response;

        http.end();
        return true;
    } else {
        Serial.println("Error enviando datos: " + String(httpResponseCode));
        http.end();
        return false;
    }
}

bool WiFiManager::hasData() {
    return rxBuffer.length() > 0;
}

String WiFiManager::receiveData() {
    String data = rxBuffer;
    rxBuffer = ""; // limpiamos buffer después de leer
    return data;
}
