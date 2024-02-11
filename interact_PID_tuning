#include "PinNames.h"
#include "QEncoder.h"
#include "L298LIB.h"
#include "RawSerial.h"
#include "encoder_names.h"
#include "PID.h"
#define EN D10
#define IN1 D8
#define IN2 D9
#define DEG_TO_RAD (4.*atan(1.)/180.)
#define SAMPLING_INTERVAL 1000
#define PRINT_INTERVAL 10000
#define dt (SAMPLING_INTERVAL/100000.f)

float Kp =3.0f;float Ki =0.0f;float Kd =0.1f; float I_max = 100.0f;
PIDBasic pid(Kp,Ki, Kd,I_max); // kp, ki, kd, imax
L298LIB motor(EN,IN1,IN2);
QEncoder  enco(D2,D3);
RawSerial pc(USBTX,USBRX,230400);
Timer tmr, tmr_prt;

float r= 0.0f, y = 0.0f;
float u;
volatile bool gotPacket = false;
volatile float data[3];

void serialEvent()
{   
    static char serialInBuffer[32];
    static int data_cnt= 0, buff_cnt = 0;
    if(pc.readable())
    {
        char byteIn = pc.getc();
        if(byteIn == ',')
        {
            serialInBuffer[buff_cnt] = '\0';
            data[data_cnt++] = atof(serialInBuffer); // string을 float으로 변환
            buff_cnt = 0;
        }
        else if(byteIn == '\n')
        {
            serialInBuffer[buff_cnt] = '\0';
            data[data_cnt] = atof(serialInBuffer);
            buff_cnt =0 ; data_cnt = 0;
            gotPacket = true;
        }
        else
        {
            serialInBuffer[buff_cnt++] = byteIn;
        }
    }
}

int main() 

{   float kp_prt; float ki_prt;float kd_prt;
    pid.GetPID(kp_prt, ki_prt, kd_prt);
    motor.setSpeed(0);
    uint32_t cnt = 0;
    tmr.start(); tmr_prt.start();
    enco.init();
    enco.setCount(0);
    pc.attach(&serialEvent);
    while(1) 
    {
        if(gotPacket)
        {
            gotPacket = false;
            Kp = data[0];Ki = data[1];Kd = data[2];
            pid.SetNewGain(Kp,Ki, Kd);
            pid.GetPID(kp_prt, ki_prt, kd_prt);
        }

        if(tmr.read_us()>SAMPLING_INTERVAL)
        {
            tmr.reset();
            y = enco.getCount()*Encoder::ratio; // encoder value
            u = pid.computePID(r,y,dt);
            motor.run(u/255.f); // mapping함수가 필요해보임.
            cnt ++;
            if(cnt%2000==0)
            {
                if(r==0.0f) r = 180.f;
                else r = 0.0f;
            }
        }
        if(tmr_prt.read_us() > PRINT_INTERVAL){
            tmr_prt.reset();
            pc.printf("ref %.1f, output : %.1f,error : %.1f, kp : %.2f, ki : %.2f, kd : %.2f\n", r,y,u/255.f,kp_prt, ki_prt, kd_prt
            );
            
        }
    }
}
