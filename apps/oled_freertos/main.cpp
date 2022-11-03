#include "mbed.h"
#include "Adafruit_SSD1306.h"
#include "FreeRTOS.h"
#include "task.h"

// bitmaps
#include "mbed_logo.h"
#include "unpsjb_logo.h"
#include "expotic.h"
#include "expotic2.h"
#include "freertos_logo.h"
#include "arm_logo.h"

I2C i2c(p28,p27);
Adafruit_SSD1306_I2c display(i2c, p10, SSD_I2C_ADDRESS, 64, 128);

void task(void *p);

int main() 
{    
        display.splash();
        wait(2);

        xTaskCreate( task, "T1", 256, NULL, configMAX_PRIORITIES - 1, NULL );
        vTaskStartScheduler();
        for(;;);
}

void task(void *p) {
    TickType_t xPeriod = 2000;
    TickType_t xLastWake = 0;
    int turn = 0;
    for(;;) {
        display.clearDisplay();
        switch(turn) {
        case 0:
            display.drawBitmap(0, 0, mbed_logo, 128, 64, 1);
            break;
        case 1:
            display.drawBitmap(0, 0, logo_uni, 128, 64, 1);
            break;
        case 2:
            display.drawBitmap(0, 0, expotic3, 128, 64, 1);
            break;
        case 3:
            display.drawBitmap(0, 0, FreeRTOS_logo, 128, 64, 1);
            break;
        case 4:
            display.drawBitmap(0, 0, arm_logo, 128, 64, 1);
            break;
        }
        display.display();
        turn = (turn + 1) % 5;
        vTaskDelayUntil( &xLastWake, xPeriod );
    }
}

