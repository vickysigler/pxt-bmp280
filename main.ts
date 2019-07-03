bmp280.init();

basic.forever(() => {
    basic.showNumber(bmp280.getPressure());
})