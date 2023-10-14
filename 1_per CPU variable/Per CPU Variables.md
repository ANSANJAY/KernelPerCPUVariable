
- **Per CPU Variables:** 🧠👨‍💻
  - These are utilized to **avoid race conditions** in the kernel by ensuring 
    - **each CPU** in the system **interacts** only with its own data.
  - It's essentially an **array of data structures**, with 
   - **each element** specific to a **single CPU**
  - Only the CPU associated with an element can modify it, negating the need for locks or other synchronization primitives.
  - Alignment of elements ensures each data structure resides on a different line of the hardware cache to sidestep cache line bouncing.
  
- **get_cpu() & put_cpu():**
  - `get_cpu()` not only retrieves the current processor number but also disables kernel preemption, ensuring the current process isn’t preempted to another CPU.
  - `put_cpu()` re-enables kernel preemption, allowing the process to be moved between CPUs again.
  
- **Race Conditions and Kernel Preemption:**
  - Kernel preemption can move processes between CPUs, which can potentially create race conditions.
  - Disabling preemption is necessary when dealing with per CPU variables to prevent a process from being switched to another CPU after obtaining a variable’s address but before accessing it.

**2. Curious Questions** 🤔💭

- **Q1: Why are per CPU variables aligned in main memory?**
  - **A:** They are aligned to ensure that each data structure falls on a different cache line, minimizing cache line bouncing and enhancing parallelism without causing hardware cache coherence contention.

- **Q2: What potential issue arises if a kernel control path accesses a per-CPU variable and is then preempted and moved to another CPU?**
  - **A:** If preempted and moved, the address obtained initially still pertains to the element of the previous CPU, leading to inconsistencies and potential race conditions as it might access or modify data for the wrong CPU.

- **Q3: Why is it necessary to disable kernel preemption when dealing with per-CPU variables?**
  - **A:** Disabling kernel preemption ensures the kernel control path accessing the per-CPU variable isn’t moved to another CPU, which would invalidate the address of the local copy and potentially lead to data inconsistencies.

**3. Simple Concept Explanation** 📘🌟

Imagine you and your friends (each CPU) have your own notebooks (per CPU variables). 📓✍️

- **Your Own Notebook (No Sharing!):**
  - Everyone writes their notes in their own notebook, no need to wait or ask for permission. No one gets confused with others' notes because every person only deals with their own.

- **Taking Notes Safely:**
  - Think of `get_cpu()` like putting a "Do Not Disturb" sign 🚫🔕 when you’re writing in your notebook, so no one interrupts or moves you. It's your time and your notes only.
  - `put_cpu()` is like removing that sign, saying you're okay with chatting or moving around again. 🔄🗣️

- **Why the "Do Not Disturb" Sign?**
  - If you start writing a note 📝 and suddenly move (preempted) to chat with another friend (switched to another CPU), you might forget where you were or mix up notes (data inconsistency or race conditions).

It's all about ensuring everyone writes their notes efficiently, without any mix-ups or waiting! 🚀🔏


**Simple Code Example** 🧑‍💻🎯

Imagine we have a per-CPU variable that keeps track of how many times a function is called per CPU. Here is a simple example in the Linux kernel:

```c
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/smp.h>

// Define a per-CPU variable
DEFINE_PER_CPU(unsigned long, function_call_count);

void example_function(void)
{
    int cpu;
    cpu = get_cpu();  // Disable preemption and get current CPU number
    
    per_cpu(function_call_count, cpu)++;  // Increment the function call count for the current CPU
    
    put_cpu();  // Enable preemption
}

// Module initialization
static int __init my_module_init(void)
{
    // Call example function
    example_function();

    return 0; 
}

// Module exit
static void __exit my_module_exit(void)
{
    // Maybe log or perform an action with the per-CPU variable
}

module_init(my_module_init);
module_exit(my_module_exit);
MODULE_LICENSE("GPL");
```

**Explanation** 🗣️📘

- We utilize `DEFINE_PER_CPU(type, name);` macro to declare a per-CPU variable named `function_call_count` which keeps a count of function calls per CPU.
- Within `example_function`, `get_cpu()` is used to disable preemption and get the current CPU number.
- `per_cpu(function_call_count, cpu)++;` increments the call count specifically for the CPU currently handling the function.
- `put_cpu()` re-enables preemption.
- On module initialization (`my_module_init`), `example_function()` gets called and on module exit (`my_module_exit`) you might decide to log the count or perform some other actions using the per-CPU variable.

💡 This code snippet allows each CPU to independently keep track of how many times `example_function()` has been called without needing to use locks or other synchronization mechanisms to handle access to `function_call_count` safely.