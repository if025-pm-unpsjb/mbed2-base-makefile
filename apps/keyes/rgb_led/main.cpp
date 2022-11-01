#include "mbed.h"

DigitalOut ledR(p15);
DigitalOut ledG(p16);
DigitalOut ledB(p19);

int main()
{
        ledR = 0;
        ledG = 0;
        ledB = 0;
        while(1)
        {
                ledR = 1;
                wait(1);
                ledR = 0;
                ledG = 1;
                wait(1);
                ledG = 0;
                ledB = 1;
                wait(1);
                ledB = 0;
        }
}
