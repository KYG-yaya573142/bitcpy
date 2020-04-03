#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "bitcpy.h"
#include <time.h>

static uint8_t output[800], input[800];

static inline void dump_8bits(uint8_t _data)
{
    for (int i = 0; i < 8; ++i)
        printf("%d", (_data & (0x80 >> i)) ? 1 : 0);
}
static inline void dump_binary(uint8_t *_buffer, size_t _length)
{
    for (int i = 0; i < _length; ++i)
        dump_8bits(*_buffer++);
}

int main(int _argc, char **_argv)
{
    memset(&input[0], 0xFF, sizeof(input));

    for (int bit = 1; bit < 6000; bit++) {
        struct timespec t_start, t_end;

        memset(&output[0], 0x00, sizeof(output));
        clock_gettime(CLOCK_MONOTONIC, &t_start);
        bitcpy(&output[0], 5, &input[0], 3, bit); /* original method */
        clock_gettime(CLOCK_MONOTONIC, &t_end);
        long long t1 = (long long)(t_end.tv_sec * 1e9 + t_end.tv_nsec)
                        - (long long)(t_start.tv_sec * 1e9 + t_start.tv_nsec);

        memset(&output[0], 0x00, sizeof(output));
        clock_gettime(CLOCK_MONOTONIC, &t_start);
        bitcpy_rewrite(&output[0], 5, &input[0], 3, bit); /* mymethod */
        clock_gettime(CLOCK_MONOTONIC, &t_end);
        long long t2 = (long long)(t_end.tv_sec * 1e9 + t_end.tv_nsec)
                        - (long long)(t_start.tv_sec * 1e9 + t_start.tv_nsec);

        printf("%d %lld %lld\n", bit, t1, t2);
    }
/*
    for (int i = 1; i <= 32; ++i) {
        for (int j = 0; j < 16; ++j) {
            for (int k = 0; k < 16; ++k) {
                memset(&output[0], 0x00, sizeof(output));
                printf("%2d:%2d:%2d ", i, k, j);
                bitcpy(&output[0], k, &input[0], j, i);
                dump_binary(&output[0], 8);
                printf("\n");
            }
        }
    }
*/
    return 0;
}