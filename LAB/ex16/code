#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/event_groups.h"

// Event Group Handle
EventGroupHandle_t eventGroup;

// Timer Handle
TimerHandle_t periodicTimer;

// Event Bits
#define SENSOR_BIT  (1 << 0)
#define NETWORK_BIT (1 << 1)
#define TIMER_BIT   (1 << 2)


// =====================================
// TIMER CALLBACK FUNCTION
// =====================================

void TimerCallback(TimerHandle_t xTimer)
{
    xEventGroupSetBits(eventGroup, TIMER_BIT);
}


// =====================================
// TIMER EVENT TASK
// =====================================

void TimerTask(void *pvParameters)
{
    while (1)
    {
        EventBits_t bits = xEventGroupWaitBits(
            eventGroup,
            TIMER_BIT,
            pdTRUE,
            pdFALSE,
            portMAX_DELAY
        );

        if (bits & TIMER_BIT)
        {
            Serial.println("Timer Event: 2 seconds completed");
        }
    }
}


// =====================================
// SENSOR TASK
// =====================================

void SensorTask(void *pvParameters)
{
    while (1)
    {
        Serial.println("Sensor Task: Data ready");

        xEventGroupSetBits(eventGroup, SENSOR_BIT);

        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}


// =====================================
// NETWORK TASK
// =====================================

void NetworkTask(void *pvParameters)
{
    while (1)
    {
        Serial.println("Network Task: Data received");

        xEventGroupSetBits(eventGroup, NETWORK_BIT);

        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}


// =====================================
// EVENT GROUP MONITOR TASK
// =====================================

void MonitorTask(void *pvParameters)
{
    while (1)
    {
        Serial.println("\nWaiting for both events...");

        EventBits_t bits = xEventGroupWaitBits(
            eventGroup,
            SENSOR_BIT | NETWORK_BIT,
            pdTRUE,
            pdTRUE,
            portMAX_DELAY
        );

        if ((bits & (SENSOR_BIT | NETWORK_BIT)) ==
            (SENSOR_BIT | NETWORK_BIT))
        {
            Serial.println("Event Group: Both events received!");
            Serial.println("Synchronization Successful\n");
        }
    }
}


// =====================================
// SETUP FUNCTION
// =====================================

void setup()
{
    Serial.begin(115200);

    delay(1000);

    Serial.println("\n================================");
    Serial.println("FreeRTOS Timer and Event Groups");
    Serial.println("================================");

    // Create Event Group
    eventGroup = xEventGroupCreate();

    if (eventGroup == NULL)
    {
        Serial.println("Event Group Creation Failed!");
        return;
    }

    // Create Periodic Software Timer
    periodicTimer = xTimerCreate(
        "PeriodicTimer",
        pdMS_TO_TICKS(2000),
        pdTRUE,
        NULL,
        TimerCallback
    );

    if (periodicTimer == NULL)
    {
        Serial.println("Timer Creation Failed!");
        return;
    }

    Serial.println("Event Group Created Successfully");
    Serial.println("Software Timer Created Successfully");

    // Create Timer Task
    xTaskCreate(
        TimerTask,
        "Timer Task",
        2048,
        NULL,
        2,
        NULL
    );

    // Create Sensor Task
    xTaskCreate(
        SensorTask,
        "Sensor Task",
        2048,
        NULL,
        2,
        NULL
    );

    // Create Network Task
    xTaskCreate(
        NetworkTask,
        "Network Task",
        2048,
        NULL,
        2,
        NULL
    );

    // Create Monitor Task
    xTaskCreate(
        MonitorTask,
        "Monitor Task",
        2048,
        NULL,
        2,
        NULL
    );

    // Start Software Timer
    if (xTimerStart(periodicTimer, 0) == pdPASS)
    {
        Serial.println("Periodic Timer Started");
    }
}


// =====================================
// LOOP FUNCTION
// =====================================

void loop()
{
    vTaskDelay(pdMS_TO_TICKS(1000));
}
