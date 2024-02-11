// #include "PinNames.h"
// #include "mbed.h"
// #include "L298LIB.h"
// #define EN D10
// #define IN1 D8
// #define IN2 D9
// #define DEG_TO_RAD (4.*atan(1.)/180.)

// L298LIB motor(EN,IN1,IN2);
// int main() {
//     motor.setSpeed(0);
//     uint32_t cnt = 0;
//     while(1) {
//         float t =2*cnt*DEG_TO_RAD;
//         float fvel = sin(t);
//         motor.run(fvel);
//         cnt ++;
//         wait(0.01);
//     }
// }