#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t child1, child2;

  child1 = fork();
  if (child1 < 0) {
    perror("Ошибка fork() для первого дочернего процесса");
    exit(1);
  }

  if (child1 == 0) {
    printf("Дочерний процесс 1 (PID: %d)\n", getpid());
    execlp("/bin/ls", "ls", NULL);
    perror("Ошибка execlp() для ls");
    exit(1);
  } else {
    child2 = fork();
    if (child2 < 0) {
      perror("Ошибка fork() для второго дочернего процесса");
      exit(1);
    }

    if (child2 == 0) {
      printf("Дочерний процесс 2 (PID: %d)\n", getpid());
      execlp("/bin/ps", "ps", NULL);
      perror("Ошибка execlp() для ps");
      exit(1);
    } else {
      printf("Родительский процесс (PID: %d)\n", getpid());
      wait(NULL);
      wait(NULL);
      printf("Оба дочерних процесса завершились.\n");
    }
  }

  return 0;
}