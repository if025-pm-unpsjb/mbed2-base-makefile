#include "mbed.h"

AnalogIn heartbeat(p16);
Serial pc(USBTX, USBRX);

int main()
{
        pc.baud(9600);
        while(1)
        {
                pc.printf("%d\n\r", heartbeat.read());
                wait(1);
        }
}
