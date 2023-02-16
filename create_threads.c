#include <stdio.h>
#include <pthread.h>

static const int CHUNK = 2000;
static const int NSAMPLES = CHUNK * 1000;

typedef pthread_t thread_t;

static void* thread_fun(void* arg) {
    (void) arg;
    return (void*) 0;
}

static thread_t create_thread() {
    thread_t result;
    pthread_create(&result, (const pthread_attr_t*)0, thread_fun, (void*) 0);
    return result;
}

static void join_thread(thread_t thread) {
    pthread_join(thread, (void**) 0);
}

int main(int argc, char** argv, char** envp) {
    thread_t threads[CHUNK];
    for (int i = 0; i < NSAMPLES; i++) {
        threads[i % CHUNK] = create_thread();
        if (i % CHUNK == CHUNK - 1) {
            for (int j = 0; j < CHUNK; ++j) {
                join_thread(threads[j]);
            }
        }
    }
    return 0;
}
