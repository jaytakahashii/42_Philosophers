<h1 align="center">
	PHILOSOPHERS (Projects at 42tokyo)
</h1>

<p align="center">
	<b><i>Final Score: 100/100</i></b><br>
</p>

# 💡 About the project

> I never thought philosophy would be so deadly.
> In this project, you will learn the basics of threading a process.
> You will see how to create threads and you will discover mutexes.

## Overview
Philosophers is a project from the 42 curriculum that introduces students to the fundamentals of concurrent programming. The goal is to simulate the dining philosophers problem, a classic synchronization problem in computer science. Through this project, you will explore how to manage multiple threads, prevent deadlocks, and handle synchronization using mutexes.

## Key Features
- **Thread Management**: Create and manage multiple threads to simulate philosophers who think, eat, and sleep.
- **Mutexes for Synchronization**: Use mutexes to avoid race conditions and ensure that resources (forks) are shared safely among threads.
- **Deadlock Prevention**: Implement strategies to prevent deadlocks, ensuring that all philosophers get a chance to eat.
- **Time Management**: Handle precise timing to simulate the activities of philosophers and ensure that the program runs in real-time.

## Objectives
- **Understanding Concurrency**: Learn the basics of concurrent programming and how to manage multiple threads within a single process.
- **Synchronization**: Gain experience in using synchronization primitives like mutexes to coordinate thread activities.
- **Avoiding Deadlocks**: Develop techniques to prevent deadlocks in multi-threaded applications, ensuring smooth operation.
- **Resource Management**: Efficiently manage shared resources and avoid common pitfalls like race conditions and starvation.

## Challenges
- **Thread Synchronization**: Ensuring that threads operate without interfering with each other, particularly when accessing shared resources.
- **Deadlock Avoidance**: Implementing a system that prevents deadlocks while allowing all philosophers to eat.
- **Precise Timing**: Handling time-sensitive operations accurately to maintain the simulation's realism.
- **Memory Management**: Properly allocate and deallocate memory to prevent leaks and ensure the stability of the program.

# 🛠️ Usage

### Requirements

- The library is written in C language and needs the **`cc` compiler**.

### Instructions

**1. Compiling the code**

To compile the project code, go to its path and run:

```shell
$ make
```

**2, Run**
after creating the executable file philosophers, you can run it with the following command:
```shell
$ ./philosophers number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**+α. Cleaning all binary and executable files**
To clean all files generated while doing a make, go to the path and run:
```shell
$ make fclean
```
