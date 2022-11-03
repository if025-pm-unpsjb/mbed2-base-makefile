#include "mbed.h"
#include "Adafruit_SSD1306.h"

// bitmaps
#include "mbed_logo.h"
#include "unpsjb_logo.h"
#include "expotic.h"
#include "expotic2.h"

I2C i2c(p28,p27);
Adafruit_SSD1306_I2c display(i2c, p10, SSD_I2C_ADDRESS, 64, 128);

int main() 
{    
        display.splash();
        wait(2);

        for(;;) {
            display.clearDisplay();
            display.drawBitmap(0, 0, mbed_logo, 128, 64, 1);
            display.display();
            wait(2);

            display.clearDisplay();
            display.drawBitmap(0, 0, logo_uni, 128, 64, 1);
            display.display();
            wait(2);

            display.clearDisplay();
            display.drawBitmap(0, 0, expotic3, 128, 64, 1);
            display.display();
            wait(2);

            display.clearDisplay();
            display.setTextCursor(0, 0);
            display.setTextSize(1);
            display.printf("-- ExpoTIC 2022 --");
            display.display();
            wait(1);
        }
}
