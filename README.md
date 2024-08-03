
# Philosophers

## Overview

The **Philosophers** project introduces the basics of threading and concurrency control using mutexes and semaphores. The project simulates a scenario where philosophers sit around a table, alternating between eating, thinking, and sleeping. The challenge is to manage the sharing of forks (resources) without causing deadlocks or starvation.

## Summary

The project requires you to implement a simulation where philosophers eat, think, and sleep, ensuring that no philosopher starves. You will need to manage resource allocation and avoid data races.

## Global Rules

- **Global variables are forbidden.**
- Programs must take the following arguments:
  - `number_of_philosophers`: The number of philosophers and forks.
  - `time_to_die`: Time (in milliseconds) after which a philosopher dies if they haven't started eating.
  - `time_to_eat`: Time (in milliseconds) it takes for a philosopher to eat.
  - `time_to_sleep`: Time (in milliseconds) a philosopher spends sleeping.
  - `number_of_times_each_philosopher_must_eat` (optional): If all philosophers have eaten at least this many times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

- Each philosopher has a unique number, starting from 1.
- Philosopher number 1 sits next to philosopher number `number_of_philosophers`, forming a circular arrangement.
- State changes must be logged in the following format:
  - `timestamp_in_ms X has taken a fork`
  - `timestamp_in_ms X is eating`
  - `timestamp_in_ms X is sleeping`
  - `timestamp_in_ms X is thinking`
  - `timestamp_in_ms X died`
  - Replace `timestamp_in_ms` with the current timestamp in milliseconds and `X` with the philosopher's number.

- Messages should not overlap, and a death message should be displayed within 10ms of the actual event.

## Mandatory Part

### Program Name
`philo`

### Turn-in Files
- `Makefile`
- `*.h`
- `*.c`
- Directory: `philo/`

### Makefile Targets
- `NAME`
- `all`
- `clean`
- `fclean`
- `re`

### Arguments
- `number_of_philosophers`
- `time_to_die`
- `time_to_eat`
- `time_to_sleep`
- `[number_of_times_each_philosopher_must_eat]` (optional)

### External Functions
- `memset`
- `printf`
- `malloc`
- `free`
- `write`
- `usleep`
- `gettimeofday`
- `pthread_create`
- `pthread_detach`
- `pthread_join`
- `pthread_mutex_init`
- `pthread_mutex_destroy`
- `pthread_mutex_lock`
- `pthread_mutex_unlock`

### Description
The mandatory part requires implementing the philosophers' simulation using threads and mutexes to manage concurrent access to shared resources (forks). Each philosopher should be represented by a thread. Forks should be protected with a mutex to prevent concurrent access.

## Bonus Part

### Program Name
`philo_bonus`

### Turn-in Files
- `Makefile`
- `*.h`
- `*.c`
- Directory: `philo_bonus/`

### Makefile Targets
- `NAME`
- `all`
- `clean`
- `fclean`
- `re`

### Arguments
- `number_of_philosophers`
- `time_to_die`
- `time_to_eat`
- `time_to_sleep`
- `[number_of_times_each_philosopher_must_eat]` (optional)

### External Functions
- `memset`
- `printf`
- `malloc`
- `free`
- `write`
- `fork`
- `kill`
- `exit`
- `pthread_create`
- `pthread_detach`
- `pthread_join`
- `usleep`
- `gettimeofday`
- `waitpid`
- `sem_open`
- `sem_close`
- `sem_post`
- `sem_wait`
- `sem_unlink`

### Description
The bonus part extends the simulation by using processes instead of threads and semaphores instead of mutexes. All forks are represented by a semaphore, and each philosopher is a separate process. The main process is responsible for starting and monitoring the philosophers.

## Installation and Usage

To compile and run the programs, follow these steps:

1. Clone the repository:
   ```sh
   git clone https://github.com/aabderrafie/philosophers_42.git
   cd philosophers
   ```

2. Compile the mandatory part:
   ```sh
   cd philo
   make
   ```

3. Run the simulation:
   ```sh
   ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
   ```

4. Compile the bonus part:
   ```sh
   cd ../philo_bonus
   make
   ```

5. Run the bonus simulation:
   ```sh
   ./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
   ```

6. To clean object files:
   ```sh
   make clean
   ```

7. To clean object files and executables:
   ```sh
   make fclean
   ```

8. To recompile:
   ```sh
   make re
   ```

## Contributing

Contributions are welcome! Feel free to fork the repository, make your changes, and submit a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgements

Special thanks to the 42 Network and the community for their support and feedback.
