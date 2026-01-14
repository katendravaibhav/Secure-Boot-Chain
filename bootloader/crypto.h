#ifndef CRYPTO_H
#define CRYPTO_H

/* Minimal abstract interface used by the bootloader to verify an image */

/* Returns 1 on success (signature valid), 0 on failure */
int verify_image(const char *image_path, const char *sig_path);

#endif /* CRYPTO_H */
