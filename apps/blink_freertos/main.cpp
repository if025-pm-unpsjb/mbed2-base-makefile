#include "mbed.h"
#include "FreeRTOS.h"
#include "task.h"

void task(void *p);
void vUtilsBusyWait( TickType_t ticks );

DigitalOut led1(LED1);

int main()
{
	led1 = 0;
	xTaskCreate( task, "T1", 256, NULL, configMAX_PRIORITIES - 1, NULL );
	vTaskStartScheduler();
	for(;;);
}

void task(void *p) {
	TickType_t xPeriod = 500;
	for(;;) {
		led1 = !led1;
		vUtilsBusyWait(250);
		vTaskDelay( xPeriod );
	}
}

void vUtilsBusyWait( TickType_t ticks )
{
        TickType_t elapsedTicks = 0;
        TickType_t currentTick = 0;
        while ( elapsedTicks < ticks ) {
                currentTick = xTaskGetTickCount();
                while ( currentTick == xTaskGetTickCount() ) {
                        asm("nop");
                }
                elapsedTicks++;
        }
}
