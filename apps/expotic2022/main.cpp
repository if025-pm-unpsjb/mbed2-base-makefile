/*****************************************************************************
 *
 * Example 5
 *
 * This program consist of 4 real-time periodic tasks and 2 aperiodic tasks,
 * the later only scheduled when there is available slack in the system. All
 * the tasks write a string with some data to to the serial port, when
 * starting and finishing each instance.
 *
 * Before writing to the serial port, the tasks try to take a shared mutex.
 * This could lead to the following problem: when an aperiodic task has taken
 * the mutex and then the available slack depletes, the periodic tasks can't
 * take the mutex, and a missed deadline will occur. To avoid this situation,
 * a timeout is used when the periodic tasks is waiting to obtain the mutex.
 *
 * This program requires FreeRTOS v10.0.0 or later.
 *
 * Created on: 19 jul. 2020
 *     Author: Francisco E. Páez
 *
 *****************************************************************************/

/*****************************************************************************
 * Includes
 ****************************************************************************/
#include "mbed.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "slack.h"
#include "utils.h"
#include "common-mbed.h"
#include "Adafruit_SSD1306.h"

// bitmaps
//#include "mbed_logo.h"
#include "unpsjb_logo.h"
#include "expotic2.h"
#include "freertos_logo.h"
#include "arm_logo.h"

/*****************************************************************************
 * Macros and definitions
 ****************************************************************************/
#define TASK_CNT 4
#define TASK_1_WCET 1000
#define TASK_2_WCET 1000
#define TASK_3_WCET 1000
#define TASK_4_WCET 1000
#define TASK_1_PERIOD 3000
#define TASK_2_PERIOD 4000
#define TASK_3_PERIOD 6000
#define TASK_4_PERIOD 12000
#define TASK_1_PRIO configMAX_PRIORITIES - configSS_SLACK_PRIOS - 1
#define TASK_2_PRIO configMAX_PRIORITIES - configSS_SLACK_PRIOS - 2
#define TASK_3_PRIO configMAX_PRIORITIES - configSS_SLACK_PRIOS - 3
#define TASK_4_PRIO configMAX_PRIORITIES - configSS_SLACK_PRIOS - 4
#define ATASK_WCET 2000
#define ATASK_MAX_DELAY 4000
#define ATASK_1_PRIO configMAX_PRIORITIES - 1
#define ATASK_2_PRIO configMAX_PRIORITIES - 2
#define MUTEX_TIMEOUT 10

#define BAUDRATE 9600

/*****************************************************************************
 * Private data declaration
 ****************************************************************************/
/* None */

/*****************************************************************************
 * Public data declaration
 ****************************************************************************/
/* None */

/*****************************************************************************
 * Private functions declaration
 ****************************************************************************/
static void vPeriodicTask( void* params );
static void vAperiodicTask( void* params );
static void vCommonPrintSlacks( char s, int32_t * slackArray, SsTCB_t *pxTaskSsTCB );

/*****************************************************************************
 * Private data
 ****************************************************************************/
static TaskHandle_t task_handles[ TASK_CNT ];
static TaskHandle_t xApTaskHandle1, xApTaskHandle2;
static int32_t slackArray[ 6 ];

/*****************************************************************************
 * Public data
 ****************************************************************************/
SemaphoreHandle_t xMutex = NULL;
Serial pc( USBTX, USBRX );
#ifdef TARGET_MBED_LPC1768
DigitalOut leds[] = { LED1, LED2, LED3, LED4 };
#endif
#ifdef TARGET_STM32F7
DigitalOut leds[] = { LED1, LED1, LED1, LED1 };
#endif

DigitalOut ledR(p23);

#if TZ == 1
traceString slack_channel;
#endif

I2C i2c(p28,p27);
Adafruit_SSD1306_I2c display(i2c, p10, SSD_I2C_ADDRESS, 64, 128);

/*****************************************************************************
 * Private functions
 ****************************************************************************/
static void vCommonPrintSlacks( char s, int32_t * slackArray, SsTCB_t *pxTaskSsTCB )
{
    pc.printf("%s [%3d] %c\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n\r",
            pcTaskGetTaskName(NULL), pxTaskSsTCB->uxReleaseCount, s,
            slackArray[0], slackArray[1], slackArray[2],
            slackArray[3], slackArray[4], slackArray[5],
            pxTaskSsTCB->xCur);
}
/*-----------------------------------------------------------*/

static void vAperiodicTask( void* params )
{
    SsTCB_t *pxTaskSsTCB;

    int id = (int) params;

    pxTaskSsTCB = pvSlackGetTaskSsTCB( NULL );

    vTaskDelay( rand() % pxTaskSsTCB->xPeriod );

    for(;;)
    {
        #if TZ == 1
        vTracePrintF( slack_channel, "%d - %d", xSlackGetAvailableSlack(), pxTaskSsTCB->xSlack );
        #endif

        pxTaskSsTCB->xCur = ( TickType_t ) 0;

        if ( xSemaphoreTake( xMutex, portMAX_DELAY ) )
        {
            vTasksGetSlacks( slackArray );
            vCommonPrintSlacks( 'S', slackArray, pxTaskSsTCB );
            xSemaphoreGive( xMutex );
        }

        if (id == 1) {
            ledR = 1;
        }

        vUtilsBusyWait( rand() % pxTaskSsTCB->xWcet );

        if (id == 1) {
            ledR = 0;
        }

        if ( xSemaphoreTake( xMutex, portMAX_DELAY ) )
        {
            vTasksGetSlacks( slackArray );
            vCommonPrintSlacks( 'E', slackArray, pxTaskSsTCB );
            xSemaphoreGive( xMutex );
        }

        #if TZ == 1
        vTracePrintF( slack_channel, "%d - %d", xSlackGetAvailableSlack(), pxTaskSsTCB->xSlack );
        #endif

        vTaskDelay( rand() % pxTaskSsTCB->xPeriod );

        pxTaskSsTCB->uxReleaseCount = pxTaskSsTCB->uxReleaseCount + 1;
    }
}
/*-----------------------------------------------------------*/

static void vPeriodicTask( void* params )
{
    int32_t taskId = (int32_t) params;
    int turn = 0;

    SsTCB_t *pxTaskSsTCB = pvSlackGetTaskSsTCB( NULL );

    UBaseType_t xRndRun = 0;

    for(;;)
    {
        #if TZ == 1
        vTracePrintF( slack_channel, "%d - %d", xSlackGetAvailableSlack(), pxTaskSsTCB->xSlack );
        #endif

        if ( xSemaphoreTake( xMutex, MUTEX_TIMEOUT ) )
        {
            vTasksGetSlacks( slackArray );
            vCommonPrintSlacks( 'S', slackArray, pxTaskSsTCB );
            xSemaphoreGive( xMutex );
        }

        leds[ taskId - 1] = 1;

        if (taskId == 1) {
            display.clearDisplay();
            switch(turn) {
            case 0:
                display.drawBitmap(0, 0, arm_logo, 128, 64, 1);
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
        }

        if (taskId == 1) {
            xRndRun = (UBaseType_t) rand() % ( pxTaskSsTCB->xWcet - 400 );
        } else {
            xRndRun = (UBaseType_t) rand() % ( pxTaskSsTCB->xWcet - 300 );
        }
        vUtilsBusyWait( xRndRun );

        leds[ taskId - 1] = 0;

        if ( xSemaphoreTake( xMutex, MUTEX_TIMEOUT ) )
        {
            vTasksGetSlacks( slackArray );
            vCommonPrintSlacks( 'E', slackArray, pxTaskSsTCB );
            xSemaphoreGive( xMutex );
        }

        #if TZ == 1
        vTracePrintF( slack_channel, "%d - %d", xSlackGetAvailableSlack(), pxTaskSsTCB->xSlack );
        #endif

        vTaskDelayUntil( &( pxTaskSsTCB->xPreviousWakeTime ), pxTaskSsTCB->xPeriod );
    }
}
/*-----------------------------------------------------------*/

/*****************************************************************************
 * Public functions
 ****************************************************************************/
/**
 *
 * @return Nothing, function should not exit.
 */
int main(void)
{
    // Verify that configUSE_SLACK_STEALING is enabled
    configSS_ASSERT_EQUAL( configUSE_SLACK_STEALING, 1 );
    // Verify that tskKERNEL_VERSION_MAJOR is >= 10
    configSS_ASSERT_GREATHER_OR_EQUAL( tskKERNEL_VERSION_MAJOR, 10);

#ifdef USE_TRACEALIZER
    // Initializes the trace recorder, but does not start the tracing.
    vTraceEnable( TRC_INIT );
    //slack_channel = xTraceRegisterString("Slack Events");
#endif

    display.splash();
    wait(2);

    pc.baud( BAUDRATE );
    pc.printf( "Example %d\n\r", EXAMPLE );
    pc.printf( "Using FreeRTOS %s\n\r", tskKERNEL_VERSION_NUMBER );

    // turn off all the on board LEDs.
    leds[0] = 0;
    leds[1] = 0;
    leds[2] = 0;
    leds[3] = 0;
    ledR = 0;

    // Create mutex.
    xMutex = xSemaphoreCreateMutex();

    // Periodic tasks.
    xTaskCreate( vPeriodicTask, "T1", 256, (void*) 1, TASK_1_PRIO, &task_handles[ 0 ] );
    xTaskCreate( vPeriodicTask, "T2", 256, (void*) 2, TASK_2_PRIO, &task_handles[ 1 ] );
    xTaskCreate( vPeriodicTask, "T3", 256, (void*) 3, TASK_3_PRIO, &task_handles[ 2 ] );
    xTaskCreate( vPeriodicTask, "T4", 256, (void*) 4, TASK_4_PRIO, &task_handles[ 3 ] );

    // Aperiodic tasks.
    xTaskCreate( vAperiodicTask, "A1", 256, (void*) 1, ATASK_1_PRIO, &xApTaskHandle1 );
    xTaskCreate( vAperiodicTask, "A2", 256, (void*) 2, ATASK_2_PRIO, &xApTaskHandle2 );

#if configUSE_SLACK_STEALING == 1
    // additional parameters needed by the slack stealing framework
    vSlackSetTaskParams( task_handles[ 0 ], PERIODIC_TASK, TASK_1_PERIOD,
            TASK_1_PERIOD, TASK_1_WCET );
    vSlackSetTaskParams( task_handles[ 1 ], PERIODIC_TASK, TASK_2_PERIOD,
            TASK_2_PERIOD, TASK_2_WCET );
    vSlackSetTaskParams( task_handles[ 2 ], PERIODIC_TASK, TASK_3_PERIOD,
            TASK_3_PERIOD, TASK_3_WCET );
    vSlackSetTaskParams( task_handles[ 3 ], PERIODIC_TASK, TASK_4_PERIOD,
            TASK_4_PERIOD, TASK_4_WCET );

    vSlackSetTaskParams( xApTaskHandle1, APERIODIC_TASK, ATASK_MAX_DELAY, 0,
            ATASK_WCET );
    vSlackSetTaskParams( xApTaskHandle2, APERIODIC_TASK, ATASK_MAX_DELAY, 0,
            ATASK_WCET );
#endif

#ifdef USE_TRACEALIZER
    // Start the tracing.
    vTraceEnable( TRC_START );
#endif

    /* Initialize random number generator with seed zero to have a reproducible
     * trace. */
    srand((unsigned) 0);

    // Start the scheduler.
    vTaskStartScheduler();

    // Should never arrive here.
    for(;;);
}
