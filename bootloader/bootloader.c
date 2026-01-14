/*
 * Minimal bootloader skeleton demonstrating image loading and signature verification.
 * In a real design, this runs from on-chip RAM/ROM and uses hardware crypto.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypto.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "usage: %s <image.bin> <image.sig>\n", argv[0]);
        return 1;
    }

    const char *image = argv[1];
    const char *sig = argv[2];

    printf("Bootloader: loading image '%s' and signature '%s'\n", image, sig);

    int ok = verify_image(image, sig);
    if (!ok) {
        fprintf(stderr, "Signature verification failed! Halting.\n");
        return 2;
    }

    printf("Signature OK — jumping to next stage (simulated)\n");
    /* In real bootloader, we'd set up CPU state and jump to image entry point */

    return 0;
}
