#include "Microphone.h"
#include "Device.h"

#define NUMOFSENSORS 2


uint8_t soundSensPins[NUMOFSENSORS] = {PA0, PA1};

uint16_t analogOutputs[NUMOFSENSORS];

Microphone soundSensorA((uint16_t*) analogOutputs);
Microphone soundSensorB((uint16_t*) analogOutputs+1);
//SoundSensor soundSensorB(dataPoints[]);

void setup()
{
    Serial.begin(2000000);
    setupDMA(soundSensPins, analogOutputs, NUMOFSENSORS);
}


void loop()
{
   
    for (int i=0; i<500000; i++) {
        soundSensorA.takeSample();
        soundSensorB.takeSample();
    }

//    Serial.println(soundSensorA.getPeakTimestamp());
    if (soundSensorA.getPeakTimestamp() && soundSensorB.getPeakTimestamp()){
        int64_t res = (int64_t)soundSensorA.getPeakTimestamp() - (int64_t)soundSensorB.getPeakTimestamp();
//        if (res < 1000 && res > -1000){
            Serial.println(res);
//        }
//        Serial.println();
    }
    Serial.println(".");
//    Serial.println(soundSensorA.getPeakTimestamp());


//    uint16_t sa = analogOutputs[0];
//    uint16_t sb = analogOutputs[1];
//
//Serial.print(3500);
//Serial.print(',');
//Serial.print(1500);
//Serial.print(',');
//    Serial.print(sa);
//    Serial.print(',');
//    Serial.println(sb);
//    soundSensorA.takeSample();
//    Serial.print(2048);
//    Serial.print(',');
//    Serial.println(analogOutputs[0]);
////    Serial.print(',');
////    Serial.print(3500);
////    Serial.print(',');
////    Serial.println(1500);
//    delayMicroseconds(5);
////    Serial.println(soundSensorA.getPeakDecibel());
soundSensorB.resetSamples();
    soundSensorA.resetSamples();

}
