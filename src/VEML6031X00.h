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

#include <Arduino.h>
#include <Wire.h>

class VEML6031X00Class {
  public:
    VEML6031X00Class(TwoWire& wire);
    virtual ~VEML6031X00Class();

    int begin();
    void end();
    boolean reads( uint8_t reg, uint8_t *data, uint8_t num);
    boolean writes( uint8_t reg, uint8_t *data, uint8_t num);
    boolean readByte( uint8_t reg, uint8_t *byteData);
    boolean writeByte( uint8_t reg, uint8_t byteData);
    boolean readWord( uint8_t reg, uint16_t *wordData);
    boolean writeWord( uint8_t reg, uint16_t wordData);
    virtual boolean read_ALS(uint16_t *als);
    virtual boolean read_IR(uint16_t *ir);
    virtual float get_lux(void);
    boolean ALS_INT_EN(boolean enable);
    boolean ALS_INT_EN_with_threshold(float percent);
    boolean read_ALS_INT(uint8_t *int_flag);
    int get_array_id(void);
    
    float lens_factor;

    const uint8_t
      ALS_IF_H = (1 << 1),
      ALS_IF_L = (1 << 2);

    typedef struct {
      uint8_t it;
      uint8_t gain;
      uint8_t pd_div4;
      float ms;
      float mlux_per_bit;
    } RESOLUTION_ARRAY;

    RESOLUTION_ARRAY resolution_map[64] = {
      {0x7, 1, 0,  400,   3.4}, {0x7, 0, 0,  400,   6.8}, {0x7, 2, 0,  400,  10.3}, {0x7, 3, 0,  400,  13.6},
      {0x6, 1, 0,  200,   6.8}, {0x6, 0, 0,  200,  13.6}, {0x6, 2, 0,  200,  20.6}, {0x6, 3, 0,  200,  27.2},
      {0x5, 1, 0,  100,  13.6}, {0x5, 0, 0,  100,  27.2}, {0x5, 2, 0,  100,  41.2}, {0x5, 3, 0,  100,  54.4},
      {0x4, 1, 0,   50,  27.2}, {0x4, 0, 0,   50,  54.4}, {0x4, 2, 0,   50,  82.4}, {0x4, 3, 0,   50, 108.8},
      {0x3, 1, 0,   25,  54.4}, {0x3, 0, 0,   25, 108.8}, {0x3, 2, 0,   25, 164.8}, {0x3, 3, 0,   25, 217.6},
      {0x2, 1, 0, 12.5, 108.8}, {0x2, 0, 0, 12.5, 217.6}, {0x2, 2, 0, 12.5, 329.7}, {0x2, 3, 0, 12.5, 435.2},
      {0x1, 1, 0, 6.25, 217.6}, {0x1, 0, 0, 6.25, 435.2}, {0x1, 2, 0, 6.25, 659.4}, {0x1, 3, 0, 6.25, 870.4},
      {0x0, 1, 0,3.125, 435.2}, {0x0, 0, 0,3.125, 870.4}, {0x0, 2, 0,3.125,1318.8}, {0x0, 3, 0,3.125,1740.8},

      {0x7, 1, 1,  400,  13.6}, {0x7, 0, 1,  400,  27.2}, {0x7, 2, 1,  400,  41.2}, {0x7, 3, 1,  400,  54.4},
      {0x6, 1, 1,  200,  27.2}, {0x6, 0, 1,  200,  54.4}, {0x6, 2, 1,  200,  82.4}, {0x6, 3, 1,  200, 108.8},
      {0x5, 1, 1,  100,  54.4}, {0x5, 0, 1,  100, 108.8}, {0x5, 2, 1,  100, 164.8}, {0x5, 3, 1,  100, 217.6},
      {0x4, 1, 1,   50, 108.8}, {0x4, 0, 1,   50, 217.6}, {0x4, 2, 1,   50, 329.7}, {0x4, 3, 1,   50, 435.2},
      {0x3, 1, 1,   25, 217.6}, {0x3, 0, 1,   25, 435.2}, {0x3, 2, 1,   25, 659.4}, {0x3, 3, 1,   25, 870.4},
      {0x2, 1, 1, 12.5, 435.2}, {0x2, 0, 1, 12.5, 870.4}, {0x2, 2, 1, 12.5,1318.8}, {0x2, 3, 1, 12.5,1740.8},
      {0x1, 1, 1, 6.25, 870.4}, {0x1, 0, 1, 6.25,1740.8}, {0x1, 2, 1, 6.25,2637.6}, {0x1, 3, 1, 6.25,3481.6},
      {0x0, 1, 1,3.125,1740.8}, {0x0, 0, 1,3.125,3481.6}, {0x0, 2, 1,3.125,5275.2}, {0x0, 3, 1,3.125,6963.2},
    };

  private:
    TwoWire* _wire;
    uint8_t slaveAddress;
    boolean bitsUpdate(uint8_t reg, uint8_t mask, uint8_t update);  
};

extern VEML6031X00Class veml6031x00;
