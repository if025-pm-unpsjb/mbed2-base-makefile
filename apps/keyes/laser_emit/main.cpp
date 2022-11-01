#include "mbed.h"

DigitalOut laser(p17);
DigitalOut led(LED1);

int main()
{
        laser = 0;
        led = 0;
        while(1)
        {
                wait(1);
                laser = 1;
                led = 1;
                wait(2);
                laser = 0;
                led = 0;
        }
}
