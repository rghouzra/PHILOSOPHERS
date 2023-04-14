# PHILOSOPPHERS
 42 Philosophers project 

resources:

https://www.youtube.com/watch?v=NbwbQQB7xNQ

https://www.youtube.com/watch?v=trdXKhWAGdg


https://www.notion.so/Philosophers-2b872948598e4f0cba91c66d8b5ba821

https://github.com/joycemacksuele

https://grizzly-muenster-737.notion.site/Philosophers-55c385e0a6224d629c86231821e3ce10

https://github.com/laisarena

https://github.com/laisarena

https://stackoverflow.com/questions/60932647/gettimeofday-why-use-both-seconds-and-microseconds

https://github.com/GOAT095/philosophers-tester

https://github.com/GOAT095/philosophers-tester/blob/master/delay_o_meter.py

https://randu.org/tutorials/threads/

https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2

https://www.youtube.com/watch?v=d9s_d28yJq0

https://www.youtube.com/watch?v=HDohXvS6UIk

https://www.youtube.com/watch?v=-i8Kzuwr4T4


http://files.kipr.org/gcer/2009/proceedings/Myers_ApplicationPthreads.pdf

https://www.youtube.com/watch?v=GNw3RXr-VJk


https://www.youtube.com/watch?v=sDLQWivf1-I

https://miro.com/app/board/o9J_l0AjIkc=/

https://github.com/lorenuars19

https://nafuka11.github.io/philosophers-visualizer/
/*
The implementation of the Dining Philosophers problem in the provided code seems to have covered the basic structure, but there are several potential issues and areas for improvement. Here's a list of observations and suggestions:

    Deadlock prevention: One common issue with the Dining Philosophers problem is the possibility of deadlocks. In the philo_take_fork function, you lock both the left and right forks sequentially. This could lead to a deadlock if all philosophers grab their left fork at the same time. To avoid this, you can use an asymmetric approach where philosophers with an odd ID grab their left fork first and those with an even ID grab their right fork first. This ensures that at least one philosopher can eat.

    Use of printf: The use of printf statements for tracing the status of the philosophers might lead to unexpected behavior, as printf is not thread-safe. Instead, you can use write or wrap the printf calls with a mutex to make them thread-safe.

    ft_usleep implementation: The ft_usleep function may cause busy waiting since the while loop keeps checking the time without giving other threads a chance to run. Instead of using usleep(time) within the loop, consider using usleep(1000) or another small value to avoid hogging the CPU.

    Memory management: The code has a commented "TODO" mentioning memory allocation. Make sure to clean up and free all allocated memory before exiting the program, including the memory allocated for philosophers, forks, and mutexes.

    Error checking: Add error checking for functions that could fail, such as pthread_create, pthread_mutex_lock, and pthread_mutex_unlock. This will help you identify issues more quickly and make the code more robust.

    Code organization: It might be helpful to separate the logic for creating and initializing the philosophers, forks, and mutexes into separate functions. This will make the code more modular and easier to read.

    Infinite loop: The while (1) loop in the philosophers_routine function might be better served with a condition tied to the program's exit criteria, such as the number of times a philosopher has eaten. This will help ensure a clean exit under normal circumstances.

    Variable naming: Some variables have unclear names or use a mix of naming conventions. Consider using more descriptive names and a consistent naming convention for better readability.

*/