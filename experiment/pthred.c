#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N

int state[N];
int phil[N] = { 0, 1, 2, 3, 4 };

pthread_mutex_t mutex;
pthread_mutex_t forks[N];

void test(int phnum) {
    if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[phnum] = EATING;
        
        usleep(200000);  // Sleep for 200ms (equivalent to sleep(2) with more precision)

        printf("Philosopher %d takes fork %d and %d\n", phnum + 1, LEFT + 1, phnum + 1);
        printf("Philosopher %d is Eating\n", phnum + 1);
    }
}

void take_fork(int phnum) {
    pthread_mutex_lock(&mutex);

    state[phnum] = HUNGRY;
    printf("Philosopher %d is Hungry\n", phnum + 1);

    test(phnum);

    pthread_mutex_unlock(&mutex);

    // If unable to eat, wait until the forks are available
    pthread_mutex_lock(&forks[phnum]);
}

void put_fork(int phnum) {
    pthread_mutex_lock(&mutex);

    state[phnum] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n", phnum + 1, LEFT + 1, phnum + 1);
    printf("Philosopher %d is thinking\n", phnum + 1);

    test(LEFT);
    test(RIGHT);

    pthread_mutex_unlock(&forks[phnum]);
    pthread_mutex_unlock(&mutex);
}

void* philosopher(void* num) {
    int* i = num;

    while (1) {
        usleep(100000);  // Sleep for 100ms (simulating thinking)

        take_fork(*i);
        usleep(100000);  // Sleep for 100ms (simulating eating)
        put_fork(*i);
    }
}

int main() {
    int i;
    pthread_t thread_id[N];

    // Initialize mutexes
    pthread_mutex_init(&mutex, NULL);
    memset(state, THINKING, sizeof(state));
    for (i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    for (i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }

    for (i = 0; i < N; i++) {
        pthread_join(thread_id[i], NULL);
    }

    // Destroy mutexes
    pthread_mutex_destroy(&mutex);
    for (i = 0; i < N; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
