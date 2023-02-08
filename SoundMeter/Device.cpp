#include "Device.h"

#include <STM32ADC.h>


STM32ADC myADC(ADC1);

void setupDMA(uint8_t* pins, uint16_t* analogOutputs, uint8_t numOfPins){
    myADC.calibrate();      // Internal self-calibration
    
    for (uint8_t j = 0; j <numOfPins; j++) 
        pinMode(pins[j], INPUT_ANALOG);

    myADC.setSampleRate(SAMPLERATE);  
    myADC.setScanMode(); 
    myADC.setPins(pins, numOfPins);
    myADC.setContinuous();      // Continuously read from the pins
    
    //Set the DMA transfer for the ADC. 
    //In this case we want to increment the memory side and run it in circular mode
    //By doing this, we can read the last value sampled from the channels by reading the memory addresses analogOutputs array pointer
    myADC.setDMA(analogOutputs, numOfPins, (DMA_MINC_MODE | DMA_CIRC_MODE), NULL);
    myADC.startConversion();  
}


float ADCtoVolts(float ADCValue){
     return ((ADCValue * SUPPLY_VOLTAGE) / ADC_MAX);
}
