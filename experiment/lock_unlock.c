#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// カウンターとミューテックス
int counter = 0;
pthread_mutex_t lock;

// スレッドで実行される関数
void* increment_counter(void* arg) {
	(void)arg;
    for (int i = 0; i < 1000000; i++) {
        // ミューテックスで排他制御
        // pthread_mutex_lock(&lock);
        counter++;
        // pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // ミューテックスの初期化
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("ミューテックス初期化に失敗しました\n");
        return 1;
    }

    // 2つのスレッドを作成
    pthread_create(&t1, NULL, increment_counter, NULL);
    pthread_create(&t2, NULL, increment_counter, NULL);

    // スレッドの終了を待つ
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // 結果を表示
    printf("カウンターの最終値: %d\n", counter);

    // ミューテックスを破棄
    pthread_mutex_destroy(&lock);

    return 0;
}
