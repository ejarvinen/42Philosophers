# 42Philosophers
A 42 school project to simulate the [Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem). In the imaginary scenario `N` number of philosophers are sitting at the same table each having their own plate and a fork. The philosophers will eat, sleep and think in cycles, but a philosopher can eat only with two forks. The objective of this program is to keep the philosophers alive. The program can be run like this:
```
./philo N D E S M
```
where
- `N` is the number of philosophers at the table
- `D` is `time_to_die` in milliseconds (if more time than `time_to_die` has passed since a philosopher last ate, it will die)
- `E` is `time_to_eat` in milliseconds (the time it takes for a philosopher to consume a meal)
- `S` is `time_to_sleep` in milliseconds (the time it takes for a philosopher to sleep)
- `M` is the minimum number of meals each philosopher has to eat before simulation stops (optional argument)

The same number of threads will be created as the number of philosophers each running the same eat-sleep-think routine. The forks are represented by mutexes and the whole show is being monitored by the main program.

## How to run
_This project has been developed on Linux._

`git clone` and `cd` into desired directory. Run `make` in the same directory. Run executable `./philo` with the above mentioned arguments such as:
```
./philo 2 180 60 60
```
> will run infinitely
```
./philo 10 180 60 60
```
> someone will die
```
./philo 3 250 60 60 5
```
> runs until all philosophers have eaten at least 5 meals

The program outputs all actions happening at the table on the terminal in the following format:
```
[time_stamp_in_milliseconds] [philosopher's id] [action]
```
