#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

char sh[6];
pthread_mutex_t mutex;

void* Thread(void* pParams) {
  int counter = 0;
  while (1) {
    pthread_mutex_lock(&mutex);
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
    pthread_mutex_unlock(&mutex);
    counter++;
    usleep(100000);
  }
  return NULL;
}

int main(void) {
  pthread_t thread_id;
  pthread_mutex_init(&mutex, NULL);
  pthread_create(&thread_id, NULL, &Thread, NULL);

  while (1) {
    pthread_mutex_lock(&mutex);
    printf("%s\n", sh);
    pthread_mutex_unlock(&mutex);
    usleep(100000);
  }

  pthread_join(thread_id, NULL);
  pthread_mutex_destroy(&mutex);
  return 0;
}