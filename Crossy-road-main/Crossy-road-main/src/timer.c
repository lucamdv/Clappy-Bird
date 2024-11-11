#include "timer.h"
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>  

static struct timeval timer, now;
static int timerDelay = -1; 

long get_time() {
    return getTimeDiff(); 
}

void delay(unsigned int milliseconds) {
    usleep(milliseconds * 1000); 
}

void timerInit(int valueMilliSec) {
    timerDelay = valueMilliSec;
    gettimeofday(&timer, NULL);
}

void timerDestroy() {
    timerDelay = -1;
}

void timerUpdateTimer(int valueMilliSec) {
    timerDelay = valueMilliSec;
    gettimeofday(&timer, NULL);
}

int getTimeDiff() {
    gettimeofday(&now, NULL);
    long diff = (((now.tv_sec - timer.tv_sec) * 1000000) + now.tv_usec - timer.tv_usec) / 1000;
    return (int)diff;
}

int timerTimeOver() {
    int ret = 0;

    if (getTimeDiff() > timerDelay) {
        ret = 1;
        gettimeofday(&timer, NULL);
    }

    return ret;
}

void timerPrint() {
    printf("Timer: %d\n", getTimeDiff());
}
