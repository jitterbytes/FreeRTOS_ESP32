# 2_Communication
This is the second concept in FreeRTOS: **"Communication"**.  

### **Why Communication Between Tasks??**  
As we know Tasks runs independently and may run on different cores or at different times. 
More often tasks will need to:  
- **Share Data** - A sensor reading task sends data to logging or display task.
- **Coordinate Actions** - A button task signals a motor control task to start.
- **Avoid Conflicts** - Two Task trying to write I2C or UART at the same time.

⚠️ Doing this incorrectly can lead to **data corruption, race condition, or missed signals.** This is where we need Communication!!

**Core Concepts**  
| Concept | Purpose | Explanation |
|:--|:--|:--|
| **Queue** | Task-to-Task data transfer | One task **posts** data, another **reads** |
| **Binary Semaphore** | Simple signaling | Like a flag set by one task, cleared by another |
| **Counting Semaphore** | Multiple resource management | Multiple copies of key. Tasks "take" a key to use a resource and "give" it back when done |
| **Mutex (Mutual Exclusion)** | Protect shared resources | Ensure only one task access a shared resource (like UART) at a time. Prevents collision and data corruption | 
| **Event Groups** | Multi-task synchronization | Task can wait for one or more events to happen. Think of it as waiting for multiple conditions before proceeding | 

<details>
<summary>View Chapter Summary</summary>  
  
**Experiments Overview**  
| Exp | Title | Concept Focus | Key Learnings |
|:--:|:--|:--|:--|
| **1a** | [Blink Multitask](./1a_Blink_Multitask/) | Task Creation & Scheduling | Create multiple tasks and observe time-sliced execution. |
| **1b** | [Task States & Control](./1b_Task_States/) | Suspend, Resume, Delete Tasks | Use Task Handles to manage task execution flow. |
| **1c** | [Core Affinity](./1c_core_affinity/) | Pin Tasks to CPU Cores | Learn to assign specific cores for deterministic behavior on ESP32. |
| **1d** | [Task Notifications](./1d_Task_Notifications/) | Inter-Task Signaling | Implement fast, lightweight communication between tasks. |

**Concepts Covered**
- Task Creation (`xTaskCreate`, `xTaskCreatePinnedToCore`)
- Task Scheduling (Equal Priority → Time-sliced)
- Task Control (`vTaskSuspend`, `vTaskResume`, `vTaskDelete`)
- Task Communication (via Direct Notifications)
- Core Affinity & Dual-core Management (ESP32)
- Task Handles & Priority Management

Up Next - _**2_Communication**_
</details>
