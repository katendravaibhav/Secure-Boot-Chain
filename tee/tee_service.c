/*
 * Minimal TEE service stub. In a real deployment this would be an OP-TEE TA
 * or other TEE-resident service that performs sensitive crypto with sealed keys.
 *
 * This C file is only a placeholder showing the intended interface.
 */

#include <stdio.h>

int tee_sign(const char *data_path, const char *out_sig) {
    /* In a real TEE, open sealed key and perform signature. Here we print a message. */
    printf("[TEE] Would sign %s and write to %s (stub)\n", data_path, out_sig);
    return 0;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "usage: %s <data> <out_sig>\n", argv[0]);
        return 1;
    }
    return tee_sign(argv[1], argv[2]);
}
