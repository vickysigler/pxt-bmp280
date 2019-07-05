# pxt-bmp280

A port of the Seeed-Studio Grove BMP280 library to the micro:bit (as none others seemed to work), however it works with any BMP280 module. The altitude calculation was ommited due to the inherent inaccuracy of using standard pressure to determine altitude. If one is needed however it can easily be coded into the main program using the standard altitude calculation formula.

I used this Grove BMP280 module for development (https://www.seeedstudio.com/Grove-Barometer-Sensor-BMP28-p-2652.html), but as previously stated this code should work with any brand (Adafruit, etc.)

## Functions

### setAddress(address)

```
barometer.setAddress(0x76)
```

Changes the I2C address of the barometer, which defaults to 0x77.

### init()

```
barometer.init()
```

Initialises the barometer, required to start using it. If the address hasn't been changed in advanced, it will use the default address of 0x77.

### getPressure()

```
barometer.getPressure()
```

Returns the current pressure in hPa.

### getTemperature()

```
barometer.getTemperature()
```

Returns the current temperature in celcius.

## TODO

- [x] Add a reference for your blocks here
- [x] Add "icon.png" image (300x200) in the root folder
- [x] Add "- beta" to the GitHub project description if you are still iterating it.
- [x] Turn on your automated build on https://travis-ci.org
- [x] Use "pxt bump" to create a tagged release on GitHub
- [x] On GitHub, create a new file named LICENSE. Select the MIT License template.
- [ ] Get your package reviewed and approved https://makecode.microbit.org/extensions/approval

Read more at https://makecode.microbit.org/extensions

## Supported targets

* for PXT/microbit
(The metadata above is needed for package search.)

