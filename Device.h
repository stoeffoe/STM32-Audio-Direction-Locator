#ifndef DEVICE_H
#define DEVICE_H

#include <Arduino.h>

#define ADCMAX 4096
#define ADCMIN 0
#define SUPPLYVOLTAGE 3.3

#define SAMPLERATE ADC_SMPR_7_5

void setupDMA(uint8_t* pins, uint16_t* dataPoints, uint8_t numOfPins);

float ADCtoVolts(float ADCValue);

#endif /*DEVICE_H*/
