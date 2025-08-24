#include <iostream>
#include <thread>
#include <chrono>

// =============================================================================
// 1. STATIC STORAGE DURATION
// =============================================================================

// This goes in the DATA section (.data) of the executable
int global_initialized = 42;  // Lives the entire program lifetime!

// This goes in the BSS section (.bss) - Block Started by Symbol
int global_uninitialized;     // Also lives forever, initialized to 0

// Static in function - still in DATA/BSS section!
void demonstrate_static() {
    // This is initialized ONCE when first called
    // Lives in .data section, not on stack!
    static int counter = 0;
    counter++;
    std::cout << "Static counter: " << counter << std::endl;
}

/*
 * HOW IT WORKS UNDER THE HOOD:
 * - Compiler puts these in special sections of the binary
 * - .data section: initialized static/global variables
 * - .bss section: uninitialized static/global (zeroed by OS)
 * - Memory allocated at program start by the OS
 * - Lives at a FIXED address for entire program
 * - Freed when program terminates
 */

// =============================================================================
// 2. THREAD-LOCAL STORAGE DURATION
// =============================================================================

// Each thread gets its OWN copy!
thread_local int tls_variable = 0;

void thread_function(int thread_id) {
    // Each thread sees its own value!
    tls_variable = thread_id * 100;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Will print different values for each thread
    std::cout << "Thread " << thread_id 
              << " sees tls_variable = " << tls_variable << std::endl;
}

void demonstrate_thread_local() {
    std::thread t1(thread_function, 1);
    std::thread t2(thread_function, 2);
    
    t1.join();
    t2.join();
}

/*
 * HOW IT WORKS UNDER THE HOOD:
 * - Compiler generates special TLS sections (.tdata, .tbss)
 * - Runtime allocates separate copy for EACH thread
 * - Usually involves Thread Control Block (TCB)
 * - Access often through segment registers (FS/GS on x86-64)
 * - Freed when thread dies
 */

// =============================================================================
// 3. AUTOMATIC STORAGE DURATION (Stack)
// =============================================================================

void demonstrate_automatic() {
    // These live on the STACK!
    int local_var = 10;        // Dies when function returns
    char array[100];           // Also on stack
    
    // Stack grows DOWN (high to low addresses usually)
    std::cout << "Local var address: " << &local_var << std::endl;
    std::cout << "Array address: " << &array << std::endl;
    
    if (true) {
        int scoped_var = 20;   // Dies at end of this block!
    } // scoped_var is GONE here!
}

/*
 * HOW IT WORKS UNDER THE HOOD:
 * - Compiler uses stack pointer register (RSP on x86-64)
 * - Function prologue: SUB RSP, <size> to allocate
 * - Variables accessed via offsets from RSP/RBP
 * - Function epilogue: ADD RSP, <size> to deallocate
 * - SUPER FAST allocation/deallocation!
 * - Stack overflow if you use too much
 */

// =============================================================================
// 4. DYNAMIC STORAGE DURATION (Heap)
// =============================================================================

class BigObject {
    int data[1000];
public:
    BigObject() { std::cout << "BigObject created at " << this << std::endl; }
    ~BigObject() { std::cout << "BigObject destroyed" << std::endl; }
};

void demonstrate_dynamic() {
    // C++ style - calls constructor/destructor
    int* ptr1 = new int(42);           // Single object
    int* arr1 = new int[10];           // Array
    BigObject* obj = new BigObject();  // Custom object
    
    // C style - just raw memory
    int* ptr2 = (int*)malloc(sizeof(int));
    *ptr2 = 43;
    
    // You MUST free them!
    delete ptr1;        // Matches new
    delete[] arr1;      // Matches new[]
    delete obj;         // Calls destructor
    free(ptr2);         // Matches malloc
}

/*
 * HOW IT WORKS UNDER THE HOOD:
 * - new/malloc call system allocator (like ptmalloc, jemalloc)
 * - Allocator manages heap via system calls (brk, mmap on Linux)
 * - Maintains free lists, bins for different sizes
 * - Memory fragmentation is real problem!
 * - MUCH slower than stack allocation
 * - Can allocate HUGE amounts (limited by virtual memory)
 * - YOU control lifetime - blessing and curse!
 */

// =============================================================================
// MEMORY LAYOUT VISUALIZATION
// =============================================================================

void show_memory_layout() {
    // Let's see where everything lives!
    int stack_var = 1;
    static int static_var = 2;
    int* heap_var = new int(3);
    
    std::cout << "\n=== MEMORY LAYOUT ===" << std::endl;
    std::cout << "Stack variable:  " << &stack_var << " (high address)" << std::endl;
    std::cout << "Heap variable:   " << heap_var << " (middle)" << std::endl;
    std::cout << "Static variable: " << &static_var << " (low address)" << std::endl;
    std::cout << "Global variable: " << &global_initialized << " (low address)" << std::endl;
    std::cout << "Code (function): " << (void*)&show_memory_layout << " (lowest)" << std::endl;
    
    delete heap_var;
}

/*
 * TYPICAL PROCESS MEMORY LAYOUT (simplified):
 * 
 * High Address
 * +-----------------+
 * |      Stack      | ← Grows DOWN
 * |        ↓        |
 * |                 |
 * |   Free Space    |
 * |                 |
 * |        ↑        |
 * |      Heap       | ← Grows UP
 * +-----------------+
 * |   BSS Section   | ← Uninitialized globals
 * +-----------------+
 * |  Data Section   | ← Initialized globals
 * +-----------------+
 * |  Text Section   | ← Your code
 * +-----------------+
 * Low Address (0x400000 on Linux typically)
 */

// =============================================================================
// MAIN - Let's see it all in action!
// =============================================================================

int main() {
    std::cout << "=== STATIC STORAGE ===" << std::endl;
    demonstrate_static();  // Counter = 1
    demonstrate_static();  // Counter = 2 (persists!)
    demonstrate_static();  // Counter = 3
    
    std::cout << "\n=== THREAD-LOCAL STORAGE ===" << std::endl;
    demonstrate_thread_local();
    
    std::cout << "\n=== AUTOMATIC STORAGE ===" << std::endl;
    demonstrate_automatic();
    
    std::cout << "\n=== DYNAMIC STORAGE ===" << std::endl;
    demonstrate_dynamic();
    
    show_memory_layout();
    
    return 0;
}

/*
 * COMPILER SPECIFICS:
 * 
 * GCC/Clang:
 * - Use __thread for C-style TLS
 * - -fstack-protector for stack safety
 * - objdump -h to see sections
 * 
 * MSVC:
 * - __declspec(thread) for TLS
 * - /GS for stack protection
 * - dumpbin /headers to see sections
 * 
 * REMEMBER:
 * - Stack = FAST but LIMITED
 * - Heap = SLOW but FLEXIBLE
 * - Static = FOREVER but GLOBAL STATE IS EVIL
 * - Thread-local = EACH THREAD GETS ONE
 * 
 * Common bugs:
 * - Stack overflow (too much automatic storage)
 * - Memory leaks (forgot delete/free)
 * - Double free (deleted twice)
 * - Use after free (accessing deleted memory)
 * - Data races (multiple threads, no sync)
 */