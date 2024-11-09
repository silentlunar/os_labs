#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t child_pid;
  pid_t parent_pid;
  double s = 0.0;
  FILE* fp;

  child_pid = fork();
  fp = fopen("test.dat", "a+");

  if (child_pid != 0) {
    s += 3.14;
    fprintf(fp, "CHILD: %i s=%g &s=%p fp=%p\n", (int)getpid(), s, (void*)&s,
            (void*)fp);
  } else {
    s += 2.72;
    fprintf(fp, "PARENT: %i s=%g &s=%p fp=%p\n", (int)getpid(), s, (void*)&s,
            (void*)fp);
  }

  fclose(fp);
  return 0;
}