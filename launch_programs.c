#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

static const int CHUNK = 400;
static const int NSAMPLES = CHUNK * 1000;

typedef pid_t process_t;

static process_t create_process(const char* arg0, int process_no) {

    pid_t pid = fork();
    if (pid == 0) {
        execlp(arg0, arg0, "-", (char*) 0);
    } else if (pid < 0) {
        fprintf(stderr, "*** Unable to create process no. %d\n", process_no);
        exit(1);
    }

    return (process_t) pid;
}

static void wait_process(process_t pid) {
    waitpid(pid, (int *) 0, 0);
}

int main(int argc, char** argv, char** envp) {

    if (argc > 1) {
        exit(0);
    }

    process_t processes[CHUNK];

    for (int i = 0; i < NSAMPLES; ++i) {
        processes[i % CHUNK] = create_process(argv[0], i);
        
        if (i % CHUNK == CHUNK - 1) {
            for (int j = 0; j < CHUNK; ++j) {
                wait_process(processes[j]);
            }
        }
    }

    return 0;
}
