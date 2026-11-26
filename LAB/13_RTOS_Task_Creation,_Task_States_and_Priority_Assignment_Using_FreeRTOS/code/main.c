
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED GPIO_NUM_2

// Task 1 - High Priority
void Task1(void *pvParameters)
{
    while (1)
    {
        printf("Task 1: LED ON\n");
        gpio_set_level(LED, 1);

        vTaskDelay(pdMS_TO_TICKS(1000));

        printf("Task 1: LED OFF\n");
        gpio_set_level(LED, 0);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Task 2 - Medium Priority
void Task2(void *pvParameters)
{
    while (1)
    {
        printf("Task 2: Running\n");

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// Task 3 - Low Priority
void Task3(void *pvParameters)
{
    while (1)
    {
        printf("Task 3: Running\n");

        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

// Main Function
void app_main(void)
{
    gpio_reset_pin(LED);
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);

    printf("\nFreeRTOS Task Scheduling Started\n");

    xTaskCreate(Task1, "LED Task", 2048, NULL, 3, NULL);

    xTaskCreate(Task2, "Task 2", 2048, NULL, 2, NULL);

    xTaskCreate(Task3, "Task 3", 2048, NULL, 1, NULL);
}
