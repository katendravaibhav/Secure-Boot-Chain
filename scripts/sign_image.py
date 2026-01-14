#!/usr/bin/env python3
"""
Simple image signing script that wraps the HSM simulator or uses a local private key.
Usage:
  python3 scripts/sign_image.py --key keys/private.pem --in image.bin --out image.bin.sig
"""
import argparse
from cryptography.hazmat.primitives import hashes, serialization
from cryptography.hazmat.primitives.asymmetric import padding


def sign_image(keyfile, infile, outfile):
    with open(keyfile, 'rb') as f:
        priv = serialization.load_pem_private_key(f.read(), password=None)
    with open(infile, 'rb') as f:
        data = f.read()
    sig = priv.sign(data, padding.PKCS1v15(), hashes.SHA256())
    with open(outfile, 'wb') as f:
        f.write(sig)
    print(f"Signed {infile} -> {outfile}")

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--key', required=True)
    parser.add_argument('--in', dest='infile', required=True)
    parser.add_argument('--out', required=True)
    args = parser.parse_args()
    sign_image(args.key, args.infile, args.out)
