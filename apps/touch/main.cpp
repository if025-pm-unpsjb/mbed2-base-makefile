#include "mbed.h"
#include "LCD_DISCO_F746NG.h"
#include "TS_DISCO_F746NG.h"

#define PALETTE_SIZE 25

LCD_DISCO_F746NG lcd;
TS_DISCO_F746NG ts;
DigitalOut led1(LED1);

uint32_t paleta[] = {
LCD_COLOR_BLUE,
LCD_COLOR_GREEN,
LCD_COLOR_RED,
LCD_COLOR_CYAN,
LCD_COLOR_MAGENTA,
LCD_COLOR_YELLOW,
LCD_COLOR_LIGHTBLUE,
LCD_COLOR_LIGHTGREEN,
LCD_COLOR_LIGHTRED,
LCD_COLOR_LIGHTCYAN,
LCD_COLOR_LIGHTMAGENTA,
LCD_COLOR_LIGHTYELLOW,
LCD_COLOR_DARKBLUE,
LCD_COLOR_DARKGREEN,
LCD_COLOR_DARKRED,
LCD_COLOR_DARKCYAN,
LCD_COLOR_DARKMAGENTA,
LCD_COLOR_DARKYELLOW,
LCD_COLOR_WHITE,
LCD_COLOR_LIGHTGRAY,
LCD_COLOR_GRAY,
LCD_COLOR_DARKGRAY,
LCD_COLOR_BLACK,
LCD_COLOR_BROWN,
LCD_COLOR_ORANGE
};

int main()
{
        TS_StateTypeDef TS_State;

        lcd.Clear(LCD_COLOR_GREEN);
        lcd.SetTextColor(LCD_COLOR_BLUE);
        lcd.DrawRect(10, 20, 50, 50);

        int i=0;

        while(1)
        {
                ts.GetState(&TS_State);
                if (TS_State.touchDetected) {
                        lcd.Clear(paleta[(i++)%25]);
                }
        }
}
