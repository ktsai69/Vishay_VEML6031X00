# Vishay_VEML6031X00 library

## Methods

### `begin()`

Initialize the veml6031x00.

#### Syntax 

```
veml6031x00.begin()
```

#### Parameters

None.

#### Returns

1 on success, 0 on failure.

#### Example

```
if (!veml6031x00.begin()) {
    Serial.println("Failed to initialize veml6031x00!");
    while (1);
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [reads()](#reads)
* [writes()](#writes)
* [readByte()](#readByte)
* [writeByte()](#writeByte)
* [readWord()](#readWord)
* [writeWord()](#writeWord)
* [read_ALS()](#read_ALS)
* [read_IR()](#read_IR)
* [get_lux()](#get_lux)
* [ALS_INT_EN()](#ALS_INT_EN)
* [ALS_INT_EN_with_threshold()](#ALS_INT_EN_with_threshold)
* [read_ALS_INT()](#read_ALS_INT)
* [lens_factor](#lens_factor)

### `end()`

De-initialize the veml6031x00.

#### Syntax 

```
veml6031x00.end()
```

#### Parameters

None.

#### Returns

None.

#### Example

```
if (!veml6031x00.begin()) {
    Serial.println("Failed to initialize veml6031x00!");
    while (1);
}

// Read data...

// Done with the veml6031x00 readings
veml6031x00.end();
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [reads()](#reads)
* [writes()](#writes)
* [readByte()](#readByte)
* [writeByte()](#writeByte)
* [readWord()](#readWord)
* [writeWord()](#writeWord)
* [read_ALS()](#read_ALS)
* [read_IR()](#read_IR)
* [get_lux()](#get_lux)
* [ALS_INT_EN()](#ALS_INT_EN)
* [ALS_INT_EN_with_threshold()](#ALS_INT_EN_with_threshold)
* [read_ALS_INT()](#read_ALS_INT)
* [lens_factor](#lens_factor)

### `reads()`

Read multiple registers. 

#### Syntax 

```
boolean veml6031x00.reads(uint8_t reg, uint8_t *data, uint8_t num)
```

#### Parameters

reg - register address

data - point of uint8_t to store data

num - number of registers

#### Returns

true on success, false on failure.

#### Example

```
uint8_t data[4];

// read register from 0x10 to 0x13
if (veml6031x00.reads(0x10, data, 4))
{
	for (int i = 0; i < 4; i++)
	{
		Serial.print(data[i], HEX);
		Serial.p;rint(" ");
	}
	Serial.println();
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [reads()](#reads)
* [writes()](#writes)
* [readByte()](#readByte)
* [writeByte()](#writeByte)
* [readWord()](#readWord)
* [writeWord()](#writeWord)
* [read_ALS()](#read_ALS)
* [read_IR()](#read_IR)
* [get_lux()](#get_lux)
* [ALS_INT_EN()](#ALS_INT_EN)
* [ALS_INT_EN_with_threshold()](#ALS_INT_EN_with_threshold)
* [read_ALS_INT()](#read_ALS_INT)
* [lens_factor](#lens_factor)

### `writes()`

Write multiple registers. 

#### Syntax 

```
boolean veml6031x00.writes(uint8_t reg, uint8_t *data, uint8_t num)
```

#### Parameters

reg - register address

data - point of uint8_t data array

num - number of registers

#### Returns

true on success, false on failure.

#### Example

```
uint8_t data[] = {0x00, 0x01};

// write to register 0x00 and 0x01
if (veml6031x00.writes(0x00, data, 2))
{
	Serial.println("Success to init reg.0x00 and reg.0x01");
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [reads()](#reads)
* [writes()](#writes)
* [readByte()](#readByte)
* [writeByte()](#writeByte)
* [readWord()](#readWord)
* [writeWord()](#writeWord)
* [read_ALS()](#read_ALS)
* [read_IR()](#read_IR)
* [get_lux()](#get_lux)
* [ALS_INT_EN()](#ALS_INT_EN)
* [ALS_INT_EN_with_threshold()](#ALS_INT_EN_with_threshold)
* [read_ALS_INT()](#read_ALS_INT)
* [lens_factor](#lens_factor)

### `readsByte()`

Read a register. 

#### Syntax 

```
boolean veml6031x00.readByte(uint8_t reg, uint8_t *data)
```

#### Parameters

reg - register address

data - point of uint8_t to store data

#### Returns

true on success, false on failure.

#### Example

```
uint8_t data;

// read register 0x00
if (veml6031x00.readByte(0x00, data))
{
	Serial.println(data, HEX);
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [reads()](#reads)
* [writes()](#writes)
* [readByte()](#readByte)
* [writeByte()](#writeByte)
* [readWord()](#readWord)
* [writeWord()](#writeWord)
* [read_ALS()](#read_ALS)
* [read_IR()](#read_IR)
* [get_lux()](#get_lux)
* [ALS_INT_EN()](#ALS_INT_EN)
* [ALS_INT_EN_with_threshold()](#ALS_INT_EN_with_threshold)
* [read_ALS_INT()](#read_ALS_INT)
* [lens_factor](#lens_factor)

### `writeByte()`

Write a register. 

#### Syntax 

```
boolean veml6031x00.writeByte(uint8_t reg, uint8_t data)
```

#### Parameters

reg - register address

data - data to write

#### Returns

true on success, false on failure.

#### Example

```
// write to register 0x00
if (veml6031x00.writes(0x00, 0x01))
{
	Serial.println("Success to write reg.0x00");
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [reads()](#reads)
* [writes()](#writes)
* [readByte()](#readByte)
* [writeByte()](#writeByte)
* [readWord()](#readWord)
* [writeWord()](#writeWord)
* [read_ALS()](#read_ALS)
* [read_IR()](#read_IR)
* [get_lux()](#get_lux)
* [ALS_INT_EN()](#ALS_INT_EN)
* [ALS_INT_EN_with_threshold()](#ALS_INT_EN_with_threshold)
* [read_ALS_INT()](#read_ALS_INT)
* [lens_factor](#lens_factor)

### `readsWord()`

Read two registers and store as 16-bit data. 

#### Syntax 

```
boolean veml6031x00.readWord(uint8_t reg, uint16_t *data)
```

#### Parameters

reg - register address

data - point of uint16_t to store data

#### Returns

true on success, false on failure.

#### Example

```
uint16_t data;

// read register 0x10
if (veml6031x00.readByte(0x10, data))
{
	Serial.println(data);
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [reads()](#reads)
* [writes()](#writes)
* [readByte()](#readByte)
* [writeByte()](#writeByte)
* [readWord()](#readWord)
* [writeWord()](#writeWord)
* [read_ALS()](#read_ALS)
* [read_IR()](#read_IR)
* [get_lux()](#get_lux)
* [ALS_INT_EN()](#ALS_INT_EN)
* [ALS_INT_EN_with_threshold()](#ALS_INT_EN_with_threshold)
* [read_ALS_INT()](#read_ALS_INT)
* [lens_factor](#lens_factor)

### `writeWord()`

Write to continuous two register as a 16-bit registers. 

#### Syntax 

```
boolean veml6031x00.writeWord(uint8_t reg, uint16_t data)
```

#### Parameters

reg - register address

data - data to write

#### Returns

true on success, false on failure.

#### Example

```
// write to register 0x00 and 0x01
if (veml6031x00.writeWord(0x00, 0x0100))
{
	Serial.println("Success to write");
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [reads()](#reads)
* [writes()](#writes)
* [readByte()](#readByte)
* [writeByte()](#writeByte)
* [readWord()](#readWord)
* [writeWord()](#writeWord)
* [read_ALS()](#read_ALS)
* [read_IR()](#read_IR)
* [get_lux()](#get_lux)
* [ALS_INT_EN()](#ALS_INT_EN)
* [ALS_INT_EN_with_threshold()](#ALS_INT_EN_with_threshold)
* [read_ALS_INT()](#read_ALS_INT)
* [lens_factor](#lens_factor)

### `read_ALS()`

Read the veml6031x00's Ambient Light sensor count. 

#### Syntax 

```
boolean veml6031x00.read_ALS(uint16_t *als)
```

#### Parameters

als - point of uint16_t for als count

#### Returns

true on success, false on failure.

#### Example

```
uint16_t als;

if (veml6031x00.read_ALS(&als))
    Serial.print(als);

```

#### See also

* [begin()](#begin)
* [end()](#end)
* [reads()](#reads)
* [writes()](#writes)
* [readByte()](#readByte)
* [writeByte()](#writeByte)
* [readWord()](#readWord)
* [writeWord()](#writeWord)
* [read_ALS()](#read_ALS)
* [read_IR()](#read_IR)
* [get_lux()](#get_lux)
* [ALS_INT_EN()](#ALS_INT_EN)
* [ALS_INT_EN_with_threshold()](#ALS_INT_EN_with_threshold)
* [read_ALS_INT()](#read_ALS_INT)
* [lens_factor](#lens_factor)

### `read_IR()`

Read the veml6031x00's Infrared count. 

#### Syntax 

```
boolean veml6031x00.read_IR(uint16_t *ir)
```

#### Parameters

IR - point of uint16_t for infrared count

#### Returns

true on success, false on failure.

#### Example

```
uint16_t ir;

if (veml6031x00.read_IR(&ir))
    Serial.print(ir);

```

#### See also

* [begin()](#begin)
* [end()](#end)
* [reads()](#reads)
* [writes()](#writes)
* [readByte()](#readByte)
* [writeByte()](#writeByte)
* [readWord()](#readWord)
* [writeWord()](#writeWord)
* [read_ALS()](#read_ALS)
* [read_IR()](#read_IR)
* [get_lux()](#get_lux)
* [ALS_INT_EN()](#ALS_INT_EN)
* [ALS_INT_EN_with_threshold()](#ALS_INT_EN_with_threshold)
* [read_ALS_INT()](#read_ALS_INT)
* [lens_factor](#lens_factor)

### `get_lux()`

Read the veml6031x00's Ambient Lioght sensor and convert to lux. 

#### Syntax 

```
float veml6031x00.get_lux()
```

#### Parameters

None.

#### Returns

Positive or zero on success, negative on failure.

#### Example

```
float lux = veml6031x00.get_lux();

if (lux >= 0)
    Serial.print(lux);

```

#### See also

* [begin()](#begin)
* [end()](#end)
* [reads()](#reads)
* [writes()](#writes)
* [readByte()](#readByte)
* [writeByte()](#writeByte)
* [readWord()](#readWord)
* [writeWord()](#writeWord)
* [read_ALS()](#read_ALS)
* [read_IR()](#read_IR)
* [get_lux()](#get_lux)
* [ALS_INT_EN()](#ALS_INT_EN)
* [ALS_INT_EN_with_threshold()](#ALS_INT_EN_with_threshold)
* [read_ALS_INT()](#read_ALS_INT)
* [lens_factor](#lens_factor)

### `ALS_INT_EN()`

Enable/disable interrupt 

#### Syntax 

```
boolean veml6031x00.ALS_INT_EN()
```

#### Parameters

enable - true to enable interrupt, false to disable interrupt.

#### Returns

true on success, false on failure.

#### Example

```
// Enable interrupt
veml6031x00.ALS_INT_EN(enable);
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [reads()](#reads)
* [writes()](#writes)
* [readByte()](#readByte)
* [writeByte()](#writeByte)
* [readWord()](#readWord)
* [writeWord()](#writeWord)
* [read_ALS()](#read_ALS)
* [read_IR()](#read_IR)
* [get_lux()](#get_lux)
* [ALS_INT_EN()](#ALS_INT_EN)
* [ALS_INT_EN_with_threshold()](#ALS_INT_EN_with_threshold)
* [read_ALS_INT()](#read_ALS_INT)
* [lens_factor](#lens_factor)

### `ALS_INT_EN_with_threshold()`

Enable interrupt and set the threshold by percentage. 

#### Syntax 

```
boolean veml6031x00.ALS_INT_EN_with_threshold(float percent)
```

#### Parameters

percent - threshold percentage.

#### Returns

true on success, false on failure.

#### Example

```
// Enable interrupt and set threshold 3%
veml6031x00.ALS_INT_EN_with_threshold(3.0f);
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [reads()](#reads)
* [writes()](#writes)
* [readByte()](#readByte)
* [writeByte()](#writeByte)
* [readWord()](#readWord)
* [writeWord()](#writeWord)
* [read_ALS()](#read_ALS)
* [read_IR()](#read_IR)
* [get_lux()](#get_lux)
* [ALS_INT_EN()](#ALS_INT_EN)
* [ALS_INT_EN_with_threshold()](#ALS_INT_EN_with_threshold)
* [read_ALS_INT()](#read_ALS_INT)
* [lens_factor](#lens_factor)

### `read_ALS_INT()`

Clean interrupt 

#### Syntax 

```
boolean veml6031x00.read_ALS_INT(uint16_t *int_flag)
```

#### Parameters

int_flag - point of uint16_t.  The return values includes:
- **ALS_IF_H** for excess the high threshold.
- **ALS_IF_L** for below the low threshold.

#### Returns

true on success, false on failure.

#### Example

```
uint16_t int_flag;
if (veml6031x00.read_ALS_INT(&int_flag))
{
  if (int_flag & veml6031x00.ALS_IF_L)
    Serial.print("\tLow threshold.");
  if (int_flag & veml6031x00.ALS_IF_H)
    Serial.print("\tHigh threshold.");
  Serial.println();
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [reads()](#reads)
* [writes()](#writes)
* [readByte()](#readByte)
* [writeByte()](#writeByte)
* [readWord()](#readWord)
* [writeWord()](#writeWord)
* [read_ALS()](#read_ALS)
* [read_IR()](#read_IR)
* [get_lux()](#get_lux)
* [ALS_INT_EN()](#ALS_INT_EN)
* [ALS_INT_EN_with_threshold()](#ALS_INT_EN_with_threshold)
* [read_ALS_INT()](#read_ALS_INT)
* [lens_factor](#lens_factor)

### `lens_factor`

Lens Factor for customerize material effect. 

#### Syntax 

```
float veml6031x00.lens_factor
```

#### Parameters

None.

#### Returns

Floating variable.

#### Example

```
Serial.print(veml6031x00.lens_factor);

```

#### See also

* [begin()](#begin)
* [end()](#end)
* [reads()](#reads)
* [writes()](#writes)
* [readByte()](#readByte)
* [writeByte()](#writeByte)
* [readWord()](#readWord)
* [writeWord()](#writeWord)
* [read_ALS()](#read_ALS)
* [read_IR()](#read_IR)
* [get_lux()](#get_lux)
* [ALS_INT_EN()](#ALS_INT_EN)
* [ALS_INT_EN_with_threshold()](#ALS_INT_EN_with_threshold)
* [read_ALS_INT()](#read_ALS_INT)
* [lens_factor](#lens_factor)
