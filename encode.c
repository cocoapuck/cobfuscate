#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define KEY_SIZE 5

static const unsigned char key[KEY_SIZE] = {
    0xA3, 0x7F, 0x2C, 0x91, 0xD6
};

void encode(unsigned char *data, size_t length)
{
    for (size_t i = 0; i < length; i++) {
        unsigned char k = key[i % KEY_SIZE];
        unsigned int r = (i % 7) + 1;

        data[i] ^= k;

        /* Rotate left (ROL) */
        data[i] = (unsigned char)(
            (data[i] << r) |
            (data[i] >> (8 - r))
        );
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <string_to_encode>\n", argv[0]);
        return 1;
    }

    size_t len = strlen(argv[1]);

    unsigned char *buffer = malloc(len);
    if (!buffer) {
        perror("malloc");
        return 1;
    }

    memcpy(buffer, argv[1], len);

    encode(buffer, len);

    printf("Encoded bytes:\n");
    for (size_t i = 0; i < len; i++) {
        printf("0x%02X", buffer[i]);
        if (i + 1 < len)
            printf(", ");
    }
    printf("\n");

    free(buffer);
    return 0;
}
