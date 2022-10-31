#include "mbed.h"
#include "max7219.h"

DigitalOut led1(LED1);

//SPI spi(p5, p6, p7); // mosi, miso, sclk
//Max7219 max7219(&spi, p19);
Max7219 max7219(p11,p12,p13,p19);

// happy face
int hf[8] = {0b00111100, 0b01000010, 0b10010101, 0b10100001, 0b10100001, 0b10010101, 0b01000010, 0b00111100};

int main()
{
        max7219_configuration_t cfg = {
                        .device_number = 0,
                        .decode_mode = 0,
                        .intensity = Max7219::MAX7219_INTENSITY_5,
                        .scan_limit = Max7219::MAX7219_SCAN_8
        };

        max7219.init_device(cfg);
        max7219.enable_device(1);

        wait(5);

        max7219.device_all_off(1);
        for (int i = 1; i <= 8; i++) {
                max7219.write_digit(1, i, hf[i-1]);
        }

    while(1)
    {
        led1 = 0;
        wait(0.5);
        led1 = 1;
        wait(2);
    }
}
