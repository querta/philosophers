# About philosophers
The project is solving the classic concurrency problem - [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) in different ways.

This project is a good lesson in optimizing C code. It is necessary to monitor CPU consumption so that the program can work with a large number of simultaneous processes.

The project consists of 2 programs.
* Philo: using mutexes and threads.
* Philo bonus: using multi-processes and semaphores

#### How to run:
1. Compile with `make` from 'philo' or 'philo_bonus' directory
2. Run using `./philo [number_of_philo] [time_to_die] [time_to_eat] [time_to_sleep] `
(e.g. `./philo 5 800 200 200`)
