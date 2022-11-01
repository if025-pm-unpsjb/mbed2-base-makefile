#include "mbed.h"

DigitalIn d_sound_sensor(p20);
AnalogIn a_sound_sensor(p15);
DigitalOut led(LED1);
Serial pc(USBTX, USBRX);

int main()
{
        pc.baud(9600);
        while(1)
        {
                float v = a_sound_sensor.read();
                if (v > 0.06) {
                        led = !led;
                        pc.printf("%f\n\r", v);
                }
        }
}
