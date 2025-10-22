#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define LED 23
static const char *TAG = "TASK_CTRL";   // Tag for the controller Task

TaskHandle_t blinkHandle = NULL; // TaskHandle Variable -> for &blinkHandle to exist we have to firs declare it here

// Task 1 -> Blink Led
void blink_task(void *pvParameter)
{
    gpio_reset_pin(LED);
    gpio_set_direction(LED,GPIO_MODE_OUTPUT);

    while(1)
    {
        gpio_set_level(LED,1);
        vTaskDelay(200 / portTICK_PERIOD_MS);
        gpio_set_level(LED,0);
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

// Task 2 -> Controller for suspend/resume/delete
void controller_task(void *pvParamter)
{
    ESP_LOGI(TAG, "Controller Started");

    // Let LED task run for 3 seconds
    vTaskDelay(5000 / portTICK_PERIOD_MS);

    ESP_LOGW(TAG, "Suspending LED Task");
    vTaskSuspend(blinkHandle);

    vTaskDelay(5000 / portTICK_PERIOD_MS);

    ESP_LOGW(TAG, "Resuming LED Task");
    vTaskResume(blinkHandle);

    vTaskDelay(5000 / portTICK_PERIOD_MS);

    ESP_LOGE(TAG, "Deleting LED Task");
    vTaskDelete(blinkHandle);    // LED Task will stop permanently

    while(1)
    {
        ESP_LOGI(TAG,"Controller running...");
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    xTaskCreate(blink_task, "Blink Task", 2048, NULL, 5, &blinkHandle);
    xTaskCreate(controller_task, "Controller Task", 2048, NULL, 6, NULL);
}
