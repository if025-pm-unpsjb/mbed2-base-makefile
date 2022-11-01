#include "mbed.h"

DigitalIn d_magnetic_sensor(p17);
AnalogIn a_magnetic_sensor(p16);
DigitalOut led(LED1);
Serial pc(USBTX, USBRX);

int main()
{
        pc.baud(9600);
        int dVal;
        while(1)
        {
                dVal = d_magnetic_sensor.read();
                if (dVal > 0) {
                        led = 1;
                        pc.printf("%d -- %f\n\r", dVal, a_magnetic_sensor.read());
                } else {
                        led = 0;
                }
                wait(1);
        }
}
