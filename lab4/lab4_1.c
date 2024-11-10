#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();

  if (pid < 0) {
    perror("Ошибка fork");
    exit(EXIT_FAILURE);
  } else if (pid == 0) {
    execl("/bin/ls", "ls", "-l", NULL);
    perror("Ошибка exec");
    exit(EXIT_FAILURE);
  } else {
    printf(
        "Родительский процесс с PID: %d, создал дочерний процесс с PID: %d\n",
        getpid(), pid);
    wait(NULL);
  }

  return 0;
}