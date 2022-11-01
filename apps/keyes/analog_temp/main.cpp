#include "mbed.h"

AnalogIn sensor(p20);
Serial pc(USBTX, USBRX);

int main()
{
        float r1 = 10000;
        float logr2, r2, t;

        // steinhart-hart coeficients for thermistor
        float c1 = 0.001129148;
        float c2 = 0.000234125;
        float c3 = 0.0000000876741;

        pc.baud(9600);

        while(1)
        {
                float vo = sensor.read();
                r2 = r1 * vo / (1023.0 - vo);
                logr2 = log(r2);
                t = (1.0 / (c1 + c2*logr2 + c3*logr2*logr2*logr2)); // temperature in Kelvin
                t = t - 273.15; //convert Kelvin to Celcius
                pc.printf("%f - %f\n\r", vo, t);
                wait(1);
        }
}
