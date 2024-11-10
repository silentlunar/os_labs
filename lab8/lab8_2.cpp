#include <pthread.h>

#include <chrono>
#include <iostream>
#include <numeric>

#define SIZE 1000000

struct ThreadData {
  int start;
  int end;
  long long result;
};

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

  auto start_time = std::chrono::high_resolution_clock::now();

  pthread_create(&threads[0], NULL, partial_sum, (void*)&thread_data[0]);
  pthread_create(&threads[1], NULL, partial_sum, (void*)&thread_data[1]);

  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);

  long long total_sum = thread_data[0].result + thread_data[1].result;

  auto end_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end_time - start_time;

  std::cout << "Total Sum: " << total_sum << "\n";
  std::cout << "Elapsed Time (Pthreads): " << elapsed.count() << " seconds\n";

  return 0;
}