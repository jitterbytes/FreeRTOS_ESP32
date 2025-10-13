# 1d Task Notification

## 🎯 Objective
Understand how direct task notifications work in FreeRTOS —
a lightweight and fast way for one task to signal or send data to another
(without using a queue or semaphore).

> For Demonstration  
> Task 1 -> Blink Task (Receiver)  
> Task 2 -> Controller Task (Sender)  

## 🛠 Steps | 📝 Code 
- Initialize the header files
  ```c
  #include <stdio.h>
  #include "freertos/FreeRTOS.h"
  #include "freertos/task.h"
  #include "driver/gpio.h"
  #include "esp_log.h"
  ```
- Define Led Pin & TAG for the Cores
  ```c
  #define LED GPIO_NUM_23
  static const char *TAG_CORE0 = "CORE0_TASK";
  static const char *TAG_CORE1 = "CORE1_TASK";
  ```
- Define Blink Task Function
  ```c
  // Task 1 -> Blink -> Core 0
  void blink_task(void *pvParameter)
  {
      gpio_reset_pin(LED);
      gpio_set_direction(LED, GPIO_MODE_OUTPUT);
  
      while(1)
      {
          gpio_set_level(LED, 1);
          ESP_LOGI(TAG_CORE0, "LED ON | Running on Core %d", xPortGetCoreID());
          vTaskDelay(500 / portTICK_PERIOD_MS);
  
          gpio_set_level(LED, 0);
          ESP_LOGI(TAG_CORE0, "LED OFF | Running on Core %d", xPortGetCoreID());
          vTaskDelay(500 / portTICK_PERIOD_MS);
      }
  }
  ```
- Define UART Task Function
  ```c
  // Task 2 -> UART -> Core 1
  void uart_task(void *pvParameter)
  {
      while(1)
      {
          ESP_LOGI(TAG_CORE1, "Hellow from UART Task | Running on Core %d", xPortGetCoreID());
          vTaskDelay(1000/ portTICK_PERIOD_MS);
      }
  }
  ``` 
- In app_main() Create both the Tasks using `xTaskCreatePinnedToCore()`
  ```c
  void app_main(void)
  {
      // Create task pinned to Core 0
      xTaskCreatePinnedToCore(blink_task, "Blink Task", 2048, NULL, 5, NULL, 0);
      // Parameters:Task Function, Task Name, Stack Size, Parameters, Priority, Task Handle
      // Task Funtion -> Function Pointer
      // Task Name -> Name for the task (for deugging purpose)
      // Stack Size -> Memory to be allocated for this task its 2048 words | 1 word = 4 bytes | 2048 words -> 8192 bytes
      // **For normal task put 2048 only approx 8KB for complex task allocate more 4096-8192 words -> 16-32KB**
      // Paramters -> can send args into task creation , if some task require some variable value
      // Priority -> Higher nos = Higher Priority | Task with same priority time-slice
      // If one task has higher priority it will *interrupt* the task with lower priority
      // Task Handle -> Can give task a handle then you can refer to the task later to either suspend/delete the task
      // Core ID -> Tells which CPU core to run the task on. 
      //  0 -> Core0 | 1 -> Core1 | tskNO_AFFINITY -> Scheduler can move it b/w cores dynamically
  
      // Create task pinned to Core 1
      xTaskCreatePinnedToCore(uart_task, "UART Task", 2048, NULL, 5, NULL, 1);
  
  }
  ```

## 👀 Observations & Experiments
ESP32 has 2 cores:  
- Core 0: Runs the WiFi, Bluetooth and system tasks.
- Core 1: Runs the User App
By default, `xTaskCreate()` allows the schedule to choose any core But we manually choose the Core we used `xTaskCreatePinnedToCore()` 






