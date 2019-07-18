function getReadings(): {pressure: number, temp: number} {
    return {
        pressure: barometer.getPressure(),
        temp: barometer.getTemperature()
    }
}

// Test that the barometer returns nothing with an invalid address
barometer.setAddress(0x00);
barometer.init();

let readings = getReadings();
control.assert(readings.pressure === 0);
control.assert(readings.temp === 0);

// Test that the barometer returns readings with the correct address
barometer.setAddress(0x77);
barometer.init();

readings = getReadings();
control.assert(readings.pressure !== 0);
control.assert(readings.temp !== 0);