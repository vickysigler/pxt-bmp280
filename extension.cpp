#include "pxt.h"
#include "BMP280.h"

using namespace pxt;

namespace bmp280 {
    BMP280 barometer;
    int i2c_address = 0x77;

    //%
    void setAddress(int address) {
        i2c_address = address;
    }

    //%
    void init() {
        barometer = BMP280(i2c_address);
        barometer.init();
    }

    //%
    float getPressure() {
        return barometer.getPressure() / 100;
    }

    //%
    float getTemperature() {
        return barometer.getTemperature();
    }
}