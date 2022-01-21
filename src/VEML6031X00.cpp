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

#include "VEML6031X00.h"

#define VEML6031X00_ADDRESS            0x29
#define VEML6031X00_WHO_AM_I           0x01

#define VEML6031X00_REG_ALS_CONF0      0x00
#define VEML6031X00_REG_ALS_CONF1      0x01
#define VEML6031X00_REG_ALS_WH_L       0x04
#define VEML6031X00_REG_ALS_WH_H       0x05
#define VEML6031X00_REG_ALS_WL_L       0x06
#define VEML6031X00_REG_ALS_WL_H       0x07
#define VEML6031X00_REG_ALS_DATA_L     0x10
#define VEML6031X00_REG_ALS_DATA_H     0x11
#define VEML6031X00_REG_IR_DATA_L      0x12
#define VEML6031X00_REG_IR_DATA_H      0x13
#define VEML6031X00_REG_ID_L           0x14
#define VEML6031X00_REG_ID_H           0x15
#define VEML6031X00_REG_ALS_INT        0x17

// ALS_CONF0
#define VEML6031X00_SD                 (1 << 0)
#define VEML6031X00_ALS_INT_EN         (1 << 1)
#define VEML6031X00_ALS_TRIG           (1 << 2)
#define VEML6031X00_ALS_AF             (1 << 3)
#define VEML6031X00_ALS_IT_SHIFT       4
#define VEML6031X00_ALS_IT_MASK        (0x7 << VEML6031X00_ALS_IT_SHIFT)
#define VEML6031X00_ALS_IT_3_125MS     (0x0 << VEML6031X00_ALS_IT_SHIFT)
#define VEML6031X00_ALS_IT_6_25MS      (0x1 << VEML6031X00_ALS_IT_SHIFT)
#define VEML6031X00_ALS_IT_12_5MS      (0x2 << VEML6031X00_ALS_IT_SHIFT)
#define VEML6031X00_ALS_IT_25MS        (0x3 << VEML6031X00_ALS_IT_SHIFT)
#define VEML6031X00_ALS_IT_50MS        (0x4 << VEML6031X00_ALS_IT_SHIFT)
#define VEML6031X00_ALS_IT_100MS       (0x5 << VEML6031X00_ALS_IT_SHIFT)
#define VEML6031X00_ALS_IT_200MS       (0x6 << VEML6031X00_ALS_IT_SHIFT)
#define VEML6031X00_ALS_IT_400MS       (0x7 << VEML6031X00_ALS_IT_SHIFT)

// ALS_CONF1
#define VEML6031X00_ALS_CAL            (1 << 0)
#define VEML6031X00_ALS_PERS_SHIFT     1
#define VEML6031X00_ALS_PERS_MASK      (0x3 << VEML6031X00_ALS_PERS_SHIFT)
#define VEML6031X00_ALS_PERS_1         (0x0 << VEML6031X00_ALS_PERS_SHIFT)
#define VEML6031X00_ALS_PERS_2         (0x1 << VEML6031X00_ALS_PERS_SHIFT)
#define VEML6031X00_ALS_PERS_4         (0x2 << VEML6031X00_ALS_PERS_SHIFT)
#define VEML6031X00_ALS_PERS_8         (0x3 << VEML6031X00_ALS_PERS_SHIFT)
#define VEML6031X00_ALS_GAIN_SHIFT     1
#define VEML6031X00_ALS_GAIN_MASK      (0x3 << VEML6031X00_ALS_GAIN_SHIFT)
#define VEML6031X00_ALS_GAIN_1         (0x0 << VEML6031X00_ALS_GAIN_SHIFT)
#define VEML6031X00_ALS_GAIN_2         (0x1 << VEML6031X00_ALS_GAIN_SHIFT)
#define VEML6031X00_ALS_GAIN_0_66      (0x2 << VEML6031X00_ALS_GAIN_SHIFT)
#define VEML6031X00_ALS_GAIN_0_5       (0x3 << VEML6031X00_ALS_GAIN_SHIFT)
#define VEML6031X00_PD_DIV4            (1 << 6)
#define VEML6031X00_ALS_IR_SD          (1 << 7)

// Default values
#define VEML6031X00_DEFAULT_ALS_CONF0  (VEML6031X00_ALS_IT_100MS)
#define VEML6031X00_DEFAULT_ALS_CONF1  (VEML6031X00_ALS_CAL)
#define VEML6031X00_DEFAULT_ALS_WH     0xFFFF
#define VEML6031X00_DEFAULT_ALS_WL     0x0000

VEML6031X00Class::VEML6031X00Class(TwoWire& wire) : _wire(&wire)
{
}

VEML6031X00Class::~VEML6031X00Class(void)
{
}     

int VEML6031X00Class::begin(void)
{
  _wire->begin();
  slaveAddress = VEML6031X00_ADDRESS;

  // Prevent I2C bus lockup
  writeByte(VEML6031X00_REG_ALS_WL_L, 0x00);
  writeByte(VEML6031X00_REG_ALS_WL_L, 0x00);

  uint8_t id;
  if (!readByte(VEML6031X00_REG_ID_L, &id) || id != VEML6031X00_WHO_AM_I)
    return 0;

  // Initialization
  if (writeWord(VEML6031X00_REG_ALS_CONF0, (VEML6031X00_DEFAULT_ALS_CONF0) |
                                        (VEML6031X00_DEFAULT_ALS_CONF1 << 8)) &&
      writeWord(VEML6031X00_REG_ALS_WH_L, VEML6031X00_DEFAULT_ALS_WH) &&
      writeWord(VEML6031X00_REG_ALS_WL_L, VEML6031X00_DEFAULT_ALS_WL))
  {
    lens_factor = 1.0;
    return 1;
  }
  return 0;
}

void VEML6031X00Class::end(void)
{
  ALS_INT_EN(false);
}

boolean VEML6031X00Class::reads(uint8_t reg, uint8_t *data, uint8_t num)
{
  uint8_t   wd;

  _wire->beginTransmission(slaveAddress);
  if (_wire->write (reg) != 1)
    goto reads_error;
  _wire->endTransmission(false);
  if (_wire->requestFrom(slaveAddress, (uint8_t)2) != 2)
    goto reads_error;
  
  wd = 10;
  while (_wire->available()<num && wd)
    wd--;
  if (!wd)
    goto reads_error;

  for (int i = 0; i < num; i++, data++)
    *data = _wire->read();
    
  return true;

reads_error:
  _wire->endTransmission(true);
  return false;
}

boolean VEML6031X00Class::writes(uint8_t reg, uint8_t *data, uint8_t num)
{
  boolean status = true;

  if ((reg == 0x00 && num == 1) || (reg == 0x01))
    return false;
  
  _wire->beginTransmission(slaveAddress);
  if (!_wire->write(reg))
    status = false;

  for (int i = 0; status && i < num; i ++, data++)
    if (!_wire->write(*data))
      status = false;
  _wire->endTransmission(true);

  return status;
}

boolean VEML6031X00Class::readByte(uint8_t reg, uint8_t *byteData)
{
  return reads(reg, byteData, 1);  
}

boolean VEML6031X00Class::writeByte(uint8_t reg, uint8_t byteData)
{
  return writes(reg, &byteData, 1);
}

boolean VEML6031X00Class::readWord(uint8_t reg, uint16_t *wordData)
{
  uint8_t buffer[2];
  boolean status = reads(reg, buffer, 2);
  *wordData = buffer[0] | ((uint16_t)buffer[1]) << 8;
  return status;
}

boolean VEML6031X00Class::writeWord(uint8_t reg, uint16_t wordData)
{
  uint8_t buffer[] = {(uint8_t)wordData, (uint8_t)(wordData >> 8)};
  return writes(reg, buffer, 2);
}

boolean VEML6031X00Class::bitsUpdate(uint8_t reg, uint8_t mask, uint8_t update)
{
  uint8_t value;
  
  if (!readByte(reg, &value))
    return false;
  value &= mask;
  value |= update;

  if (reg == 0x00 || reg == 0x01)
  {
    uint16_t valWord;
    if (!readWord(reg, &valWord))
      return false;
    if (reg == 0x00)
    {
      valWord &= 0xFF00;
      valWord |= value;
    } else
    {
      valWord &= 0x00FF;
      valWord |= value << 8;
    }
    return writeWord(0x00, valWord);
  }
  return writeByte(reg, value);
}

boolean VEML6031X00Class::read_ALS(uint16_t *als)
{
  return readWord(VEML6031X00_REG_ALS_DATA_L, als);
}

boolean VEML6031X00Class::read_IR(uint16_t *ir)
{
  return readWord(VEML6031X00_REG_IR_DATA_L, ir);
}

float VEML6031X00Class::get_lux(void)
{
  uint16_t als;
  uint8_t id = get_array_id();
  
  if (id < 0 || !read_ALS(&als))
    return -1.0f;

  float lux = (float)als;
  lux *= resolution_map[id].mlux_per_bit;
  lux *= lens_factor;
  lux /= 1000;

  return lux;
}

boolean VEML6031X00Class::ALS_INT_EN(boolean enable)
{
  return bitsUpdate(
    VEML6031X00_REG_ALS_CONF0,
    ~VEML6031X00_ALS_INT_EN,
    enable ? VEML6031X00_ALS_INT_EN : 0);
}

boolean VEML6031X00Class::ALS_INT_EN_with_threshold(float percent)
{
  uint16_t als;
  
  if (!read_ALS(&als) || percent <= 0)
    return false;
 
  float thdh = (float)als * (100.0 + percent) / 100.0;
  float thdl = (float)als * (100.0 - percent) / 100.0;
  if (thdh - thdl < 1.0)
    thdh += 1.0;
  uint16_t wh = (thdh > 65535.0f) ? 65535 : (uint16_t)thdh;   
  uint16_t wl = (thdl < 0.0f) ? 0 : (uint16_t)thdl;

  if (ALS_INT_EN(false) &&
      writeWord(VEML6031X00_REG_ALS_WH_L, wh) &&
      writeWord(VEML6031X00_REG_ALS_WL_L, wl) &&
      ALS_INT_EN(true))
    return true;
    
  return false;
}

boolean VEML6031X00Class::read_ALS_INT(uint8_t *int_flag)
{
  return readByte(VEML6031X00_REG_ALS_INT, int_flag);
}

int VEML6031X00Class::get_array_id(void)
{
  uint8_t als_conf0, als_conf1;
  
  if (!readByte(VEML6031X00_REG_ALS_CONF0, &als_conf0) ||
      !readByte(VEML6031X00_REG_ALS_CONF1, &als_conf1))
    return -1;

  uint8_t it = (als_conf0 & VEML6031X00_ALS_IT_MASK) >> VEML6031X00_ALS_IT_SHIFT;
  uint8_t gain = (als_conf1 & VEML6031X00_ALS_GAIN_MASK) >> VEML6031X00_ALS_GAIN_SHIFT;
  uint8_t pd_div4 = (als_conf1 & VEML6031X00_PD_DIV4) ? 1 : 0;
  uint8_t num_map = sizeof(resolution_map)/sizeof(resolution_map[0]);
  uint8_t id;

  for (id = 0; id < num_map; id++)
    if (it == resolution_map[id].it && 
        gain == resolution_map[id].gain &&
        pd_div4 == resolution_map[id].pd_div4)
      break;
  if (id >= num_map)
    return -1;
  return id;
}

VEML6031X00Class veml6031x00(Wire);
