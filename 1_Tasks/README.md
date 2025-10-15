# 1_Tasks
This is the first concept in FreeRTOS: **"Tasks"**.  

### **What are Tasks??**  
_RTOS → Real-Time Operating System_ – when we include an RTOS in our project, it means we want **concurrent things to run at the same time**. Otherwise, we would be stuck with the basic **superloop architecture** using `while(1)`.  

To achieve concurrency, all pieces of code are organized into **Tasks**.  

**Example**  
- **Superloop Architecture:**  
  `Sensor Reading -> Start WiFi & Send the data -> Update the LCD screen`  

- **FreeRTOS with Tasks:**  
  - **Task 1:** Sensor Reading  
  - **Task 2:** Start WiFi and Send Data  
  - **Task 3:** Update LCD Screen  

Here, all three tasks run **concurrently** (or appear to run **simultaneously**). In reality, the FreeRTOS **scheduler** is sitting behind them, time-slicing and quickly switching between tasks. To us, it looks like everything is happening at the same time.  

Next, let’s create our own tasks and understand the fundamentals.  

<details>
<summary> View Chapter Summary </summary>
**Experiments Overview**
| Exp | Title | Concept Focus | Key Learnings |
|:--:|:--|:--|:--|
| **1a** | [Blink Multitask](./1a_blink_multitask/) | Task Creation & Scheduling | Create multiple tasks and observe time-sliced execution. |
| **1b** | [Task States & Control](./1b_task_states/) | Suspend, Resume, Delete Tasks | Use Task Handles to manage task execution flow. |
| **1c** | [Core Affinity](./1c_core_affinity/) | Pin Tasks to CPU Cores | Learn to assign specific cores for deterministic behavior on ESP32. |
| **1d** | [Task Notifications](./1d_task_notifications/) | Inter-Task Signaling | Implement fast, lightweight communication between tasks. |

</details>
