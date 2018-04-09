/*
    Simplified example for the Adafruit LIS3DH accelerometer
    breakout board (https://www.adafruit.com/products/2809)
    based on Kevin Townsend's sample code.

    Note: this code sets the accelerometer to 2G (aka 2x the acceleration
    due to gravity). The accelerometer has a 14-bit range, or -8193 to 8192.
    So at 1G, when the full force of gravity is on one of the axes,
    the reading should be around 4095 for that axis (or -4096, depending on
    the orientation).

    modified 24 Nov 2015
    by Tom Igoe
*/

#include <Wire.h>
#include <Adafruit_LIS3DH.h>

Adafruit_LIS3DH accelerometer = Adafruit_LIS3DH();

void setup() {
  Serial.begin(9600);
  while (!Serial);
  if (! accelerometer.begin(0x18)) {
    Serial.println("Couldn't start. Check wiring.");
    while (true);     // stop here and do nothing
  }

  accelerometer.setRange(LIS3DH_RANGE_2_G);   // 2, 4, 8 or 16 G!
  Serial.print(accelerometer.getRange());
}

void loop() {
  accelerometer.read();      // get X Y and Z data at once
  // Then print out the raw data
    Serial.print(convertReading(accelerometer.x));
    Serial.print(",");
    Serial.print(convertReading(accelerometer.y));
    Serial.print(",");
    Serial.println(convertReading(accelerometer.z));
    
}

float convertReading(int reading) {
  float divisor = 2 << (13 - accelerometer.getRange());
  float acceleration = (float)reading / divisor;
  return acceleration;
}

