#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define NUM_PHILOSOPHERS 5
#define MAX_EATING_TIME 5

void *philosopher_action(void *arg) {
    int phil_id = *(int *)arg;
    pthread_mutex_t *left_chopstick = (pthread_mutex_t *)arg + 1;
    pthread_mutex_t *right_chopstick = (pthread_mutex_t *)arg + 2;
    struct timeval *last_meal_time = (struct timeval *)arg + 3;

    while (1) {
        // Think (simulate by sleeping)
        usleep(rand() % 1000);

        // Pick up chopsticks
        pthread_mutex_lock(left_chopstick);
        pthread_mutex_lock(right_chopstick);

        // Eat (simulate by sleeping)
        gettimeofday(last_meal_time, NULL);
        printf("Philosopher %d is eating.\n", phil_id);
        usleep(rand() % 1000);

        // Put down chopsticks
        pthread_mutex_unlock(right_chopstick);
        pthread_mutex_unlock(left_chopstick);
    }

    return NULL;
}

void *check_philosophers(void *arg) {
    pthread_mutex_t *chopsticks = (pthread_mutex_t *)arg;
    struct timeval *last_meal_times = (struct timeval *)arg + NUM_PHILOSOPHERS * 2;

    while (1) {
        for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
            struct timeval current_time;
            gettimeofday(&current_time, NULL);
            if (current_time.tv_sec - last_meal_times[i].tv_sec > MAX_EATING_TIME) {
                printf("Philosopher %d has died.\n", i);
                exit(0);
            }
        }
        usleep(1000);
    }

    return NULL;
}

int main() {
    // Initialize chopstick mutexes and last meal time array
    pthread_mutex_t chopsticks[NUM_PHILOSOPHERS];
    struct timeval last_meal_times[NUM_PHILOSOPHERS];
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
        gettimeofday(&last_meal_times[i], NULL);
    }

    // Initialize philosopher threads
    pthread_t philosopher_threads[NUM_PHILOSOPHERS];
    int philosopher_args[NUM_PHILOSOPHERS][5];
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_args[i][0] = i;  // philosopher ID
        philosopher_args[i][1] = (int)&chopsticks[i];  // left chopstick mutex
        philosopher_args[i][2] = (int)&chopsticks[(i + 1) % NUM_PHILOSOPHERS];  // right chopstick mutex
        philosopher_args[i][3] = (int)&last_meal_times[i];  // last meal time
        philosopher_args[i][4] = 0;  // placeholder for future arguments
        pthread_create(&philosopher_threads[i], NULL, philosopher_action, philosopher_args[i]);
    }

    // Start checking thread
    pthread_t check_thread;
    void *check_args[2];
    check_args[0] = chopsticks;
    check_args[1] = last_meal_times;
    pthread_create(&check_thread, NULL, check_philosophers, check_args);// Wait for philosopher threads to finish (will never happen)
for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
    pthread_join(philosopher_threads[i], NULL);
}

return 0;

