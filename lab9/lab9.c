#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

char sh[6];
int turn = 0;  // Переменная для спин-блокировки

void* Thread(void* pParams) {
  int counter = 0;
  while (1) {
    while (turn);  // Спин-блокировка
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
    turn = 1;  // Установка turn для другого потока
    counter++;
    usleep(100);
  }
  return NULL;
}

int main(void) {
  pthread_t thread_id;
  pthread_create(&thread_id, NULL, &Thread, NULL);

  while (1) {
    while (!turn);  // Ждем, пока поток не освободит turn
    printf("%s\n", sh);
    turn = 0;  // Возвращаем управление потоку
    usleep(100);
  }

  pthread_join(thread_id, NULL);
  return 0;
}