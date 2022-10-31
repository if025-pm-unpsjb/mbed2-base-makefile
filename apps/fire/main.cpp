/**
 * Fire
 * Ver: - https://fabiensanglard.net/doom_fire_psx/index.html
 *      - https://github.com/fabiensanglard/DoomFirePSX/blob/master/flames.html
 */
#include "mbed.h"
#include "LCD_DISCO_F746NG.h"

LCD_DISCO_F746NG lcd;

uint32_t colors[] = {
                0xFF070707,
                0xFF1F0707,
                0xFF2F0F07,
                0xFF470F07,
                0xFF571707,
                0xFF671F07,
                0xFF771F07,
                0xFF8F2707,
                0xFF9F2F07,
                0xFFAF3F07,
                0xFFBF4707,
                0xFFC74707,
                0xFFDF4F07,
                0xFFDF5707,
                0xFFDF5707,
                0xFFD75F07,
                0xFFD75F07,
                0xFFD7670F,
                0xFFCF6F0F,
                0xFFCF770F,
                0xFFCF7F0F,
                0xFFCF8717,
                0xFFC78717,
                0xFFC78F17,
                0xFFC7971F,
                0xFFBF9F1F,
                0xFFBF9F1F,
                0xFFBFA727,
                0xFFBFA727,
                0xFFBFAF2F,
                0xFFB7AF2F,
                0xFFB7B72F,
                0xFFB7B737,
                0xFFCFCF6F,
                0xFFDFDF9F,
                0xFFEFEFC7,
                0xFFFFFFFF
};

#define WIDTH 480
#define HEIGHT 272

char firePixels[WIDTH*HEIGHT];

int main()
{
        lcd.Clear(LCD_COLOR_BLACK);
        lcd.SetBackColor(LCD_COLOR_BLACK);
        lcd.SetTextColor(LCD_COLOR_WHITE);
        lcd.DisplayStringAt(0, LINE(5), (uint8_t *)"FIRE!", CENTER_MODE);

        wait(5);

        for(int i = 0; i < WIDTH*HEIGHT; i++) {
                firePixels[i] = 0;
        }
        for(int i = 0; i < WIDTH; i++) {
                firePixels[(HEIGHT-1)*WIDTH + i] = 36;
        }

        while(1)
        {
                for (int x = 0; x < WIDTH; x++) {
                        for (int y = 1; y < HEIGHT; y++) {
                                int src = y * WIDTH + x;
                                uint32_t pixel = firePixels[src];
                                if (pixel == 0) {
                                        firePixels[src - WIDTH] = 0;
                                } else {
                                        int r = (rand() % 3) & 3;
                                        int dst = src - r + 1;
                                        firePixels[dst - WIDTH] = pixel - (r&1);
                                }
                        }
                }

                for (int y = 0; y < 272; y++) {
                        for (int x = 0; x < 480; x++) {
                                int index = firePixels[y * WIDTH  + x];
                                lcd.DrawPixel(x, y, colors[index]);
                        }
                }

                //wait(0.01);
        }
}
