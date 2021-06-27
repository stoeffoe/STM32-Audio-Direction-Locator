#include "cross_correlation.h"

int16_t calculateDelay(int16_t s1[], int16_t s2[], uint16_t n, uint16_t maxDelay){
    
    float corr, highestCorr=0;
    int mostProbableDelay;

    for (int16_t d=-maxDelay; d<=maxDelay; d++) {
        uint16_t starti;
        uint16_t endi;
        
        if (d < 0){
            starti = -d;
            endi = n;
        } else {
            starti = 0;
            endi = n-d;
        }
        
        corr = 0;
        for (uint16_t i=starti; i<endi; i++) {
            corr += s1[i] * s2[i+d];
        }
        
        if (corr > highestCorr){
            mostProbableDelay = d;
            highestCorr = corr;
        }
   }
   
   return mostProbableDelay;
}

void filterData(int16_t data[], uint16_t n) {
    uint16_t UpperCutoff = 2100;
    uint16_t LowerCuttoff = 2000; 
    uint16_t center = 2048;
    
    for (int i=0; i<n; i++){
        if (data[i] > LowerCuttoff && data[i] < UpperCutoff) {
            data[i] = 0;
        } else {
            data[i] -= center;
        }
    }
}
