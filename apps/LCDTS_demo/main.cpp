#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"

int main()
{
    TS_StateTypeDef TS_State;
    uint16_t x, y;
    uint8_t text[30];
    uint8_t status;
    uint8_t idx;
    uint8_t cleared = 0;
    uint8_t prev_nb_touches = 0;

    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);

    BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)"TOUCHSCREEN DEMO", CENTER_MODE);
    HAL_Delay(1000);

    status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
    if (status != TS_OK) {
        BSP_LCD_Clear(LCD_COLOR_RED);
        BSP_LCD_SetBackColor(LCD_COLOR_RED);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)"TOUCHSCREEN INIT FAIL", CENTER_MODE);
    } else {
        BSP_LCD_Clear(LCD_COLOR_GREEN);
        BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)"TOUCHSCREEN INIT OK", CENTER_MODE);
    }

    HAL_Delay(1000);
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

    while(1) {

        BSP_TS_GetState(&TS_State);
        if (TS_State.touchDetected) {
            // Clear lines corresponding to old touches coordinates
            if (TS_State.touchDetected < prev_nb_touches) {
                for (idx = (TS_State.touchDetected + 1); idx <= 5; idx++) {
                    BSP_LCD_ClearStringLine(idx);
                }
            }
            prev_nb_touches = TS_State.touchDetected;

            cleared = 0;

            //sprintf((char*)text, "Touches: %d", TS_State.touchDetected);
            BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);

            for (idx = 0; idx < TS_State.touchDetected; idx++) {
                x = TS_State.touchX[idx];
                y = TS_State.touchY[idx];
                //sprintf((char*)text, "Touch %d: x=%d y=%d    ", idx+1, x, y);
                BSP_LCD_DisplayStringAt(0, LINE(idx+1), (uint8_t *)&text, LEFT_MODE);
            }

            BSP_LCD_DrawPixel(TS_State.touchX[0], TS_State.touchY[0], LCD_COLOR_ORANGE);
        } else {
            if (!cleared) {
                BSP_LCD_Clear(LCD_COLOR_BLUE);
                //sprintf((char*)text, "Touches: 0");
                BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);
                cleared = 1;
            }
        }
    }
}
