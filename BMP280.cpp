/*
 * BMP280 Microbit Library
 * Adapted from https://github.com/Seeed-Studio/Grove_BMP280
 * 
 * Rebecca Clavier, 2019
 * Licensed under the MIT license
*/

#include "BMP280.h"

BMP280::BMP280() : i2c(I2C_SDA0, I2C_SCL0)
{
    _devAddr = BMP280_ADDRESS << 1;
}

BMP280::BMP280(int i2c_addr) : i2c(I2C_SDA0, I2C_SCL0)
{
    _devAddr = i2c_addr << 1;
}

bool BMP280::init()
{
    uint8_t chip_id = 0;
    uint8_t retry = 0;

    i2c.start();

    while ((retry++ < 5) && (chip_id != 0x58))
    {
        chip_id = bmp280Read8(BMP280_REG_CHIPID);
#ifdef BMP280_DEBUG_PRINT
        Serial.print("Read chip ID: ");
        Serial.println(chip_id);
#endif
    }

    dig_T1 = bmp280Read16LE(BMP280_REG_DIG_T1);
    dig_T2 = bmp280ReadS16LE(BMP280_REG_DIG_T2);
    dig_T3 = bmp280ReadS16LE(BMP280_REG_DIG_T3);

    dig_P1 = bmp280Read16LE(BMP280_REG_DIG_P1);
    dig_P2 = bmp280ReadS16LE(BMP280_REG_DIG_P2);
    dig_P3 = bmp280ReadS16LE(BMP280_REG_DIG_P3);
    dig_P4 = bmp280ReadS16LE(BMP280_REG_DIG_P4);
    dig_P5 = bmp280ReadS16LE(BMP280_REG_DIG_P5);
    dig_P6 = bmp280ReadS16LE(BMP280_REG_DIG_P6);
    dig_P7 = bmp280ReadS16LE(BMP280_REG_DIG_P7);
    dig_P8 = bmp280ReadS16LE(BMP280_REG_DIG_P8);
    dig_P9 = bmp280ReadS16LE(BMP280_REG_DIG_P9);

    writeRegister(BMP280_REG_CONTROL, 0x3F);
    return true;
}

float BMP280::getTemperature(void)
{
    int32_t var1, var2;

    int32_t adc_T = bmp280Read24(BMP280_REG_TEMPDATA);

    adc_T >>= 4;
    var1 = (((adc_T >> 3) - ((int32_t)(dig_T1 << 1))) *
            ((int32_t)dig_T2)) >>
           11;

    var2 = (((((adc_T >> 4) - ((int32_t)dig_T1)) *
              ((adc_T >> 4) - ((int32_t)dig_T1))) >>
             12) *
            ((int32_t)dig_T3)) >>
           14;

    t_fine = var1 + var2;
    float T = (t_fine * 5 + 128) >> 8;
    return T / 100;
}

float BMP280::getPressure(void)
{
    int64_t var1, var2;
    float p;

    // Call getTemperature to get t_fine
    getTemperature();

    int32_t adc_P = bmp280Read24(BMP280_REG_PRESSUREDATA);
    adc_P >>= 4;

    var1 = ((int64_t)t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)dig_P6;
    var2 = var2 + ((var1 * (int64_t)dig_P5) << 17);
    var2 = var2 + (((int64_t)dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t)dig_P3) >> 8) + ((var1 * (int64_t)dig_P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)dig_P1) >> 33;
    if (var1 == 0)
    {
        return 0; // avoid exception caused by division by zero
    }
    p = 1048576 - adc_P;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = (((int64_t)dig_P9) * (p >> 13) * (p >> 13)) >> 25;
    var2 = (((int64_t)dig_P8) * p) >> 19;
    p = ((p + var1 + var2) >> 8) + (((int64_t)dig_P7) << 4);
    return (float)p / 256;
}

uint8_t BMP280::bmp280Read8(uint8_t reg)
{
    return i2c.readRegister(_devAddr, reg);
}

uint16_t BMP280::bmp280Read16(uint8_t reg)
{
    char data[2];

    i2c.writeRegister(_devAddr, reg, 1);
    i2c.read(_devAddr, data, 2);

    return (uint16_t)data[0] << 8 | data[1];
}

uint16_t BMP280::bmp280Read16LE(uint8_t reg)
{
    uint16_t data = bmp280Read16(reg);
    return (data >> 8) | (data << 8);
}

int16_t BMP280::bmp280ReadS16(uint8_t reg)
{
    return (int16_t)bmp280Read16(reg);
}

int16_t BMP280::bmp280ReadS16LE(uint8_t reg)
{
    return (int16_t)bmp280Read16LE(reg);
}

uint32_t BMP280::bmp280Read24(uint8_t reg)
{
    uint32_t data;

    char res[3];

    i2c.writeRegister(_devAddr, reg, 1);
    i2c.read(_devAddr, res, 3);

    data = res[0];
    data <<= 8;
    data |= res[1];
    data <<= 8;
    data |= res[2];

    return data;
}

void BMP280::writeRegister(uint8_t reg, uint8_t val)
{
    i2c.writeRegister(_devAddr, reg, val);
}
