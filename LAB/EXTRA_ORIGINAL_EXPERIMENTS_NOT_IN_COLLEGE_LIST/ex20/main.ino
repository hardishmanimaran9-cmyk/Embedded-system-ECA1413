#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <stdlib.h>

// Memory Pool Configuration
#define POOL_SIZE 5
#define BLOCK_SIZE 64

// Memory Pool
uint8_t memoryPool[POOL_SIZE][BLOCK_SIZE];

// Queue for free memory blocks
QueueHandle_t poolQueue;


// =====================================
// HEAP MEMORY MONITORING
// =====================================

void HeapMonitorTask(void *pvParameters)
{
    while (1)
    {
        size_t freeHeap = xPortGetFreeHeapSize();

        size_t minimumHeap =
            xPortGetMinimumEverFreeHeapSize();

        Serial.println("\n--- HEAP MEMORY STATUS ---");

        Serial.print("Free Heap: ");
        Serial.print(freeHeap);
        Serial.println(" bytes");

        Serial.print("Minimum Free Heap: ");
        Serial.print(minimumHeap);
        Serial.println(" bytes");

        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}


// =====================================
// STACK HIGH WATER MARK
// =====================================

void StackMonitorTask(void *pvParameters)
{
    while (1)
    {
        UBaseType_t stackRemaining =
            uxTaskGetStackHighWaterMark(NULL);

        Serial.println("\n--- STACK MONITOR ---");

        Serial.print("Remaining Stack: ");
        Serial.print((unsigned int)stackRemaining);
        Serial.println(" bytes");

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}


// =====================================
// MEMORY POOL TASK
// =====================================

void MemoryPoolTask(void *pvParameters)
{
    while (1)
    {
        uint8_t *block = NULL;

        // Request memory block
        if (xQueueReceive(
                poolQueue,
                &block,
                portMAX_DELAY) == pdTRUE)
        {
            Serial.println("\n--- MEMORY POOL ---");

            Serial.println("Memory Block Allocated");

            // Write data into memory block
            snprintf(
                (char *)block,
                BLOCK_SIZE,
                "FreeRTOS Memory Pool Data"
            );

            Serial.print("Stored Data: ");
            Serial.println((char *)block);

            vTaskDelay(pdMS_TO_TICKS(1000));

            // Return memory block
            xQueueSend(poolQueue, &block, portMAX_DELAY);

            Serial.println("Memory Block Released");
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


// =====================================
// HEAP ALLOCATION TEST
// =====================================

void HeapAllocationTask(void *pvParameters)
{
    while (1)
    {
        Serial.println("\n--- HEAP ALLOCATION TEST ---");

        // Allocate dynamic memory
        void *memory = pvPortMalloc(128);

        if (memory != NULL)
        {
            Serial.println("128 Bytes Allocated Successfully");

            // Release allocated memory
            vPortFree(memory);

            Serial.println("Memory Released Successfully");
        }
        else
        {
            Serial.println("Heap Allocation Failed");
        }

        vTaskDelay(pdMS_TO_TICKS(5000));
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
    Serial.println("FreeRTOS Memory Management");
    Serial.println("================================");

    // Create Memory Pool Queue
    poolQueue = xQueueCreate(
        POOL_SIZE,
        sizeof(uint8_t *)
    );

    if (poolQueue == NULL)
    {
        Serial.println("Memory Pool Creation Failed!");
        return;
    }

    // Initialize Memory Pool
    for (int i = 0; i < POOL_SIZE; i++)
    {
        uint8_t *block = memoryPool[i];

        xQueueSend(poolQueue, &block, 0);
    }

    Serial.println("Memory Pool Created Successfully");

    // Heap Monitor Task
    xTaskCreate(
        HeapMonitorTask,
        "Heap Monitor",
        2048,
        NULL,
        2,
        NULL
    );

    // Stack Monitor Task
    xTaskCreate(
        StackMonitorTask,
        "Stack Monitor",
        2048,
        NULL,
        2,
        NULL
    );

    // Memory Pool Task
    xTaskCreate(
        MemoryPoolTask,
        "Memory Pool",
        2048,
        NULL,
        2,
        NULL
    );

    // Heap Allocation Task
    xTaskCreate(
        HeapAllocationTask,
        "Heap Allocation",
        2048,
        NULL,
        2,
        NULL
    );
}


// =====================================
// LOOP FUNCTION
// =====================================

void loop()
{
    vTaskDelay(pdMS_TO_TICKS(1000));
}
