#pragma once

/******************************************************************************
 * includes
 *****************************************************************************/
#include <main.h>

/******************************************************************************
 * function declarations
 *****************************************************************************/
void WeighingSetup();
void WeighingLoop();
void tareScale();
void calibrateScale();

void (*doPublishWeight)(float weight);
void (*doPublishRawReading)(long reading);

/******************************************************************************
 * HX711 setup
 *
 * Info to calibrating the load cell:
 * https://github.com/bogde/HX711#how-to-calibrate-your-load-cell
 *****************************************************************************/
HX711 scale;

/******************************************************************************
 * Button setup
 *****************************************************************************/
InputButton btnCalibrate(CALIBRATE_BTN, calibrateScale, nullptr);
InputButton btnTare(TARE_BTN, tareScale, nullptr);

/******************************************************************************
 * Workflow setups
 *****************************************************************************/
// only allow next tare after 2000ms
Timeout tareTimeout(2000);

// calibrate mode switch
bool fCalibrateModeActive = false;

// Initial calibration value (200g calibration weight on load cell from DIPSE)
float floatCalibrationWeight;
float floatCalibrationValue;

/******************************************************************************
 * Main setup routine
 *****************************************************************************/
void WeighingSetup() {
  Serial.println("WeighingSetup() - enter");
  // Serial.println("\n\nHX711 Demo");

  Serial.println("Initializing the scale");

  // Initialize library with data output pin, clock input pin and gain factor.
  // Channel selection is made by passing the appropriate gain:
  // - With a gain factor of 64 or 128, channel A is selected
  // - With a gain factor of 32, channel B is selected
  // By omitting the gain factor parameter, the library
  // default "128" (Channel A) is used here.
  scale.begin(LOAD_CELL_DOUT_PIN, LOAD_CELL_SCK_PIN);

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read()); // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(
      scale.read_average(20)); // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(
      scale.get_value(5)); // print the average of 5 readings from the ADC minus
                           // the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(
      scale.get_units(5),
      1); // print the average of 5 readings from the ADC minus tare weight (not
          // set) divided by the SCALE parameter (not set yet)

  scale.set_scale(
      floatCalibrationValue); // this value is obtained by calibrating the scale
                              // with known weights; see the README for details
  scale.tare();               // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read()); // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(
      scale.read_average(20)); // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(
      scale.get_value(5)); // print the average of 5 readings from the ADC minus
                           // the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(
      scale.get_units(5),
      1); // print the average of 5 readings from the ADC minus tare weight,
          // divided by the SCALE parameter set with set_scale

  // Serial.println();
  Serial.println("WeighingSetup() - leave");
}

/******************************************************************************
 * Main scale loop
 *****************************************************************************/
void WeighingLoop() {
  long reading = 0;
  float weight = 0;
  char strMode[12];
  char strWeight[12];

  if (scale.is_ready()) {
    reading = scale.read();

    if (doPublishRawReading) {
      doPublishRawReading(reading);
    }

    if (fCalibrateModeActive) {
      String("Calibrating ").toCharArray(strMode, 12);
      weight = scale.get_units(5);

    } else {
      String("Weighing    ").toCharArray(strMode, 12);
      weight = scale.get_units(10);
    }

    String("             ").toCharArray(strWeight, 12);
    String(weight, 2).toCharArray(strWeight, 5);

    if (doPublishWeight) {
      doPublishWeight(weight);
    }

    Serial.print("HX711 reading: ");
    Serial.print(reading);
    Serial.print("\t");
    Serial.print("Weight: ");
    Serial.print(weight);
    Serial.print("\t");
    Serial.print(strMode);
    Serial.print("\t");
    Serial.print("Calibration Value: ");
    Serial.println(floatCalibrationValue);
  }

  // delay(1000);
  btnCalibrate.CheckButtonState(nullptr, nullptr);
  btnTare.CheckButtonState(nullptr, nullptr);
}

/******************************************************************************
 * functions
 *****************************************************************************/
void tareScale() {
  if (tareTimeout.Elapsed()) {
    scale.tare();
    Serial.println("Scale tared.");
  }
}

void calibrateScale() {
  if (fCalibrateModeActive) {
    floatCalibrationValue = scale.get_units(10) / floatCalibrationWeight;
    scale.set_scale(floatCalibrationValue);
    fCalibrateModeActive = false;
  } else {
    fCalibrateModeActive = true;

    while (!scale.is_ready()) {
      delay(100);
    }

    scale.set_scale();
    scale.tare();
  }
}
