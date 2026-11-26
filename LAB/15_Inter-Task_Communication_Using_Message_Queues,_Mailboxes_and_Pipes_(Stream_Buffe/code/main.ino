#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/stream_buffer.h"

// Communication handles
QueueHandle_t messageQueue;
QueueHandle_t mailbox;
StreamBufferHandle_t streamBuffer;


// ========================================
// MESSAGE QUEUE - PRODUCER
// ========================================

void QueueProducer(void *pvParameters)
{
  int data = 1;

  while (1)
  {
    if (xQueueSend(messageQueue, &data, portMAX_DELAY) == pdTRUE)
    {
      Serial.print("Queue Producer: Sent ");
      Serial.println(data);
    }

    data++;

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}


// ========================================
// MESSAGE QUEUE - CONSUMER
// ========================================

void QueueConsumer(void *pvParameters)
{
  int receivedData;

  while (1)
  {
    if (xQueueReceive(messageQueue, &receivedData,
                      portMAX_DELAY) == pdTRUE)
    {
      Serial.print("Queue Consumer: Received ");
      Serial.println(receivedData);
    }
  }
}


// ========================================
// MAILBOX - PRODUCER
// ========================================

void MailboxProducer(void *pvParameters)
{
  int data = 100;

  while (1)
  {
    xQueueOverwrite(mailbox, &data);

    Serial.print("Mailbox Producer: Sent ");
    Serial.println(data);

    data++;

    vTaskDelay(pdMS_TO_TICKS(1500));
  }
}


// ========================================
// MAILBOX - CONSUMER
// ========================================

void MailboxConsumer(void *pvParameters)
{
  int receivedData;

  while (1)
  {
    if (xQueueReceive(mailbox, &receivedData,
                      portMAX_DELAY) == pdTRUE)
    {
      Serial.print("Mailbox Consumer: Received ");
      Serial.println(receivedData);
    }

    vTaskDelay(pdMS_TO_TICKS(2500));
  }
}


// ========================================
// STREAM BUFFER - PRODUCER
// ========================================

void StreamProducer(void *pvParameters)
{
  const char *message = "Hello from Producer\n";

  while (1)
  {
    size_t length = strlen(message);

    size_t sent = xStreamBufferSend(
      streamBuffer,
      message,
      length,
      portMAX_DELAY
    );

    Serial.print("Stream Producer: Sent ");
    Serial.print(sent);
    Serial.println(" bytes");

    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}


// ========================================
// STREAM BUFFER - CONSUMER
// ========================================

void StreamConsumer(void *pvParameters)
{
  char receivedData[64];

  while (1)
  {
    size_t received = xStreamBufferReceive(
      streamBuffer,
      receivedData,
      sizeof(receivedData),
      portMAX_DELAY
    );

    if (received > 0)
    {
      Serial.print("Stream Consumer: Received ");

      Serial.write((uint8_t *)receivedData, received);

      Serial.println();
    }
  }
}


// ========================================
// SETUP FUNCTION
// ========================================

void setup()
{
  Serial.begin(115200);

  delay(1000);

  Serial.println("\n================================");
  Serial.println("FreeRTOS Communication Started");
  Serial.println("================================");


  // Create Message Queue
  messageQueue = xQueueCreate(5, sizeof(int));

  // Create Mailbox (Queue length = 1)
  mailbox = xQueueCreate(1, sizeof(int));

  // Create Stream Buffer
  streamBuffer = xStreamBufferCreate(128, 1);


  // Check creation
  if (messageQueue == NULL ||
      mailbox == NULL ||
      streamBuffer == NULL)
  {
    Serial.println("Communication object creation failed!");
    return;
  }

  Serial.println("All Communication Objects Created");


  // Message Queue Tasks
  xTaskCreate(
    QueueProducer,
    "Queue Producer",
    2048,
    NULL,
    2,
    NULL
  );

  xTaskCreate(
    QueueConsumer,
    "Queue Consumer",
    2048,
    NULL,
    2,
    NULL
  );


  // Mailbox Tasks
  xTaskCreate(
    MailboxProducer,
    "Mailbox Producer",
    2048,
    NULL,
    2,
    NULL
  );

  xTaskCreate(
    MailboxConsumer,
    "Mailbox Consumer",
    2048,
    NULL,
    2,
    NULL
  );


  // Stream Buffer Tasks
  xTaskCreate(
    StreamProducer,
    "Stream Producer",
    2048,
    NULL,
    2,
    NULL
  );

  xTaskCreate(
    StreamConsumer,
    "Stream Consumer",
    2048,
    NULL,
    2,
    NULL
  );
}


// ========================================
// LOOP FUNCTION
// ========================================

void loop()
{
  vTaskDelay(pdMS_TO_TICKS(1000));
}
