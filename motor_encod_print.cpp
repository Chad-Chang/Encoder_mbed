#include "PinNames.h"
#include "mbed.h"
#include "QEncoder.h"
#include "L298LIB.h"
#include "encoder_names.h"
#define EN D10
#define IN1 D8
#define IN2 D9
#define DEG_TO_RAD (4.*atan(1.)/180.)


DigitalOut led1(LED1);
L298LIB motor(EN,IN1,IN2);
QEncoder  enco(D2,D3);
int main() {
    motor.setSpeed(0);
    uint32_t cnt = 0;
    enco.init();
    enco.setCount(0);
    while(1) {
        float t =2*cnt*DEG_TO_RAD;
        float fvel = sin(t);
        motor.run(fvel);
        cnt ++;
        printf("count= %f , %d\n",float(enco.getCount()) * Encoder::ratio, enco.getErrorCount());
        wait(0.01);
    }
}
