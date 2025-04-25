#pragma once

/******************************************************************************
 * defines
 ******************************************************************************/
#if defined(ARDUINO_ARCH_ESP8266)

#define LOAD_CELL_DOUT_PIN D6 /* GPIO 12 */
#define LOAD_CELL_SCK_PIN D5  /* GPIO 14 */
#define TARE_BTN D1           /* GPIO  5 */
#define CALIBRATE_BTN D2      /* GPIO  4 */

#elif defined(ESP32)

#define LOAD_CELL_DOUT_PIN 19 /* GPIO 19 */
#define LOAD_CELL_SCK_PIN 18  /* GPIO 18 */
#define TARE_BTN 5            /* GPIO  5 */
#define CALIBRATE_BTN 4       /* GPIO  4 */

#else
#error Architecture unrecognized by this code.
#endif

/******************************************************************************
** includes
******************************************************************************/
#include <Arduino.h>
#include <DebugOutput.h>
#include <HX711.h>
#include <InputButton.h>
#include <MqttClient.h>
#include <Timeout.h>
#include <WifiConnection.h>
#include <communication.h>
#include <string>
#include <weighing.h>

/******************************************************************************
** predefinitions
******************************************************************************/
String prefix_main_h = "main.h -> ";
String ssid = "";
String pwd = "";

void TareScale();
void CalibrateScale();

void PublishWeight(float weight);

/******************************************************************************
** instance definitions
******************************************************************************/
DebugOutput *debugOut;

/******************************************************************************
** setup config
******************************************************************************/
void setupConfig(DebugOutput *debugOut) {
// get secrets
#ifdef WLAN_SSID
  debugOut->ToDebug("WLAN_SSID: " + String(WLAN_SSID), prefix_main_h);
  ssid = WLAN_SSID;
#endif
#ifdef WLAN_PASSWORD
  debugOut->ToDebug("WLAN_PASSWORD: " + String(WLAN_PASSWORD), prefix_main_h);
  pwd = WLAN_PASSWORD;
#endif
#ifdef MQTT_BROKER
  debugOut->ToDebug("MQTT_BROKER: " + String(MQTT_BROKER), prefix_main_h);
  mqtt_server = MQTT_BROKER;
#endif
#ifdef CLIENT_ID
  debugOut->ToDebug("CLIENT_ID: " + String(CLIENT_ID), prefix_main_h);
  client_id = CLIENT_ID;
#endif

  topic_heartbeat = client_id + "/heartbeat";
  topic_weight = client_id + "/weight";
  topic_tare = client_id + "/tare";
  topic_calibrate = client_id + "/calibrate";
}