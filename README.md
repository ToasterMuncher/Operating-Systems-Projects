# **Operating Systems Projects**
A collection of four projects completed for TCES 420 - Principles of Operating Systems at University of Washington Tacoma, covering fundamental operating system concepts including system calls, multithreading, scheduling, and kernel drivers.

## **Table of Contents**
- [Project Overview](#Project-Overiew)
- [Project 1: Custom System Call](#Project1)
- [Project 2: Multithreaded Matrix Multiplication](#Project2)
- [Project 3: CPU Scheduler](#Project3)
- [Project 4: Linux Kernel Driver](#Project4)
- [Build and Run Instructions](#Build-Run)
- [Technologies Used](#Tech-Used)
- [Learning Outcomes](#Learning-Outcomes)

<a name="Project-Overview"></a>
## **Project Overview**
This repository contains four projects that explore core operating system concepts:
1. **Custom System Call** - Kernel modification and system call implementation
2. **Multithreaded Matrix Multiplication** - Concurrent programming and thread management
3. **CPU Scheduler** - Process scheduling algorithms (In Progress)
4. **Linux Kernel Driver** - Device driver development (Upcoming)

<a name="Project1"></a>
## **Project 1: Custom System Call**
**Status:** ✔️ Completed

**Description**
Implemented a custom system call in a modified Linux kernel that will print "Julio Anacleto \nHello World" when called.

**Key Concepts**
- Linux kernel compilation and configuration
- System call table modification
- Kernel space vs. user space
- System call interface design

**Files**
- [project1-custom-syscall/](/Project1) - Contains kernel patches and test program

**How to Run**
```
[Fill steps in here]
```

<a name="Project2"></a>
## **Project 2: Multithreaded Matrix Multiplication**
**Status:** ✔️ Completed

**Description**
Developed a single threaded application used to perform a dot product on two matrices of size 2000 x 2000. Proceeded to create a multithreaded application that performs the same operations dividing each threads work among sections of rows for each matrix.

**Key Concepts**
- POSIX threads (pthreads)
- Thread creation and management
- Workload distribution strategies
- Performance optimization through parallelism
- Thread synchronization

**Performance**
- Matrix size: 2000 x 2000
- 1 Thread - Average Runtime: 21.27 s
- 2 Threads - Average Runtime: 17.06 s - Average Speedup: 1.25
- 4 Threads - Average Runtime: 11.53 s - Average Speedup: 1.85
- 8 Threads - Average Runtime: 12.33 s - Average Speedup: 1.72
- 16 Threads - Average Runtime: 12.68 s - Average Speedup: 1.68

**Files**
- [project2-matrix-multiplication/](/Project2) - Source code and performance benchmarks

**How to Run**
```
[Fill steps in here
```

<a name="Project3"></a>
## **Project 3: CPU Scheduler**
**Status:** 🚧 In Progress

<a name="Project4"></a>
## **Project 4: Linux Kernel Driver**
**Status:** 📋 Upcoming

<a name="Build-Run"></a>

<a name="Tech-Used"></a>
## **Technologies Used**
- **Language:** C
- **Build System**: Make
- **Threading:** POSIX Threads (pthreads)
- **Kernel Version:** 6.12
- **Development Environment:** Raspberry Pi OS (Ubuntu Based)

<a name="Learning-Outcomes"></a>
## **Learning Outcomes**
Through these projects, I gained hands-on experience with:
- Linux kernel internals and architecture
- System programming in C
- Concurrent programming and synchronization
- Operating system design principles
- Performance analysis and optimization
- Low-level hardware interaction

## **Authors**
- **Julio Anacleto - University of Washington Tacoma | Computer Engineering - Fall 2025**
- **Abdullah Almaroof - University of Washington Tacoma | Computer Engineering - Fall 2025**

## **Acknowledgements**
Course Instructor: Matt Tolentino
Course: TCES 420 - Principles of Operating Systems
Institution: University of Washington Tacoma

**Note:** This repository is for educational purposes. Please refer to your insitution's academic integrity policies before viewing or using this code.
