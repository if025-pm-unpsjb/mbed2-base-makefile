#include "mbed.h"
#include "LCD_DISCO_F746NG.h"

LCD_DISCO_F746NG lcd;
DigitalOut led1(LED1);

int main()
{
        lcd.Clear(LCD_COLOR_GREEN);
        lcd.SetTextColor(LCD_COLOR_BLUE);
        lcd.DrawRect(10, 20, 50, 50);

        while(1)
        {
                led1 = 0;
                wait(0.5);
                led1 = 1;
                wait(2);
        }
}
