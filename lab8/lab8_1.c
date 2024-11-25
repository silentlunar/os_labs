#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000000

typedef struct {
  int start;
  int end;
  long long result;
} ThreadData;

void* partial_sum(void* arg) {
  ThreadData* data = (ThreadData*)arg;
  data->result = 0;
  for (int i = data->start; i < data->end; ++i) {
    data->result += i + 1;
  }
  return NULL;
}

int main() {
  pthread_t threads[2];
  ThreadData thread_data[2];

  thread_data[0].start = 0;
  thread_data[0].end = SIZE / 2;

  thread_data[1].start = SIZE / 2;
  thread_data[1].end = SIZE;

  clock_t start_time = clock();

  pthread_create(&threads[0], NULL, partial_sum, &thread_data[0]);
  pthread_create(&threads[1], NULL, partial_sum, &thread_data[1]);

  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);

  long long total_sum = thread_data[0].result + thread_data[1].result;

  clock_t end_time = clock();

  printf("Итоговая сумма: %lld\n", total_sum);
  printf("Подсчитанное время (Pthreads): %f seconds\n",
         (double)(end_time - start_time) / CLOCKS_PER_SEC);

  return 0;
}