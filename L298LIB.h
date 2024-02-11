#ifndef L298LIB_h
#define L298LIB_h
#include "mbed.h"

class L298LIB{
    public:
        L298LIB(PinName pinEnable, PinName pinIN1, PinName);
        void setSpeed(float pwmVal);
        float getSpeed();
        void forward();
        void backward();
        void stop();
        void run(float velocity);
        
    private:
        PwmOut pwm_;
        DigitalOut pinIN1_;
        DigitalOut pinIN2_;
};

#endif

