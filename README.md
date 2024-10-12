# Philosophers

![image](https://github.com/user-attachments/assets/e9cec3d6-5d9f-4ad7-984a-ceb9316b178b)

This project implements a solution to the classic "Dining Philosophers Problem," a well-known metaphor in computer science that illustrates issues of concurrency and process synchronization.

# Dining Philosophers Problem

Five philosophers sit around a circular table, each with a plate of spaghetti in front of them. The spaghetti is so slippery that to eat it, a philosopher needs two Fs (called "chopsticks" in this case). Between every two plates, there is a chopstick, meaning there are as many chopsticks as there are philosophers.

A philosopher's life consists of alternating between thinking and eating. When a philosopher feels hungry, they try to pick up the left chopstick and, if successful, try to pick up the right one. If they manage to grab both chopsticks, they eat for a while, then put the chopsticks down and continue thinking.

# Key Concepts
The main challenge in this scenario is avoiding deadlocks, starvation, and race conditions, where multiple philosophers attempt to access the same resources (chopsticks) simultaneously. Without proper management, all philosophers could end up waiting indefinitely for access to the resources, causing a deadlock.

#### Solution
The solution implemented in this project is based on the management of semaphores and shared memory, which are essential for process synchronization in operating systems.

#### Semaphores
Each chopstick is modeled as a resource controlled by a binary semaphore. A semaphore has two states:

- 0: The chopstick is currently being used by another philosopher.
- 1: The chopstick is available.

#### Philosophers as processes
Each philosopher is represented as an individual process attempting to acquire two chopsticks (resources) in order to eat. If both chopsticks are available, the philosopher eats for a specified time, then releases the chopsticks and resumes thinking.

#### Avoiding deadlock
The implementation ensures that philosophers do not enter a deadlock by efficiently managing the acquisition of chopsticks through semaphores. Additionally, the option to set the number of times each philosopher must eat ensures the program does not run indefinitely.

### How to use: 
```
$> make 
```
```
$> ./philosophers number_philosopher time_D time_E time_S [number_of_time_each_philosophers_must_eat] arguments in square brackets are not required (number_of_time_each_philosophers_must_eat)
```
- number_of_philosophers: The number of philosophers (and chopsticks) participating in the simulation.
- time_D: Time in milliseconds a philosopher can go without eating before dying.
- time_E: Time in milliseconds a philosopher spends eating.
- time_S: Time in milliseconds a philosopher spends sleeping after eating.
- [number_of_times_each_philosopher_must_eat]: (Optional) The number of times each philosopher must eat before the program finishes. If not provided, the simulation continues indefinitely until the philosophers die.

#### example: 
```
$>./philosophers 4 500 200 200
```
# Extras
Through this implementation, you can explore how operating systems handle synchronization and resource allocation, while also testing the scalability and performance of the solution in different scenarios. The project provides a solid foundation for understanding concurrency issues and lays the groundwork for more advanced synchronization techniques. Whether you’re new to concurrency or looking to deepen your understanding, this implementation of the Dining Philosophers Problem offers a practical example.

-Born2code

![42madrid](https://github.com/ismaelucky342/Born2code/assets/153450550/3a377f34-9156-4eff-b04b-71c4b128523e)

