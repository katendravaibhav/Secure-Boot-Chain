#!/usr/bin/env python3
"""
Simple HSM simulator: provides sign and verify commands using a local private key.
This is a POC for testing flows when a real HSM isn't available.

Dependencies: cryptography

Usage:
  python3 hsm/hsm_sim.py sign --key keys/private.pem --in image.bin --out image.bin.sig
  python3 hsm/hsm_sim.py verify --pub keys/public.pem --in image.bin --sig image.bin.sig

Do NOT use this in production. Use a hardware-backed HSM for private key operations.
"""

import argparse
import sys
from cryptography.hazmat.primitives import hashes, serialization
from cryptography.hazmat.primitives.asymmetric import padding
from cryptography.hazmat.primitives import serialization


def sign(key_pem, infile, outfile):
    with open(key_pem, 'rb') as f:
        priv = serialization.load_pem_private_key(f.read(), password=None)
    with open(infile, 'rb') as f:
        data = f.read()
    sig = priv.sign(data, padding.PKCS1v15(), hashes.SHA256())
    with open(outfile, 'wb') as f:
        f.write(sig)
    print(f"Signed {infile} -> {outfile}")


def verify(pub_pem, infile, sigfile):
    with open(pub_pem, 'rb') as f:
        pub = serialization.load_pem_public_key(f.read())
    with open(infile, 'rb') as f:
        data = f.read()
    with open(sigfile, 'rb') as f:
        sig = f.read()
    try:
        pub.verify(sig, data, padding.PKCS1v15(), hashes.SHA256())
        print("Signature valid")
        return 0
    except Exception as e:
        print("Signature verification failed:", e)
        return 2


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    sub = parser.add_subparsers(dest='cmd')
    p1 = sub.add_parser('sign')
    p1.add_argument('--key', required=True)
    p1.add_argument('--in', dest='infile', required=True)
    p1.add_argument('--out', required=True)
    p2 = sub.add_parser('verify')
    p2.add_argument('--pub', required=True)
    p2.add_argument('--in', dest='infile', required=True)
    p2.add_argument('--sig', required=True)

    args = parser.parse_args()
    if args.cmd == 'sign':
        sign(args.key, args.infile, args.out)
    elif args.cmd == 'verify':
        sys.exit(verify(args.pub, args.infile, args.sig))
    else:
        parser.print_help()
