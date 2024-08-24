#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THINKING 2
#define HUNGRY 1
#define EATING 0

typedef struct {
    int *state;
    pthread_mutex_t mutex;
    pthread_mutex_t *forks;
    int num_philosophers;
} Table;

typedef struct {
    int id;
    Table *table;
} Philosopher;

void test(Table *table, int phnum) {
    int LEFT = (phnum + table->num_philosophers - 1) % table->num_philosophers;
    int RIGHT = (phnum + 1) % table->num_philosophers;

    if (table->state[phnum] == HUNGRY &&
        table->state[LEFT] != EATING &&
        table->state[RIGHT] != EATING) {
        table->state[phnum] = EATING;
        printf("Philosopher %d takes fork %d and %d\n", phnum + 1, LEFT + 1, phnum + 1);
        printf("Philosopher %d is Eating\n", phnum + 1);
        usleep(2000); // 食事中の時間を表す
    }
}

void take_fork(Philosopher *philosopher) {
    Table *table = philosopher->table;
    int id = philosopher->id;

    pthread_mutex_lock(&table->mutex);
    table->state[id] = HUNGRY;
    printf("Philosopher %d is Hungry\n", id + 1);

    test(table, id);

    pthread_mutex_unlock(&table->mutex);

    pthread_mutex_lock(&table->forks[id]); // フォークを待つ
}

void put_fork(Philosopher *philosopher) {
    Table *table = philosopher->table;
    int id = philosopher->id;
    int LEFT = (id + table->num_philosophers - 1) % table->num_philosophers;
    int RIGHT = (id + 1) % table->num_philosophers;

    pthread_mutex_lock(&table->mutex);

    table->state[id] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n", id + 1, LEFT + 1, id + 1);
    printf("Philosopher %d is thinking\n", id + 1);

    test(table, LEFT);
    test(table, RIGHT);

    pthread_mutex_unlock(&table->forks[id]); // フォークを開放

    pthread_mutex_unlock(&table->mutex);
}

void* philosopher(void* arg) {
    Philosopher *philosopher = (Philosopher*)arg;

    while (1) {
        usleep(1000); // 考える時間
        take_fork(philosopher);
        usleep(1000); // 食事後の処理
        put_fork(philosopher);
    }
}

int main() {
    int num_philosophers;
    printf("Enter the number of philosophers: ");
    scanf("%d", &num_philosophers);

    pthread_t *thread_id = malloc(num_philosophers * sizeof(pthread_t)); // スレッドIDを格納する配列
    Table table; // テーブルの状態を表す構造体
    Philosopher *philosophers = malloc(num_philosophers * sizeof(Philosopher)); // 哲学者を表す構造体の配列

    table.state = malloc(num_philosophers * sizeof(int)); // 哲学者の状態を表す配列 (THINKING, HUNGRY, EATING)
    table.forks = malloc(num_philosophers * sizeof(pthread_mutex_t)); // フォークを表すmutexの配列
    table.num_philosophers = num_philosophers; // 哲学者の数

    pthread_mutex_init(&table.mutex, NULL); // テーブルのmutexを初期化

    for (int i = 0; i < num_philosophers; i++) {
        table.state[i] = THINKING;
        pthread_mutex_init(&table.forks[i], NULL); // フォークのmutexを初期化
        philosophers[i].id = i; // 哲学者のID
        philosophers[i].table = &table;
    }

    for (int i = 0; i < num_philosophers; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &philosophers[i]); // 哲学者のスレッドを生成 (スレッドID, スレッドの属性, 関数, 関数に渡す引数)
        printf("Philosopher %d is thinking\n", i + 1);
    }

    for (int i = 0; i < num_philosophers; i++) {
        pthread_join(thread_id[i], NULL); // スレッドの終了を待つ
    }

    pthread_mutex_destroy(&table.mutex);
    for (int i = 0; i < num_philosophers; i++) {
        pthread_mutex_destroy(&table.forks[i]); // mutexを破棄
    }

    free(table.state);
    free(table.forks);
    free(philosophers);
    free(thread_id);

    return 0;
}
