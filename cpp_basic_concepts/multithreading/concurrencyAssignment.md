# C++ Concurrency Assignment
This assignment will help you understand and mitigate race conditions in multi-threaded C++ applications using std::mutex and std::atomic.

## Part 1: Observing a Race Condition (The Problem)
Objective: To observe and understand what a race condition looks like in practice.

#### Instructions:

- Compile and run the following C++ code.

- Run it multiple times (at least 5-10 times).

- Observe the output, specifically the values printed for val by each thread and the final value of val in main.

Code:

```cpp
#include <iostream>
#include <thread>
#include <vector>
#include <chrono> // For potential sleep if desired for debugging output

// Function to be executed by each thread
void hello_race(int& val) {
    // Simulate some work before incrementing
    // std::this_thread::sleep_for(std::chrono::milliseconds(1));

    val++; // This is the critical operation causing the race condition

    std::thread::id current_thread_id = std::this_thread::get_id();
    // Printing to cout can also be subject to interleaving without protection
    std::cout << "Hello from thread " << current_thread_id << ": val = " << val << std::endl;
}

int main() {
    int shared_val = 0; // Shared variable accessed by multiple threads
    std::vector<std::thread> threads;

    const int num_threads = 5;

    // Create and launch threads
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(hello_race, std::ref(shared_val));
    }

    // Join all threads to ensure they complete before main exits
    for (std::thread& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    std::cout << "\n--- Race Condition Results ---" << std::endl;
    std::cout << "Final value of shared_val in main: " << shared_val << std::endl;
    std::cout << "Expected final value: " << num_threads << std::endl;
    std::cout << "All threads finished." << std::endl;

    return 0;
}

```
#### Questions for Part 1:

- Describe the values of val printed by the individual threads. Do they always increment sequentially (1, 2, 3, 4, 5)?

- What is the final value of shared_val printed in main? Is it consistently 5 (the num_threads) across multiple runs?

- Explain why you observe this behavior. What is a "race condition" in the context of val++?

#### Part 2: Solving with std::mutex (Mutual Exclusion)
Objective: To implement and understand how std::mutex prevents race conditions by enforcing mutual exclusion.

Instructions:

- Modify the hello_race function from Part 1 to use a std::mutex to protect the increment and print operations.

- Compile and run the modified code multiple times.

- Observe the output.

Code (Modified hello_race and global mutex):

```cpp
#include <iostream>
#include <thread>
#include <vector>
#include <mutex> // NEW: For std::mutex and std::lock_guard
#include <chrono>

// NEW: Global mutex to protect shared resources
std::mutex global_mtx;

void hello_mutex(int& val) {
    // Acquire the lock before entering the critical section
    // std::lock_guard ensures the mutex is unlocked when 'lock' goes out of scope
    std::lock_guard<std::mutex> lock(global_mtx); // Critical section starts here

    val++; // This operation is now protected
    std::thread::id current_thread_id = std::this_thread::get_id();
    std::cout << "Hello from thread " << current_thread_id << ": val = " << val << std::endl;
    // Critical section ends here (lock is released when 'lock' goes out of scope)
}

int main() {
    int shared_val = 0;
    std::vector<std::thread> threads;

    const int num_threads = 5;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(hello_mutex, std::ref(shared_val));
    }

    for (std::thread& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    std::cout << "\n--- Mutex Results ---" << std::endl;
    std::cout << "Final value of shared_val in main: " << shared_val << std::endl;
    std::cout << "Expected final value: " << num_threads << std::endl;
    std::cout << "All threads finished." << std::endl;

    return 0;
}
```

#### Questions for Part 2:

- How do the values of val printed by individual threads now compare to Part 1? Are they consistently sequential?

- What is the final value of shared_val in main? Is it consistently 5 across multiple runs?

- Explain how the std::mutex and std::lock_guard solve the race condition. What does it mean for a section of code to be "serialized" by a mutex?

- Discuss the potential performance implications of using a mutex. If the hello_mutex function contained a very long, complex calculation inside the lock_guard block, how would that affect the overall execution time compared to a version without threads?

#### Part 3: Solving with std::atomic (Atomic Operations)
Objective: To understand how std::atomic provides a lightweight, hardware-supported way to perform atomic operations on simple data types.

Instructions:

- Modify the main function to declare shared_val as std::atomic<int>.

- Modify the hello_atomic function to accept std::atomic<int>& and use atomic operations.

- Compile and run the modified code multiple times.

- Observe the output.

Code (Modified main and hello_atomic):

```cpp
#include <iostream>
#include <thread>
#include <vector>
#include <atomic> // NEW: For std::atomic
#include <chrono>

// No global mutex needed for 'val' itself if we use atomic
// std::mutex global_mtx; // Not needed for val, but still needed for cout if strict order is required

void hello_atomic(std::atomic<int>& val) { // NEW: Accept std::atomic<int>&
    // Atomically increment val. This operation is guaranteed to be indivisible.
    int current_val_snapshot = ++val; // Atomically increments and returns the new value

    std::thread::id current_thread_id = std::this_thread::get_id();
    // NOTE: Printing to cout is NOT inherently atomic.
    // The output lines might still interleave, even though 'val' itself is correctly incremented.
    std::cout << "Hello from thread " << current_thread_id << ": val = " << current_val_snapshot << std::endl;
}

int main() {
    std::atomic<int> shared_val = 0; // NEW: Declare as std::atomic<int>
    std::vector<std::thread> threads;

    const int num_threads = 5;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(hello_atomic, std::ref(shared_val)); // Pass std::atomic by reference
    }

    for (std::thread& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    std::cout << "\n--- Atomic Results ---" << std::endl;
    // Use .load() to get the current value from an atomic variable
    std::cout << "Final value of shared_val in main: " << shared_val.load() << std::endl;
    std::cout << "Expected final value: " << num_threads << std::endl;
    std::cout << "All threads finished." << std::endl;

    return 0;
}
```

#### Questions for Part 3:

- What is the final value of shared_val in main? Is it consistently 5 across multiple runs?

- Observe the output lines from std::cout. Do they always appear in a perfectly sequential order (e.g., val = 1, then val = 2, etc.)? Why or why not?

- Explain the difference between std::mutex and std::atomic<int> for protecting val. When would you choose one over the other?

#### Challenge: 
Modify the hello_atomic function to ensure that the std::cout output also appears in a perfectly sequential order (i.e., val = 1 always prints before val = 2, and the entire line is printed without interruption). You will need to use a mechanism discussed previously.

Good luck with the assignment! This hands-on experience will significantly deepen your understanding of these critical concurrency concepts.