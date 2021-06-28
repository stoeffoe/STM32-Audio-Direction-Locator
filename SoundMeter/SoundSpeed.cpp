#include "SoundSpeed.h"
#include <math.h>

float soundSpeedFromTempKelvin(float airTempKelvin){
    return 20.05 * sqrt(airTempKelvin);
}


float soundSpeedFromTempCelsius(float airTempCelsius){
    return  soundSpeedFromTempKelvin(273.15 + airTempCelsius);
}
