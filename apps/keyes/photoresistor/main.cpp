/* KY018 Photo resistor module */
#include "mbed.h"

AnalogIn sensor(p20);
Serial pc(USBTX, USBRX);

int main()
{
        pc.baud(9600);
        while(1)
        {
                float value = sensor.read();
                pc.printf("%f\n\r", value);
                wait(1);
        }
}
