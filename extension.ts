/**
 * Provides support for the BMP280 barometer module.
 */
//% color=#7300ff weight=0 icon="\uf0c2" block="Barometer"
namespace barometer {
    /**
     * Changes the default I2C address from 0x77 to the provided address
     * @param The I2C address to use
    */
    //% shim=bmp280::setAddress
    export function setAddress(address: number): void { }

    /**
     * Initialises the BMP280 module
     */
    //% shim=bmp280::init
    export function init(): void { }

    /**
     * Returns the pressure read by the BMP280's barometer in hPa
     */
    //% shim=bmp280::getPressure
    export function getPressure(): number { return 0 }

    /**
     * Returns the temperature read by the BMP280's temperature sensor in Celcius
     */
    //% shim=bmp280::getTemperature
    export function getTemperature(): number { return 0 }
}