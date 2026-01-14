/*
 * Tamper-evident logging daemon (POC)
 * Each log entry is appended with a SHA-256 of (prev_hash || entry).
 * A verify tool can scan the log and detect tampering.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <openssl/evp.h>

static void sha256(const uint8_t *in, size_t inlen, uint8_t out[32]) {
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    unsigned int outlen = 32;
    EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(mdctx, in, inlen);
    EVP_DigestFinal_ex(mdctx, out, &outlen);
    EVP_MD_CTX_free(mdctx);
}

void print_hex(const uint8_t *b, size_t n) {
    for (size_t i=0;i<n;i++) printf("%02x", b[i]);
}

int append_log(const char *path, const char *entry) {
    FILE *f = fopen(path, "ab");
    if (!f) return -1;
    uint8_t prev[32] = {0};
    /* read last hash if file exists */
    FILE *rf = fopen(path, "rb");
    if (rf) {
        fseek(rf, 0, SEEK_END);
        long sz = ftell(rf);
        if (sz >= 32) {
            fseek(rf, sz - 32, SEEK_SET);
            fread(prev, 1, 32, rf);
        }
        fclose(rf);
    }

    size_t elen = strlen(entry);
    uint8_t *buf = malloc(32 + elen);
    memcpy(buf, prev, 32);
    memcpy(buf+32, entry, elen);
    uint8_t newhash[32];
    sha256(buf, 32 + elen, newhash);
    free(buf);

    /* write entry length, entry, then hash */
    uint32_t elen32 = (uint32_t)elen;
    fwrite(&elen32, sizeof(elen32), 1, f);
    fwrite(entry, 1, elen, f);
    fwrite(newhash, 1, 32, f);
    fflush(f);
    fclose(f);
    return 0;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "usage: %s <logfile> <message>\n", argv[0]);
        return 1;
    }
    append_log(argv[1], argv[2]);
    printf("Appended message to %s\n", argv[1]);
    return 0;
}
