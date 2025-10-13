# 1c Core Affinity

## 🎯 Objective
Understand how to assign FreeRTOS tasks to specific CPU cores (Core 0 or Core 1) on the dual-core ESP32
and observe how tasks run concurrently on both cores.

> For Demonstration  
> Task 1 -> Blink Task (pinned to Core 0)
> Task 2 -> UART Print Task (pinned to Core 1)  

## 🛠 Steps | 📝 Code 
- Initialize the header files
  ```c
  #include <stdio.h>
  #include "freertos/FreeRTOS.h"
  #include "freertos/task.h"
  #include "driver/gpio.h"
  #include "esp_log.h"
  ```
- Define Led Pin & TAG for Task 2
  ```c
  #define LED 23
  static const char *TAG = "TASK_CTRL";   // Tag for the controller Task
  ```
- Define Blink Task Function
  ```c
  // Task 1 -> Blink led at 1Hz
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
  ```
- Define Controller Task Function
  ```c
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
  ``` 
- In app_main() Create both the Tasks and Task 2 has higher priority
  ```c
  void app_main(void)
  {
      xTaskCreate(blink_task, "Blink Task", 2048, NULL, 5, &blinkHandle);
      xTaskCreate(controller_task, "Controller Task", 2048, NULL, 6, NULL);
  }
  ```

## 👀 Observations & Experiments
ESP32 has 2 cores:  
- Core 0: Runs the WiFi, Bluetooth and system tasks.
- Core 1: Runs the User App
By default, `xTaskCreate()` allows the schedule to choose any core But we manually choose the Core we used `xTaskCreatePinnedToCore()` 





