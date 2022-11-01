#include "mbed.h"

DigitalIn sensor(p16);
DigitalOut led(LED1);

int main()
{
        led = 0;
        while(1)
        {
                if (sensor.read()) {
                        led = 0;
                } else {
                        led = 1;
                }
        }
}
