#include "mbed.h"
#include "Adafruit_SSD1306.h"

// bitmaps
#include "mbed_logo.h"
#include "unpsjb_logo.h"

I2C i2c(p9,p10);
Adafruit_SSD1306_I2c display(i2c, p27, SSD_I2C_ADDRESS, 64, 128);

int main() 
{    
        display.splash();
        wait(2);

        display.clearDisplay();
        display.drawBitmap(0, 0, mbed_logo, 128, 64, 1);
        display.display();
        wait(2);

        display.clearDisplay();
        display.drawBitmap(0, 0, logo_uni, 128, 64, 1);
        display.display();
        wait(2);

        uint8_t textSize = 0;

        for(;;) {
                textSize = (textSize + 1) % 6;
                display.clearDisplay();
                display.setTextCursor(0, 0);
                display.setTextSize(textSize);
                display.printf("Hola");
                display.display();
                wait(1);
        }

}
