#include "mbed.h"
#include "FreeRTOS.h"
#include "task.h"

void task(void *p);

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
		vTaskDelay( xPeriod );
	}
}
