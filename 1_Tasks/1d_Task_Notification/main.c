#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define LED GPIO_NUM_23
static const char *TAG_LED = "LED_TASK";
static const char *TAG_CTRL = "CTRL_TASK";

TaskHandle_t ledHandle = NULL;  // Handle for the receiver task
 

// Task 1 -> Blink Task -> Receiver
void led_task(void *pvParameter)
{
    gpio_reset_pin(LED);
    gpio_set_direction(LED,GPIO_MODE_OUTPUT);

    uint8_t led_state = 0;  // This executes only one time when the task is created. Its not like a function
    uint32_t ulNotifiedValue;

    while(1)
    {
        // Wait for notification indefinetly
        // xTaskNotifyWait Parameters 
        // 1. ulBitsToClearOnEntry -> Bits of the task notified value is cleared before receiving
        // 2. ulBitsToClearOnExit -> After receiving bits are cleared
        // 3. *pulNotificationValue -> Pointer to where received value will be stored
        // 4. xTicksToWait -> portMAX_DELAY -> indefinetly 
        if(xTaskNotifyWait(0x00,0xFFFFFFFF,&ulNotifiedValue,portMAX_DELAY ))
        {   
            led_state = !led_state;
            gpio_set_level(LED, led_state);
            ESP_LOGI(TAG_LED, "Notification Recieved: %ld | LED TOGGLED", ulNotifiedValue);
        }
    }
}

// Task 2 -> Controller Task -> Sender
void controller_task(void *pvParameter)
{
    uint32_t count = 0;
    while(1)
    {
        count++;
        ESP_LOGI(TAG_CTRL, "Sending Notification %ld", count);

        // Send Notification to LED Task
        // xTaskNotify Parameters 
        // 1. xTaskToNotify -> Handle of receivng task
        // 2. ulValue -> Value to send 
        // 3. eAction -> How to update the receiving task's notification value
        // eAction 
        // 3.1 eSetBits -> Bitwise OR with existing value
        // 3.2 eIncrement -> Increment task notification value
        // 3.3 eSetValueWithoutOverwrite -> Sets the value if task hasn't been already notified
        // 3.4 eSetValueWithOverwrite -> Overwrites the existing notified value
        // 3.5 eNoAction -> Just unblocks the tasks does not change the value 
        xTaskNotify(ledHandle, count, eSetValueWithOverwrite);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    // Creating Receiver Task - LED
    xTaskCreate(led_task, "LED Task", 2048, NULL, 5, &ledHandle);

    // Creating Sender Task - Controller
    xTaskCreate(controller_task, "Controller Task", 2048, NULL, 6, NULL);

}
