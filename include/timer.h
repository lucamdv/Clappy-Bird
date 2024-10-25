#ifndef TIMER_H
#define TIMER_H

void delay(unsigned int milliseconds); // Adicione a declaração da função delay

void timerInit(int valueMilliSec);

void timerDestroy();

void timerUpdateTimer(int valueMilliSec);

int getTimeDiff(); // Adicione a declaração da função getTimeDiff

int timerTimeOver();

void timerPrint();

long get_time(); // Adicione a declaração da função get_time

#endif // TIMER_H
