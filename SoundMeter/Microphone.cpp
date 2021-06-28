#include "Microphone.h"
#include "Device.h"


Microphone :: Microphone(uint16_t* adcReadAddr) {
    this -> adcReadAddr = adcReadAddr;
    resetSamples();
}


void Microphone :: takeSample() {
    if (*adcReadAddr > signalMax) {
        signalMax = *adcReadAddr;  
    } else if (*adcReadAddr < signalMin) {
        signalMin = *adcReadAddr;
    }
}


float Microphone :: getPeak(){
    return signalMax - signalMin;
}


float Microphone :: getPeakDecibel() {
    return voltsToDecibel(ADCtoVolts(getPeak()));
}


uint32_t Microphone :: getPeakTimestamp() {
    return peakTimestamp;
}


void Microphone :: resetSamples() {  // reset all values
    signalMax = ADCMIN;
    signalMin = ADCMAX;
    peakTimestamp = 0;
}


float Microphone :: voltsToDecibel(float volts) {
    volts = volts * 0.7071;  // convert to RMS voltage;
    return log10(volts / 0.00631) * 20 + 94 - 44 - 5;
}
