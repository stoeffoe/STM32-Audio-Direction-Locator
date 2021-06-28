#ifndef MICROPHONE_H
#define MICROPHONE_H

#include <Arduino.h>

#define TRESHOLD 2100

class Microphone {

    private:
        uint16_t* adcReadAddr;
        uint16_t signalMax;
        uint16_t signalMin;
        uint32_t peakTimestamp;

    public:
        Microphone(uint16_t* adcReadAddr);
        void takeSample();
        float getPeak();
        float getPeakDecibel();
        uint32_t getPeakTimestamp();
        void resetSamples();
        static float voltsToDecibel(float volts);
};

#endif /*MICROPHONE_H*/
