# **Operating Systems Projects**
A collection of four projects completed for TCES 420 - Principles of Operating Systems at University of Washington Tacoma, covering fundamental operating system concepts including system calls, multithreading, scheduling, and kernel drivers.

## **Table of Contents**
- Project Overview
- Project 1: Custom System Call
- Project 2: Multithreaded Matrix Multiplication
- Project 3: CPU Scheduler
- Project 4: Linux Kernel Driver
- Build and Run Instructions
- Technologies Used
- Learning Outcomes

## **Project Overview**
This repository contains four projects that explore core operating system concepts:
1. **Custom System Call** - Kernel modification and system call implementation
2. **Multithreaded Matrix Multiplication** - Concurrent programming and thread management
3. **CPU Scheduler** - Process scheduling algorithms (In Progress)
4. **Linux Kernel Driver** - Device driver development (Upcoming)

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
- [project1-custom-syscall/](Operating-System-Projects/Project1) - Contains kernel patches and test program
**How to Run**
```
[Fill steps in here]
```

## **Project 2: Multithreaded Matrix Multiplication**
**Status:** ✔️ Completed
**Description**
Developed a single threaded application used to perform a dot product on two matrices of size 2000 x 2000. Proceeded to create a multithreaded application that performs the same operations dividing each threads work among sections of rows foe each matrix.
**Key Concepts**
- POSIX threads (pthreads)
- Thread creation and management
- Workload distribution strategies
- Performance optimization through parallelism
- Thread synchronization
**Performance**
- Matrix size: 2000 x 2000
- 1 Thread -
**Files**
- [project2-matrix-multiplication/](Operating-System-Projects/Project2) - Source code and performance benchmarks
**How to Run**
```
[Fill steps in here
```

## **Project 3: CPU Scheduler**
**Status:** 🚧 In Progress

## **Project 4: Linux Kernel Driver**
**Status:** 📋 Upcoming

## **Technologies Used**
- **Language:** C
- **Build System**: Make
- **Threading:** POSIX Threads (pthreads)
- **Kernel Version:** [Specify Linux kernel version]
- **Development Environment:** Raspberry Pi OS (Ubuntu Based)

## **Learning Outcomes**
Through these projects, I gained hands-on experience with:
- Linux kernel internals and architecture
- System programming in C
- Concurrent programming and synchronization
- Operating system design principles
- Performance analysis and optimization
- Low-level hardware interaction

## **Author**
Julio Anacleto
University of Washington Tacoma | Computer Engineering
Fall 2026

## **Acknowledgements**
Course Instructor: Matt Tolentino
Course: TCES 420 - Principles of Operating Systems
Institution: University of Washington Tacoma

**Note:** This repository is for educational purposes. Please refer to your insitution's academic integrity policies before viewing or using this code.
