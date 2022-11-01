#include "mbed.h"

DigitalIn tilt(p17);
DigitalOut led(LED1);
Serial pc(USBTX, USBRX);

int main()
{
        pc.baud(9600);
        while(1)
        {
                if (tilt.read() > 0) {
                        led = 1;
                } else {
                        led = 0;
                }
                wait(1);
        }
}
