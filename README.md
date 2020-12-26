# BLE Thermal Camera
Using BLE on a Particle Xenon to stream thermal camera data. The `docs` folder (named to work with GitHub pages) contains an example web page that connects to the Xenon via BLE and displays the thermal image. You can view this page at https://mbr4477.github.io/ble-thermal.

## Setup
1. Install AMG88xx library: `particle library add Adafruit_AMG88xx`
2. Change `TARGET` to your board in the Makefile
3. Compile and flash: `make`

## GATT Information
| Service ID | Characteristic ID | Data Format |
|-|-|-|
|0x18CC|0x2BCC|64-byte buffer. Each byte is the corresponding pixel value truncated to integer degrees Celsius.