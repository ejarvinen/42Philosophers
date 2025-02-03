# 42Philosophers
## Description
**Philosophers** is a project that explores the fundamentals of threading and process synchronization in C. The goal is to simulate the classic [Dining Philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) while managing concurrent execution using threads and mutexes.

## Features
- Simulates multiple philosophers alternating between eating, sleeping, and thinking.
- Implements threading and mutual exclusion to avoid race conditions.
- Ensures philosophers do not starve and properly manage shared resources.

## Installation
1. Clone the repository:
```
git clone https://github.com/ejarvinen/42Philosophers.git
```
2. Navigate to the project directory:
```
cd 42Philosophers
```
3. Compile the project:
```
make
```
## Usage
Run the program with the following syntax:
```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
Example:
```
./philo 5 800 200 200
```
This runs a simulation with 5 philosophers who die if they do not eat within 800ms, take 200ms to eat, and sleep for 200ms.

### Output Format
- `timestamp_in_ms X has taken a fork`
- `timestamp_in_ms X is eating`
- `timestamp_in_ms X is sleeping`
- `timestamp_in_ms X is thinking`
- `timestamp_in_ms X died`

Where `X` is the philosopher number.
