#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static const int CHUNK = 400;
static const int NSAMPLES = CHUNK * 1000;

static double my_log2(double x) {
    static const double LOG2SCALE = 1.442695040888963;
    return log(x) * LOG2SCALE;
}

static int num_hex_chars(int max_int) {
    int num_bits = (int) ceil(my_log2((double) max_int));
    return (num_bits + 3) / 4 ;
}

static void to_hex(int x, char* str, const int str_len) {
    static const char TOHEX[16] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
        'a', 'b', 'c', 'd', 'e', 'f' };

    str += str_len - 1;
    for (int i = 0; i < str_len; ++i) {
        *str-- = TOHEX[x & 15];
        x = x >> 4;
    }
}
static void create_file(const char* filename) {
    static const char FILE_DATA[32] = {
         0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 
        16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};

    FILE *f = fopen(filename, "wb");
    if (!f) {
        fprintf(stderr, "*** Unable to create file \"%s\"\n", filename);
        exit(1);
    }
    fwrite(FILE_DATA, 1, sizeof(FILE_DATA), f);
    fclose(f);
}

static void delete_file(const char* filename) {
    remove(filename);
}

int main(int argc, char** argv, char** envp) {
    if (argc != 2) {
        printf("Usage: %s root-folder\n", argv[0]);
        exit(1);
    }

    int hex_len = num_hex_chars(NSAMPLES - 1);
    size_t root_path_len = strlen(argv[1]);
    size_t path_len = root_path_len + 1 + hex_len;
    char* filename = (char*) malloc(path_len + 1);
    if (!filename) {
        fprintf(stderr, "*** Out of memory!\n");
        exit(1);
    }
    strncpy(filename, argv[1], root_path_len);
    filename[root_path_len] = '/';
    filename[path_len] = '\0';

    for (int file_no = 0; file_no < NSAMPLES; ++file_no) {
        to_hex(file_no, &filename[root_path_len + 1], hex_len);

        create_file(filename);
    }

    for (int file_no = 0; file_no < NSAMPLES; ++file_no) {
        to_hex(file_no, &filename[root_path_len + 1], hex_len);

        delete_file(filename);
    }
    free((void *) filename);
    
    return 0;
}
