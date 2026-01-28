#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define KEY_SIZE 5

static const unsigned char key[KEY_SIZE] = {
    0xA3, 0x7F, 0x2C, 0x91, 0xD6
};

void decode(const unsigned char *in, unsigned char *out, size_t length)
{
    for (size_t i = 0; i < length; i++) {
        unsigned char k = key[i % KEY_SIZE];
        unsigned int r = (i % 7) + 1;

        unsigned char v = in[i];

        v = (unsigned char)(
            (v >> r) |
            (v << (8 - r))
        );

        out[i] = v ^ k;
    }

    out[length] = '\0';
}


int main(void)
{
    static unsigned char v1[] = {0xDF, 0x40, 0x6A, 0x5F, 0x53, 0xB2, 0x8E, 0xBC, 0xC3, 0x25, 0xAD, 0xC7};
    static unsigned char v2[] = {0xD1, 0x68, 0xF2, 0xFF, 0x76, 0xF3, 0x26, 0x3C, 0xFE, 0x95, 0xFC, 0x62};
    static unsigned char v3[] = {0xC1, 0x34, 0x4A, 0x0F, 0x54, 0xB1, 0x97, 0xBC, 0xFB, 0xAD, 0x6C, 0x81, 0xD7, 0x68};
    static unsigned char v4[] = {0xE7, 0x34, 0x2A, 0x7E, 0xF7, 0xF3, 0x0D, 0x96, 0xD3, 0xAC, 0xBC, 0x43, 0xD3, 0x7D};
    static unsigned char v5[] = {0xC9, 0x68, 0xC2, 0x5C, 0x37, 0x32, 0x0D, 0x84, 0x63, 0xC5, 0x5C, 0x02, 0x97, 0x7E, 0x6F, 0x5F, 0xB0, 0x34, 0xFF};

    unsigned char *d1 = malloc(sizeof(v1) + 1);
    unsigned char *d2 = malloc(sizeof(v2) + 1);
    unsigned char *d3 = malloc(sizeof(v3) + 1);
    unsigned char *d4 = malloc(sizeof(v4) + 1);
    unsigned char *d5 = malloc(sizeof(v5) + 1);

    decode(v1, d1, sizeof(v1));
    decode(v2, d2, sizeof(v2));
    decode(v3, d3, sizeof(v3));
    decode(v4, d4, sizeof(v4));
    decode(v5, d5, sizeof(v5));

    printf("%s\n", d1);
    printf("%s\n", d2);
    printf("%s\n", d3);
    printf("%s\n", d4);
    printf("%s\n", d5);
    
    free(d1);
    free(d2);
    free(d3);
    free(d4);
    free(d5);


    return 0;
}