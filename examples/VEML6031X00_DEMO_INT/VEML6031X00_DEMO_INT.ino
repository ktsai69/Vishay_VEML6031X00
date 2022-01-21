/*
  This file is part of the Vishay_VEML6031X00 library.
  Copyright (c) 2021 Vishay Capella.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

/*
 * This demo requests to cnnect the INT pin of VEML6031X00 to Digital Pin 2. 
 */
 
#include <Vishay_VEML6031X00.h>

const byte interruptPin = 2;
volatile boolean isr_triggered = false;
float thd_percent = 1.0f;               // threshold 1%

void isr()
{
  isr_triggered = true;  
}

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  Serial.println();

  if (!veml6031x00.begin())
  {
    Serial.println("Failed to initialize veml6031x00");
    while(1);
  }

  // Initial interrupt
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), isr, FALLING);
  veml6031x00.ALS_INT_EN_with_threshold(thd_percent);
  Serial.println("ALS\tLux");
}

void loop()
{
  if (isr_triggered)
  {
    isr_triggered = false;
    uint8_t int_flag;
    if (veml6031x00.read_ALS_INT(&int_flag) &&
        (int_flag & (veml6031x00.ALS_IF_H | veml6031x00.ALS_IF_L)))
    {
      uint16_t als;
      if (veml6031x00.read_ALS(&als))
      {
        Serial.print(als);
        Serial.print('\t');
        Serial.println(veml6031x00.get_lux());
      }
      veml6031x00.ALS_INT_EN_with_threshold(thd_percent);
    }
  }
}
