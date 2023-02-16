#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

static const int CHUNK = 400;
static const int NSAMPLES = CHUNK * 1000;

int main(int argc, char** argv, char** envp) {
    pid_t processes[CHUNK];
    for (int i = 0; i < NSAMPLES; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            exit(0);
        } else if (pid > 0) {
            processes[i % CHUNK] = pid;
        } else {
            fprintf(stderr, "*** Unable to create process no. %d\n", i);
            exit(1);
        }
        if (i % CHUNK == CHUNK - 1) {
            for (int j = 0; j < CHUNK; ++j) {
                waitpid(processes[j], (int *) 0, 0);

            }
        }
    }
    return 0;
}
