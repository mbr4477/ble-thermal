/*
 * Project ble-thermal
 * Description:
 * Author:
 * Date:
 * BLE code adapted from 
 * https://docs.particle.io/tutorials/device-os/bluetooth-le/#body-temperature-thermometer
 */
#include "Particle.h"
#include "Adafruit_AMG88xx.h"

// Use Xenon in offline mode (no cloud)
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
  } else {
    while(1);
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
  float thermalData[64];
  thermalCam.readPixels(thermalData);
  uint8_t msg[64];
  for (uint8_t i = 0; i < 64; i++)
  {
    msg[i] = (uint8_t) thermalData[i];
  }
  thermalDataCharacteristic.setValue(msg, 64);
  delay(100);
}