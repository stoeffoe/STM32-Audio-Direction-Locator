#ifndef DEVICE_H
#define DEVICE_H

#include <Arduino.h>

#define ADC_MAX 4095
#define ADC_MIN 0
#define SUPPLY_VOLTAGE 3.3

#define SAMPLERATE ADC_SMPR_7_5

void setupDMA(uint8_t* pins, uint16_t* dataPoints, uint8_t numOfPins);

float ADCtoVolts(float ADCValue);

#endif /*DEVICE_H*/
