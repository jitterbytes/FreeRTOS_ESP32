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
  <summary>**Chapter Summary**</summary>
  
  This is the content that is hidden by default.
  It can contain regular Markdown, like **bold text** or a [link](https://example.com).
</details>
