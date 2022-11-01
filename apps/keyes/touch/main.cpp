#include "mbed.h"

DigitalIn d_touch_sensor(p17);
AnalogIn a_touch_sensor(p16);
DigitalOut led(LED1);
Serial pc(USBTX, USBRX);

int main()
{
        pc.baud(9600);
        while(1)
        {
                int v = d_touch_sensor.read();
                if (v > 0) {
                        led = !led;
                }
                pc.printf("%d -- %d\n\r", v, a_touch_sensor.read());
                wait(1);
        }
}
