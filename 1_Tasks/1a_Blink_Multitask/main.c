#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define LED 23   // Led -> GPIO 23

// Task 1 -> Blink led at 1Hz
void blink_task(void *pvParameter){
    gpio_reset_pin(LED);
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    while(1)
    {
        gpio_set_level(LED,1);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        gpio_set_level(LED,0);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

// Task 2 -> Printing via UART
void uart_task(void *pvParameter){
    while(1)
    {  
        ESP_LOGI("UART_TASK", "Hello from UART Task");
        vTaskDelay(1000/portTICK_PERIOD_MS); 
    }
}

void app_main(void)
{
    // Creating Blink Task 
    xTaskCreate(blink_task, "Blink Task", 2048, NULL, 5, NULL);
    // Parameters:Task Function, Task Name, Stack Size, Parameters, Priority, Task Handle
    // Task Funtion -> Function Pointer
    // Task Name -> Name for the task (for deugging purpose)
    // Stack Size -> Memory to be allocated for this task its 2048 words | 1 word = 4 bytes | 2048 words -> 8192 bytes
    // **For normal task put 2048 only approx 8KB for complex task allocate more 4096-8192 words -> 16-32KB**
    // Paramters -> can send args into task creation , if some task require some variable value
    // Priority -> Higher nos = Higher Priority | Task with same priority time-slice
    // If one task has higher priority it will *interrupt* the task with lower priority
    // Task Handle -> Can give task a handle then you can refer to the task later to either suspend/delete the task

    // Creating UART Task
    xTaskCreate(uart_task, "UART Task", 2048, NULL, 5, NULL);
}
