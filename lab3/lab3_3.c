#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
void createNewProcess() {
  pid_t child_pid = fork();
  if (child_pid != 0) {
    fprintf(stdout, "%u create process %u\n", getpid(), child_pid);
  } else {
    return;
  }
}
int main() {
  pid_t child_pid, parent_pid;
  int i = 0;
  fprintf(stdout, "First process %i\n", parent_pid = (int)getpid());
  child_pid = fork();
  createNewProcess();
  createNewProcess();
  getchar();
  return 0;
}