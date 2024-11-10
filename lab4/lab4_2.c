#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  for (int i = 0; i < 3; i++) {
    pid_t pid = fork();

    if (pid < 0) {
      perror("Ошибка fork");
      exit(EXIT_FAILURE);
    } else if (pid == 0) {
      printf("Дочерний процесс #%d с PID: %d\n", i + 1, getpid());
      execl("/bin/sleep", "sleep", "2", NULL);
      perror("Ошибка exec");
      exit(EXIT_FAILURE);
    }
  }
  for (int i = 0; i < 3; i++) {
    wait(NULL);
  }
  printf("Все дочерние процессы завершены.\n");
  return 0;
}