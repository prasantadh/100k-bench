#include <stdio.h>
#include <stdlib.h>

#define CHUNK 100
static const int NSAMPLES = CHUNK * 1000;

static void * s_addresses[CHUNK];

int main(int argc, char** argv, char** envp) {
    for (int i = 0; i < NSAMPLES; ++i) {
        const size_t memory_size = ((i % 32) + 1) * 8;
        s_addresses[i % CHUNK] = malloc(memory_size);
        ((char *) s_addresses[i % CHUNK])[0] = 1;

        if ( i % CHUNK == CHUNK - 1) {
            for (int j = 0; j < CHUNK; ++j) {
                free(s_addresses[j]);
            }
        }
    }
    return 0;
}
