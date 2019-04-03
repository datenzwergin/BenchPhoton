#include "ref/photon.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 16 * 1024 * 1024
#define IN_SIZES                                                               \
    { 12, 64, 128, 256, 1024, 16 * 1024, 1024 * 1024, 16 * 1024 * 1024, 44 }

void hash(byte *out, const byte *in, int inlen);
clock_t clock(void);
void *malloc(size_t size);
#ifdef _TABLE_
void BuildTableSCShRMCS();
#endif

int run_hash(byte *out, const byte *in, int inlen) {
    clock_t clk_pre, clk_post;

    // do the bench
    clk_pre = clock();
    hash(out, in, 8 * inlen);
    clk_post = clock();
    return (int)clk_post - (int)clk_pre;
}

int main() {
    static uint8_t in[MAX_SIZE] = {0};
    uint8_t out[DIGESTSIZE / 8] = {0};
    unsigned int i, j;
    const int sizes[] = IN_SIZES;

#ifdef _TABLE_
    // Building this table beforehand, greatly improves speed_
    BuildTableSCShRMCS();
#endif

    // read random data from 'random.data' into `in`.
    FILE *rnd_src = fopen("random.data", "rb");
    if (rnd_src == NULL) {
        perror("random.data");
        exit(1);
    }
    size_t num_read = fread(in, 1, MAX_SIZE, rnd_src);
    if (num_read < MAX_SIZE) { /* error */
    }
    fclose(rnd_src);

    printf("CLOCKS_PER_SEC: %li\n", CLOCKS_PER_SEC);
    for (i = 0; i < sizeof(sizes) / sizeof(*sizes); i++) {

        printf("INPUT SIZE    : %i\nCLOCKS: ", sizes[i]);
        for (j = 0; j < 10; j++) {
            int clocks = run_hash(out, (byte *)in, sizes[i]);
            printf(" %i", clocks);
        }
        printf("\n");
    }

    // The last hash is displayed, just to verify
    printDigest(out); // should be: 07d1723459751e368532
    return 0;
}
