#include "mbed.h"

DigitalIn magnetic_sensor(p16);
DigitalOut led(LED1);
Serial pc(USBTX, USBRX);

int main()
{
        pc.baud(9600);
        while(1)
        {
                if (magnetic_sensor.read() > 0) {
                        led = 1;
                } else {
                        led = 0;
                }
                pc.printf("%d\n\r", magnetic_sensor.read());
                wait(1);
        }
}
