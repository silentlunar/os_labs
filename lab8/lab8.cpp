#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#define SIZE 1000000

struct ThreadData {
  int start;
  int end;
  long long result;
};

void partial_sum(ThreadData& data) {
  data.result = 0;
  for (int i = data.start; i < data.end; ++i) {
    data.result += i + 1;
  }
}

int main() {
  std::vector<std::thread> threads(2);
  ThreadData thread_data[2];

  thread_data[0].start = 0;
  thread_data[0].end = SIZE / 2;

  thread_data[1].start = SIZE / 2;
  thread_data[1].end = SIZE;

  auto start_time = std::chrono::high_resolution_clock::now();

  threads[0] = std::thread(partial_sum, std::ref(thread_data[0]));
  threads[1] = std::thread(partial_sum, std::ref(thread_data[1]));

  for (auto& t : threads) {
    t.join();
  }

  long long total_sum = thread_data[0].result + thread_data[1].result;

  auto end_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end_time - start_time;

  std::cout << "Total Sum: " << total_sum << "\n";
  std::cout << "Elapsed Time (std::thread): " << elapsed.count()
            << " seconds\n";

  return 0;
}