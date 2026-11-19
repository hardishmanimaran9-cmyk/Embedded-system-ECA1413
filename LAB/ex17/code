#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

// Pin Definitions
#define BUTTON_PIN 18
#define LED_PIN 2

// Queue Handle
QueueHandle_t interruptQueue;

// Interrupt Counter
volatile int interruptCount = 0;


// =====================================
// INTERRUPT SERVICE ROUTINE
// =====================================

void IRAM_ATTR buttonISR()
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    uint32_t event = 1;

    // Send event to queue from ISR
    xQueueSendFromISR(
        interruptQueue,
        &event,
        &xHigherPriorityTaskWoken
    );

    // Request context switch if required
    if (xHigherPriorityTaskWoken == pdTRUE)
    {
        portYIELD_FROM_ISR();
    }
}


// =====================================
// HIGH PRIORITY TASK
// DEFERRED PROCESSING
// =====================================

void InterruptTask(void *pvParameters)
{
    uint32_t receivedEvent;

    while (1)
    {
        // Wait for interrupt event
        if (xQueueReceive(
                interruptQueue,
                &receivedEvent,
                portMAX_DELAY) == pdTRUE)
        {
            interruptCount++;

            Serial.println("\nInterrupt Received!");
            Serial.println("Deferred Processing Started");

            // Toggle LED
            digitalWrite(LED_PIN, !digitalRead(LED_PIN));

            Serial.print("Interrupt Count: ");
            Serial.println(interruptCount);

            Serial.println("Deferred Processing Completed");
        }
    }
}


// =====================================
// LOW PRIORITY BACKGROUND TASK
// =====================================

void BackgroundTask(void *pvParameters)
{
    while (1)
    {
        Serial.println("Background Task Running");

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}


// =====================================
// SETUP FUNCTION
// =====================================

void setup()
{
    Serial.begin(115200);

    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);

    digitalWrite(LED_PIN, LOW);

    delay(1000);

    Serial.println("\n================================");
    Serial.println("FreeRTOS Interrupt Demonstration");
    Serial.println("================================");

    // Create Queue
    interruptQueue = xQueueCreate(10, sizeof(uint32_t));

    if (interruptQueue == NULL)
    {
        Serial.println("Queue Creation Failed!");
        return;
    }

    Serial.println("Interrupt Queue Created");

    // Create High Priority Interrupt Task
    xTaskCreate(
        InterruptTask,
        "Interrupt Task",
        2048,
        NULL,
        3,
        NULL
    );

    // Create Low Priority Background Task
    xTaskCreate(
        BackgroundTask,
        "Background Task",
        2048,
        NULL,
        1,
        NULL
    );

    // Attach GPIO Interrupt
    attachInterrupt(
        digitalPinToInterrupt(BUTTON_PIN),
        buttonISR,
        FALLING
    );

    Serial.println("GPIO Interrupt Enabled");
    Serial.println("Press the Button to Generate Interrupt");
}


// =====================================
// LOOP FUNCTION
// =====================================

void loop()
{
    vTaskDelay(pdMS_TO_TICKS(1000));
}
