# 1a Blink Multitask

## 🎯 Objective
Create 2 FreeRTOS task that will run in parallel  
- Task 1: Blink Led (at 1 second)
- Task 2: Print messages over UART
Demonstrate multitasking in action.

## 🛠 Steps
- Initialize the header files
  ```
  #include <stdio.h>
  #include "freertos/FreeRTOS.h"
  #include "freertos/task.h"
  #include "driver/gpio.h"
  #include "esp_log.h"
  ```
3. Create Task 2
4. Intialize those Tasks in the int main()  
and see the result.

## 👀 Observations & Experiments


## 📝 Notes / Decoding the Code 



