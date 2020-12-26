/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "/Users/matthew/Dropbox/ble-thermal/src/ble-thermal.ino"
/*
 * Project ble-thermal
 * Description:
 * Author:
 * Date:
 * BLE code adapted from 
 * https://docs.particle.io/tutorials/device-os/bluetooth-le/#body-temperature-thermometer
 */
#include "Particle.h"
#include <Adafruit_AMG88xx.h>

// Use Xenon in offline mode (no cloud)
void setup();
void loop();
#line 13 "/Users/matthew/Dropbox/ble-thermal/src/ble-thermal.ino"
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(MANUAL);

// Thermal camera sensor
Adafruit_AMG88xx thermalCam;

// Custom BLE service
BleUuid thermalService(0x18CC);

// Custom BLE thermal characteristic
BleCharacteristic thermalDataCharacteristic(
    "therm",
    BleCharacteristicProperty::NOTIFY,
    // Custom id
    BleUuid(0x2BCC),
    thermalService);

void setup()
{
  // Setup logging
  Serial.begin();

  // Setup up the sensor
  bool status = thermalCam.begin();
  if (status) {
    Serial.println("AMG88xx ok");
  }

  // Setup the BLE
  BLE.on();
  BLE.addCharacteristic(thermalDataCharacteristic);

  BleAdvertisingData advData;
  advData.appendServiceUUID(thermalService);
  BLE.advertise(&advData);
}

void loop()
{

}