#ifndef CROSS-CORRELATION_H
#define CROSS-CORRELATION_H

#include <stdint.h>

int16_t calculateDelay(float s1[], float s2[], uint16_t n, uint16_t maxDelay){
    
    float corr, highestCorr=0;
    int mostProbableDelay;

    for (int16_t delay=-maxDelay; delay<=maxDelay; delay++) {
        uint16_t starti;
        uint16_t endi;
        
        if (delay < 0){
            starti = -delay;
            endi = n;
        } else {
            starti = 0;
            endi = n-delay;
        }
        
        corr = 0;
        for (uint16_t i=starti; i<endi; i++) {
            corr += s1[i] * s2[i+delay];
        }
        
        if (corr > highestCorr){
            mostProbableDelay = delay;
            highestCorr = corr;
        }
   }
   
   return mostProbableDelay;
}


#endif /*CROSS-CORRELATION_H*/
