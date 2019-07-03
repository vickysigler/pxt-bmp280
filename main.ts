barometer.init();

basic.forever(() => {
    basic.showNumber(barometer.getPressure());
})