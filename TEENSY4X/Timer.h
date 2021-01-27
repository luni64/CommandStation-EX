#pragma once

#include "../VirtualTimer.h"
#include <Arduino.h>

class Timer : public VirtualTimer
{
 public:
    Timer(int timer_num) {} 

    void initialize()
    {       
        if (timer != nullptr) stop();
        timer = new IntervalTimer();
    }

    void setPeriod(unsigned long mu)
    {     
        microseconds = mu;
    }
    void start()
    {     
        timer->begin(isrCallback, microseconds);        
    }
    void stop()
    {     
        if (timer != nullptr)
        {
            timer->end();    //this will release the timer, I assume that the lib doesn't call start after stop without initializing.
            delete timer;
            timer = nullptr; // If so -> start would error. In case the lib wants to stop/start something more elaborate needs to be done here
        }
    }

    void attachInterrupt(void (*isr)())
    {        
        isrCallback = isr;
    }

    void detachInterrupt()
    {
        stop();
        isrCallback = nullptr;
    }

 private:
    uint32_t microseconds;
    IntervalTimer* timer = nullptr;
    void (*isrCallback)();
};

extern Timer TimerA;
extern Timer TimerB;
extern Timer TimerC;
extern Timer TimerD;
