#include "SoundSpeed.h"
#include <math.h>

const float KELVIN_CELCIUS_OFFSET = 273.15f;
const float SOUND_SPEED_CONSTANT = 20.05f;

float soundSpeedFromTempKelvin(float airTemperatureKelvin){
    return SOUND_SPEED_CONSTANT * sqrt(airTemperatureKelvin);
}

float soundSpeedFromTempCelsius(float airTemperatureCelsius){
    return soundSpeedFromTempKelvin(KELVIN_CELCIUS_OFFSET + airTemperatureCelsius);
}
