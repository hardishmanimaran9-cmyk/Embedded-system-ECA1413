#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

// Semaphore handles
SemaphoreHandle_t binarySem;
SemaphoreHandle_t countingSem;
SemaphoreHandle_t mutexSem;

// Shared variable
int sharedCounter = 0;


// BINARY SEMAPHORE - Sender Task
void BinarySender(void *pvParameters)
{
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(2000));

        printf("\nBinary: Sending signal\n");

        if (xSemaphoreGive(binarySem) == pdTRUE)
            printf("Binary: Signal sent successfully\n");
    }
}


// BINARY SEMAPHORE - Receiver Task
void BinaryReceiver(void *pvParameters)
{
    while (1)
    {
        if (xSemaphoreTake(binarySem, portMAX_DELAY) == pdTRUE)
        {
            printf("Binary: Signal received\n");
        }
    }
}


// COUNTING SEMAPHORE - Producer
void CountingProducer(void *pvParameters)
{
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));

        if (xSemaphoreGive(countingSem) == pdTRUE)
        {
            printf("Counting: Resource added\n");
        }
        else
        {
            printf("Counting: Maximum count reached\n");
        }
    }
}


// COUNTING SEMAPHORE - Consumer
void CountingConsumer(void *pvParameters)
{
    while (1)
    {
        if (xSemaphoreTake(countingSem, portMAX_DELAY) == pdTRUE)
        {
            printf("Counting: Resource consumed\n");

            printf("Remaining count: %lu\n",
                   (unsigned long)uxSemaphoreGetCount(countingSem));

            vTaskDelay(pdMS_TO_TICKS(2500));
        }
    }
}


// MUTEX - Shared Data Access
void MutexTask(void *pvParameters)
{
    char *taskName = (char *)pvParameters;

    for (int i = 0; i < 5; i++)
    {
        if (xSemaphoreTake(mutexSem, portMAX_DELAY) == pdTRUE)
        {
            sharedCounter++;

            printf("%s accessing shared data: %d\n",
                   taskName, sharedCounter);

            vTaskDelay(pdMS_TO_TICKS(200));

            xSemaphoreGive(mutexSem);
        }

        vTaskDelay(pdMS_TO_TICKS(500));
    }

    printf("%s completed\n", taskName);

    vTaskDelete(NULL);
}


// MAIN FUNCTION
void app_main(void)
{
    printf("\nFreeRTOS Synchronization Started\n");

    // Create semaphores
    binarySem = xSemaphoreCreateBinary();

    countingSem = xSemaphoreCreateCounting(3, 0);

    mutexSem = xSemaphoreCreateMutex();

    if (binarySem == NULL ||
        countingSem == NULL ||
        mutexSem == NULL)
    {
        printf("Semaphore creation failed!\n");
        return;
    }

    // Binary Semaphore Tasks
    xTaskCreate(BinarySender, "Binary Sender",
                2048, NULL, 2, NULL);

    xTaskCreate(BinaryReceiver, "Binary Receiver",
                2048, NULL, 2, NULL);

    // Counting Semaphore Tasks
    xTaskCreate(CountingProducer, "Producer",
                2048, NULL, 2, NULL);

    xTaskCreate(CountingConsumer, "Consumer",
                2048, NULL, 2, NULL);

    // Mutex Tasks
    xTaskCreate(MutexTask, "Mutex Task 1",
                2048, "Task 1", 2, NULL);

    xTaskCreate(MutexTask, "Mutex Task 2",
                2048, "Task 2", 2, NULL);
}
