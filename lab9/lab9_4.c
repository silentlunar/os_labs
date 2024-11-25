#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>

char sh[6];
atomic_int lock = 0;

void* Thread(void* pParams);
void acquire_lock();
void release_lock();

int main(void) {
  pthread_t thread_id;
  pthread_create(&thread_id, NULL, &Thread, NULL);

  while (1) {
    // acquire_lock();  // Захват блокировки
    printf("%s\n", sh);
    // release_lock();  // Освобождение блокировки
  }
}

void* Thread(void* pParams) {
  int counter = 0;
  while (1) {
    // acquire_lock();  // Захват блокировки
    if (counter % 2) {
      sh[0] = 'H';
      sh[1] = 'e';
      sh[2] = 'l';
      sh[3] = 'l';
      sh[4] = 'o';
      sh[5] = '\0';
    } else {
      sh[0] = 'B';
      sh[1] = 'y';
      sh[2] = 'e';
      sh[3] = '_';
      sh[4] = 'u';
      sh[5] = '\0';
    }
    // release_lock();  // Освобождение блокировки
    counter++;
  }
  return NULL;
}

void acquire_lock() {
  while (atomic_exchange(&lock, 1)) {
    // Ожидание, пока блокировка не будет освобождена
  }
}

void release_lock() {
  atomic_store(&lock, 0);  // Освобождение блокировки
}