#include "Microphone.h"
#include "Device.h"
#include "cross_correlation.h"
#include "soundSpeed.h"


#define NUMOFSENSORS 2
#define BUFSIZE 500

bool dataReady = false;

uint8_t soundSensPins[NUMOFSENSORS] = {PA0, PA1};

uint16_t analogOutputs[NUMOFSENSORS];


int16_t signals[NUMOFSENSORS][BUFSIZE];

Microphone soundSensorA((uint16_t*) analogOutputs);
Microphone soundSensorB((uint16_t*) analogOutputs+1);





void setup() {
  delay(1000);
      // Setup Sample Timer
    Timer2.setMode(TIMER_CH1, TIMER_OUTPUTCOMPARE);
    Timer2.setPeriod(10); // in microseconds
    Timer2.setCompare(TIMER_CH1, 1);     
    Timer2.attachInterrupt(TIMER_CH1, sampleInterrupt);
    
    Serial.begin(2000000);
    setupDMA(soundSensPins, analogOutputs, NUMOFSENSORS);

//    uint16_t s1[] = {0,0,1,2,1,0};
//    uint16_t s2[] = {0,0,0,1,2,1};
//
//    delay(1000);
//    Serial.println(calculateDelay(s1,s2,6,5));
}

void loop() {



    if (dataReady) {
        dataReady = false;

//        for (uint16_t i=0; i<BUFSIZE ; i++){
//            Serial.print(signals[0][i]);
//            Serial.print(',');
//
//        }
//        Serial.println();
//        for (uint16_t i=0; i<BUFSIZE ; i++){
//            Serial.print(signals[1][i]);
//            Serial.print(',');
//
//        }

        filterData(signals[0], BUFSIZE);
        filterData(signals[1], BUFSIZE);
//       Serial.println(calculateDelay(signals[0],signals[1],BUFSIZE, 70));
        Serial.println(degrees(acos((((float)calculateDelay(signals[0],signals[1],BUFSIZE, 70)/100000.0)*343.4)/0.2)));


        Timer2.resume();
    }



}



void sampleInterrupt(){
    static bool recording = false;
    static uint16_t sampleIndex = 0;
    
    if (recording){
        for (uint8_t i=0; i<NUMOFSENSORS; i++){
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

        for (uint8_t i=0; i<NUMOFSENSORS; i++){
            signals[i][sampleIndex] = analogOutputs[i];
            
            if (recording == false && signals[i][sampleIndex] > TRESHOLD){
                recording = true;
            }
            
        }
    }
}
