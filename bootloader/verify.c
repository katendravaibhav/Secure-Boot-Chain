#include "crypto.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Very small verification stub used for local POC. Real implementation should use
 * a verified crypto library and hardware key storage (HSM/secure element) or
 * platform-specific secure boot infrastructure.
 */

int verify_image(const char *image_path, const char *sig_path) {
    /* Proof-of-concept: accept if signature file exists and non-empty. */
    FILE *f = fopen(sig_path, "rb");
    if (!f) {
        return 0;
    }
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fclose(f);
    return sz > 0;
}
