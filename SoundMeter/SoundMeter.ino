#include "Microphone.h"
#include "Device.h"
#include "SignalProcessing.h"
#include "SoundSpeed.h"


#define NUM_OF_MICROPHONES 2
#define BUFSIZE 500

bool dataReady = false;

uint8_t soundSensPins[NUM_OF_MICROPHONES] = {PA0, PA1};

uint16_t analogOutputs[NUM_OF_MICROPHONES];


int16_t signals[NUM_OF_MICROPHONES][BUFSIZE];

Microphone soundSensorA((uint16_t*) analogOutputs);
Microphone soundSensorB((uint16_t*) analogOutputs+1);


void setup() {
  delay(1000);
      // Setup microphone sampling timer
    Timer2.setMode(TIMER_CH1, TIMER_OUTPUTCOMPARE);
    Timer2.setPeriod(20); // 20 microseconds | 50kHz
    Timer2.setCompare(TIMER_CH1, 1);     
    Timer2.attachInterrupt(TIMER_CH1, sampleInterrupt);
    
    Serial.begin(2000000);
    setupDMA(soundSensPins, analogOutputs, NUM_OF_MICROPHONES); // Direct Memory Access for high frequency sampling

}

void loop() {

    if (dataReady) {
        dataReady = false;

        filterData(signals[0], BUFSIZE);
        filterData(signals[1], BUFSIZE);

        Serial.println((((float)calculateDelay(signals[0],signals[1],BUFSIZE, 400)/50000.0)*343.4));
        delay(200);

        Timer2.resume();
    }



}



void sampleInterrupt(){
    static bool recording = false;
    static uint16_t sampleIndex = 0;
    
    if (recording){
        for (uint8_t i=0; i<NUM_OF_MICROPHONES; i++){
            signals[i][sampleIndex] = analogOutputs[i];
        }
        sampleIndex++;

        if (sampleIndex >= BUFSIZE){
            recording = false;
            dataReady = true;
            sampleIndex = 0;
            Timer2.pause();
        }
        
    } else {

        for (uint8_t i=0; i<NUM_OF_MICROPHONES; i++){
            signals[i][sampleIndex] = analogOutputs[i];
            
            if (recording == false && signals[i][sampleIndex] > TRESHOLD){
                recording = true;
            }
            
        }
    }
}
