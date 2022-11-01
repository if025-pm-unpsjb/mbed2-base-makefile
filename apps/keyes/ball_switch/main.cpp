#include "mbed.h"

DigitalIn tilt(p17);
DigitalOut led(LED1);
Serial pc(USBTX, USBRX);

int main()
{
        led = 0;
        while(1)
        {
                if (tilt) {
                        pc.printf("shock!\n\r");
                        led = !led;
                }
                wait(1);
        }
}
