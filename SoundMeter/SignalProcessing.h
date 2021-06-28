#ifndef SIGNALPROCESSING_H
#define SIGNALPROCESSING_H

#include <stdint.h>

int16_t calculateDelay(int16_t s1[], int16_t s2[], uint16_t n, uint16_t maxDelay);
void filterData(int16_t data[], uint16_t n);

#endif /*SIGNALPROCESSING_H*/
