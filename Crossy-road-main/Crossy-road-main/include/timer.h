#ifndef TIMER_H
#define TIMER_H

void delay(unsigned int milliseconds); 

void timerInit(int valueMilliSec);

void timerDestroy();

void timerUpdateTimer(int valueMilliSec);

int getTimeDiff(); 

int timerTimeOver();

void timerPrint();

long get_time(); 

#endif // TIMER_H
