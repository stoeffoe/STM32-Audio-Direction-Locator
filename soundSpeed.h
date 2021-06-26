#ifndef SOUNDSPEED_H
#define SOUNDSPEED_H

float soundSpeedFromTempKelvin(float airTempKelvin){
    return 331.3 * sqrt(1+ airTempKelvin);
}

float soundSpeedFromTempCelsius(float airTempCelsius){
    return  soundSpeedFromTempKelvin(273.15 + airTempCelsius);
}

#endif /*SOUNDSPEED_H*/
