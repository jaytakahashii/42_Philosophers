#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philosopher {
    int id;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    long long last_meal_time;
    int meal_count;
    struct s_data *data;
} t_philosopher;

typedef struct s_data {
    int number_of_philosophers;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    long long start_time;
    int stop_simulation;
    t_philosopher *philosophers;
} t_data;

long long get_time_in_ms(void) {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000LL + time.tv_usec / 1000);
}

void log_event(t_data *data, int id, const char *event) {
    long long timestamp = get_time_in_ms() - data->start_time;
    pthread_mutex_lock(&data->print_lock);
    printf("%lld %d %s\n", timestamp, id, event);
    pthread_mutex_unlock(&data->print_lock);
}

void* philosopher_lifecycle(void* arg) {
    t_philosopher *philo = (t_philosopher*)arg;

    while (!philo->data->stop_simulation) {
        // フォークを取る
        pthread_mutex_lock(philo->left_fork);
        log_event(philo->data, philo->id, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        log_event(philo->data, philo->id, "has taken a fork");

        // 食事
        philo->last_meal_time = get_time_in_ms();
        log_event(philo->data, philo->id, "is eating");
        usleep(philo->data->time_to_eat * 1000);
        philo->meal_count++;

        // フォークを置く
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        // 睡眠
        log_event(philo->data, philo->id, "is sleeping");
        usleep(philo->data->time_to_sleep * 1000);

        // 考える
        log_event(philo->data, philo->id, "is thinking");
    }
    return NULL;
}

void* monitor_philosophers(void* arg) {
    t_data *data = (t_data*)arg;
    while (!data->stop_simulation) {
        for (int i = 0; i < data->number_of_philosophers; i++) {
            long long current_time = get_time_in_ms();
            if (current_time - data->philosophers[i].last_meal_time > data->time_to_die) {
                log_event(data, data->philosophers[i].id, "died");
                data->stop_simulation = 1;
                break;
            }
        }
        usleep(1000);  // 1ミリ秒ごとにチェック
    }
    return NULL;
}

void clean_up(t_data *data) {
    for (int i = 0; i < data->number_of_philosophers; i++) {
        pthread_join(data->philosophers[i].thread, NULL);
    }
    for (int i = 0; i < data->number_of_philosophers; i++) {
        pthread_mutex_destroy(&data->forks[i]);
    }
    pthread_mutex_destroy(&data->print_lock);
    free(data->forks);
    free(data->philosophers);
}

int init_data(t_data *data, int argc, char **argv) {
    if (argc < 5 || argc > 6) {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        return 1;
    }

    data->number_of_philosophers = atoi(argv[1]);
    data->time_to_die = atol(argv[2]);
    data->time_to_eat = atol(argv[3]);
    data->time_to_sleep = atol(argv[4]);
    data->number_of_times_each_philosopher_must_eat = (argc == 6) ? atoi(argv[5]) : -1;
    data->stop_simulation = 0;
    data->start_time = get_time_in_ms();
    
    data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
    data->philosophers = malloc(sizeof(t_philosopher) * data->number_of_philosophers);
    if (!data->forks || !data->philosophers) return 1;
    
    pthread_mutex_init(&data->print_lock, NULL);
    for (int i = 0; i < data->number_of_philosophers; i++) {
        pthread_mutex_init(&data->forks[i], NULL);
    }

    for (int i = 0; i < data->number_of_philosophers; i++) {
        data->philosophers[i].id = i + 1;
        data->philosophers[i].left_fork = &data->forks[i];
        data->philosophers[i].right_fork = &data->forks[(i + 1) % data->number_of_philosophers];
        data->philosophers[i].last_meal_time = data->start_time;
        data->philosophers[i].meal_count = 0;
        data->philosophers[i].data = data;
    }
    
    return 0;
}

int main(int argc, char **argv) {
    t_data data;

    if (init_data(&data, argc, argv)) {
        return 1;
    }

    pthread_t monitor_thread;
    pthread_create(&monitor_thread, NULL, monitor_philosophers, &data);

    for (int i = 0; i < data.number_of_philosophers; i++) {
        pthread_create(&data.philosophers[i].thread, NULL, philosopher_lifecycle, &data.philosophers[i]);
    }

    for (int i = 0; i < data.number_of_philosophers; i++) {
        pthread_join(data.philosophers[i].thread, NULL);
    }

    pthread_join(monitor_thread, NULL);
    clean_up(&data);
    
    return 0;
}
