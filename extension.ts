/**
 * Provides support for the BMP280 barometer module.
 */
//% color=#7300ff weight=0 icon="\uf0e4" block="Barometer"
namespace barometer {
    /**
     * Initialises the BMP280 module
     */
    //% block
    //% shim=bmp280::init
    export function init(): void { return }

    /**
     * Changes the default I2C address from 0x77 to the provided address
     * @param The I2C address to use; eg: 0x76
     */
    //% block
    //% shim=bmp280::setAddress
    export function setAddress(address: number): void { return }

    /**
     * Returns the pressure read by the BMP280's barometer in hPa
     */
    //% block="pressure"
    //% shim=bmp280::getPressure
    export function getPressure(): number { return 0 }

    /**
     * Returns the temperature read by the BMP280's temperature sensor in Celcius
     */
    //% block="temperature"
    //% shim=bmp280::getTemperature
    export function getTemperature(): number { return 0 }
}