#pragma once

#include "../VirtualTimer.h"
#include "TeensyTimerTool.h"


class Timer : public VirtualTimer
{
 public:
    Timer(int timer_num) {}

    void initialize()
    {
    }

    void setPeriod(unsigned long mu)
    {
        microseconds = mu;
    }
    void start()
    {        
        if (timer == nullptr)
        {
            timer = new TeensyTimerTool::PeriodicTimer(TeensyTimerTool::TCK); // change to any other timer here
            timer->begin(isrCallback, microseconds);
        } else
        {
            timer->start();
        }
    }
    
    void stop()
    {
        timer->stop();
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
    TeensyTimerTool::PeriodicTimer* timer = nullptr;
    void (*isrCallback)();
};

extern Timer TimerA;
extern Timer TimerB;
extern Timer TimerC;
extern Timer TimerD;
