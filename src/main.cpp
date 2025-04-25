#include <main.h>

String prefix_main_cpp = "main.cpp -> ";

void setup() {
  delay(10);
  Serial.begin(115200);

  debugOut = new DebugOutput(true, true);
  debugOut->ToDebug("setup() - enter", prefix_main_cpp);

  setupConfig(debugOut);

  WeighingSetup();
  CommunicationSetup(ssid.c_str(), pwd.c_str());

  onTareScale = TareScale;
  onCalibrateScale = CalibrateScale;
  doPublishWeight = PublishWeight;

  debugOut->ToDebug("setup() - leave", prefix_main_cpp);
}

void loop() {
  WeighingLoop();
  CommunicationLoop();
}

void TareScale() { tareScale(); }

void CalibrateScale() { calibrateScale(); }

void PublishWeight(float weight) { publishWeight(weight); }