#include "MQTTManager.h"

MQTTManager::MQTTManager(const char* ssid, const char* password, const char* mqttServer, uint16_t mqttPort, const char* mqttTopic)
    : ssid(ssid), password(password), mqttServer(mqttServer), mqttPort(mqttPort), mqttTopic(mqttTopic),
      mqttClient(wifiClient), rxBuffer(""), lastReconnectAttempt(0), reconnectInterval(10000) {}

void MQTTManager::begin() {
    WiFi.begin(ssid, password);
    Serial.print("Conectando a WiFi");
    mqttClient.setServer(mqttServer, mqttPort);
    randomSeed(analogRead(0)); // Inicializa la semilla para random()
}

void MQTTManager::handle() {
    if (WiFi.status() != WL_CONNECTED) {
        unsigned long now = millis();
        if (now - lastReconnectAttempt > reconnectInterval) {
            Serial.println("\nIntentando reconectar a WiFi...");
            WiFi.disconnect();
            WiFi.begin(ssid, password);
            lastReconnectAttempt = now;
        }
        Serial.print(".");
        return;
    }
    if (!mqttClient.connected()) {
        reconnect();
    }
    mqttClient.loop();
}

void MQTTManager::reconnect() {
    // Usar un nombre de cliente único para evitar colisiones en el broker público
    String clientId = "ESP32Client_";
    clientId += String(random(0xffff), HEX); // Sufijo aleatorio
    while (!mqttClient.connected()) {
        Serial.print("Intentando conectar al broker MQTT...");
        if (mqttClient.connect(clientId.c_str())) {
            Serial.println("Conectado a MQTT!");
            mqttClient.subscribe(mqttTopic); // Suscribirse si se requiere
        } else {
            Serial.print("Fallo, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" intentando de nuevo en 5 segundos");
            delay(5000);
        }
    }
}

bool MQTTManager::isConnected() {
    return WiFi.status() == WL_CONNECTED && mqttClient.connected();
}

String MQTTManager::getAddress() {
    if (isConnected()) {
        return WiFi.localIP().toString();
    }
    return "0.0.0.0";
}

bool MQTTManager::sendData(const String& data) {
    if (!isConnected()) {
        Serial.println("No conectado a WiFi/MQTT. No se pueden enviar datos.");
        return false;
    }
    bool result = mqttClient.publish(mqttTopic, data.c_str());
    if (result) {
        Serial.println("Datos publicados en MQTT: " + data);
    } else {
        Serial.println("Error publicando en MQTT");
    }
    return result;
}

bool MQTTManager::hasData() {
    return rxBuffer.length() > 0;
}

String MQTTManager::receiveData() {
    String data = rxBuffer;
    rxBuffer = "";
    return data;
}

String MQTTManager::receiveData(const String& url) {
    if (!isConnected()) {
        Serial.println("No hay conexión para consultar el endpoint");
        return "";
    }

    HTTPClient http;
    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    Serial.println("Consultando endpoint...");
    int httpCode = http.GET();

    if (httpCode == 200) {
        String payload = http.getString();
        http.end();
        return payload;
    } else {
        Serial.printf("Error consultando endpoint: %d\n", httpCode);
        http.end();
        return "";
    }
}