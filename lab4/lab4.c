#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();

  if (pid < 0) {
    perror("Ошибка fork");
    exit(EXIT_FAILURE);
  } else if (pid == 0) {
    printf("Дочерний процесс с PID: %d\n", getpid());
    exit(EXIT_SUCCESS);
  } else {
    printf(
        "Родительский процесс с PID: %d, создал дочерний процесс с PID: %d\n",
        getpid(), pid);
  }

  return 0;
}