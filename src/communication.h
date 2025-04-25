#pragma once

/******************************************************************************
 * includes
 *****************************************************************************/
#include <main.h>
#include <string>

/******************************************************************************
 * function declarations
 *****************************************************************************/
void CommunicationSetup(const char *ssid, const char *pwd);
void CommunicationLoop();
void mqttClientConnected();
void message_received(char *topic, byte *payload, unsigned int length);
bool publishHeartbeat();
bool publishWeight(float value);

void (*onTareScale)();
void (*onCalibrateScale)();

/******************************************************************************
 * Workflow setups
 *****************************************************************************/
MqttClient *_mqttClass;
String mqtt_server;

// publish heartbeat every second
Timeout heartbeatTimeout(1000);

/******************************************************************************
 * MQTT topic declarations
 *****************************************************************************/
String client_id;
String topic_heartbeat;
String topic_weight;
String topic_tare;
String topic_calibrate;

/******************************************************************************
 * Main setup routine
 *****************************************************************************/
void CommunicationSetup(const char *ssid, const char *pwd) {

  // connect to WIFI
  setup_wifi_connection(ssid, pwd, client_id.c_str());

  // initialize MQTT client
  _mqttClass = new MqttClient(mqtt_server, 1883, client_id.c_str(),
                              message_received, mqttClientConnected);
}

/******************************************************************************
 * Main scale loop
 *****************************************************************************/
void CommunicationLoop() {
  // MQTT
  _mqttClass->VerifyMqttServerConnection();

  if (_mqttClass->Instance()->connected()) {
    // heartbeat
    if (heartbeatTimeout.Elapsed()) {
      publishHeartbeat();
    }
  }
}

/******************************************************************************
 * functions
 *****************************************************************************/
void mqttClientConnected() {
  _mqttClass->Instance()->subscribe(topic_tare.c_str());
  _mqttClass->Instance()->subscribe(topic_calibrate.c_str());
}

void message_received(char *topic, byte *payload, unsigned int length) {
  std::string payload1((const char *)payload, length);
  String payload2 = String((const char *)payload);

  ToSerial("Topic   : " + String(topic), "message_received -> ");
  ToSerial("Payload1: ", "message_received -> ", "", false);
  ToSerial(payload1.c_str());
  ToSerial("Payload2: " + payload2, "message_received -> ");

  if (String(topic) == topic_tare) {
    ToSerial("taring scale...", "message_received -> ", "", false);
    if (onTareScale) {
      onTareScale();
    }
    ToSerial("done", "message_received -> ");
  }

  if (String(topic) == topic_calibrate) {
    ToSerial("taring scale...", "message_received -> ", "", false);
    if (onCalibrateScale) {
      onCalibrateScale();
    }
    ToSerial("done", "message_received -> ");
  }
}

bool publishHeartbeat() {
  if (!_mqttClass->Instance()->connected()) {
    return false;
  }

  return _mqttClass->Instance()->publish(topic_heartbeat.c_str(), ".");
}

bool publishWeight(float value) {
  if (!_mqttClass->Instance()->connected()) {
    return false;
  }

  return _mqttClass->Instance()->publish(topic_weight.c_str(),
                                         String(value, 2).c_str());
}
