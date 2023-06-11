Philosophers
Table of Contents

    Introduction
    Problem Statement
    Solution Approach
    Requirements
    Usage
    Contributing
    License

Introduction

Welcome to the 42 Philosophers project! This project is inspired by the classical problem of the Dining Philosophers, which involves a set of philosophers sitting around a table and thinking and eating. The goal of this project is to create a simulation where multiple philosophers can coexist and perform their activities without deadlocks or resource starvation.
Problem Statement

The Dining Philosophers problem presents the challenge of avoiding deadlock and resource contention in a concurrent system. In this scenario, there are N philosophers sitting around a circular table, and each philosopher alternates between thinking and eating. There are only a limited number of shared resources, such as forks, that the philosophers need to use while eating.

The problem arises when each philosopher picks up the fork on their left and waits for the fork on their right to be available. If all philosophers simultaneously pick up their left forks, they will be stuck in a deadlock state, as no one can proceed with eating. The objective is to design a solution that allows the philosophers to eat without deadlocks or starvation.
Solution Approach

In this project, we provide two different solutions to the Dining Philosophers problem:
Mandatory Part:

    Each philosopher is represented as a separate thread.
    We use mutexes to synchronize access to the shared forks.
    The solution ensures that the philosophers can eat without deadlock or starvation.

Bonus Part:

    Each philosopher is represented as a separate process.
    We use semaphores to synchronize access to the shared forks.
    The solution ensures that the philosophers can eat without deadlock or starvation.

Requirements

    C programming language
    POSIX threads library (pthread)
    GCC compiler (or any other C compiler)
    Make utility

Usage

To run the simulation for the mandatory part (using threads and mutexes), follow these steps:

    Clone the repository:

    bash

git clone https://github.com/rghouzra/PHILOSOPHERS.git

Navigate to the philo directory:

bash

cd PHILOSOPHERS/philo

Compile the source code:

go

make

Run the simulation with the desired parameters:

bash

    ./philo num_philosophers time_to_die time_to_eat time_to_sleep [num_times_each_must_eat]

        num_philosophers: The number of philosophers (3 or more).
        time_to_die: The time in milliseconds after which a philosopher dies if they haven't eaten.
        time_to_eat: The time in milliseconds it takes for a philosopher to finish eating.
        time_to_sleep: The time in milliseconds a philosopher spends sleeping after eating.
        num_times_each_must_eat (optional): The number of times each philosopher must eat before the simulation ends (if not specified, philosophers can eat indefinitely).

    Observe the simulation output and analyze the behavior of the philosophers.

To run the simulation for the bonus part (using processes and semaphores), follow the same steps as above but navigate to the philo_bonus directory (cd PHILOSOPHERS/philo_bonus).Philosophers
Table of Contents

    Introduction
    Problem Statement
    Solution Approach
    Requirements
    Usage
    Contributing
    License

Introduction

Welcome to the 42 Philosophers project! This project is inspired by the classical problem of the Dining Philosophers, which involves a set of philosophers sitting around a table and thinking and eating. The goal of this project is to create a simulation where multiple philosophers can coexist and perform their activities without deadlocks or resource starvation.
Problem Statement

The Dining Philosophers problem presents the challenge of avoiding deadlock and resource contention in a concurrent system. In this scenario, there are N philosophers sitting around a circular table, and each philosopher alternates between thinking and eating. There are only a limited number of shared resources, such as forks, that the philosophers need to use while eating.

The problem arises when each philosopher picks up the fork on their left and waits for the fork on their right to be available. If all philosophers simultaneously pick up their left forks, they will be stuck in a deadlock state, as no one can proceed with eating. The objective is to design a solution that allows the philosophers to eat without deadlocks or starvation.
Solution Approach

In this project, we provide two different solutions to the Dining Philosophers problem:
Mandatory Part:

    Each philosopher is represented as a separate thread.
    We use mutexes to synchronize access to the shared forks.
    The solution ensures that the philosophers can eat without deadlock or starvation.

Bonus Part:

    Each philosopher is represented as a separate process.
    We use semaphores to synchronize access to the shared forks.
    The solution ensures that the philosophers can eat without deadlock or starvation.

Requirements

    C programming language
    POSIX threads library (pthread)
    GCC compiler (or any other C compiler)
    Make utility

Usage

To run the simulation for the mandatory part (using threads and mutexes), follow these steps:

    Clone the repository:

    bash

git clone https://github.com/rghouzra/PHILOSOPHERS.git

Navigate to the philo directory:

bash

cd PHILOSOPHERS/philo

Compile the source code:

go

make

Run the simulation with the desired parameters:

bash

    ./philo num_philosophers time_to_die time_to_eat time_to_sleep [num_times_each_must_eat]

        num_philosophers: The number of philosophers (3 or more).
        time_to_die: The time in milliseconds after which a philosopher dies if they haven't eaten.
        time_to_eat: The time in milliseconds it takes for a philosopher to finish eating.
        time_to_sleep: The time in milliseconds a philosopher spends sleeping after eating.
        num_times_each_must_eat (optional): The number of times each philosopher must eat before the simulation ends (if not specified, philosophers can eat indefinitely).

    Observe the simulation output and analyze the behavior of the philosophers.

To run the simulation for the bonus part (using processes and semaphores), follow the same steps as above but navigate to the philo_bonus directory (cd PHILOSOPHERS/philo_bonus).
