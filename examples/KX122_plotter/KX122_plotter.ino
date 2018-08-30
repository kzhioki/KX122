/*****************************************************************************
  KX122_plotter.ino
 Copyright (c) 2018 ROHM Co.,Ltd.
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
******************************************************************************/
#include <Wire.h>
#include "KX122.h"

KX122 kx122(KX122_DEVICE_ADDRESS_1F);

void setup() {
  byte rc;

  Serial.begin(115200);
  while (!Serial);

  Wire.begin();

  rc = kx122.init();
  if (rc != 0) {
    Serial.println(F("KX122 initialization failed"));
    Serial.flush();
  }
}

void loop() {
  byte rc;
  union {
    unsigned char u8[6];
    signed short s16[3];
  } data;
  rc = kx122.get_rawval(data.u8);
  if (rc == 0) {
    Serial.print(data.s16[0]);
    Serial.print(",");
    Serial.print(data.s16[1]);
    Serial.print(",");
    Serial.println(data.s16[2]);
  }
  delay(10);
}
