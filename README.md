Secure Boot Chain & Trusted Logging for Automotive ECUs

This repository contains a multi-component skeleton demonstrating a hardware-rooted secure boot chain and tamper-evident logging for automotive ECUs. It is educational and designed to capture the architecture, build stubs, and proof-of-concept tools used during the research project.

Structure:
- docs/
  - architecture.md  (design and threat model)
- bootloader/        (C bootloader skeleton + verification API)
- uboot/             (integration notes for U-Boot)
- hsm/               (simple HSM simulator in Python)
- tee/               (TEE service stub / notes)
- logging/           (tamper-evident logging daemon)
- scripts/           (image-signing utilities)
- keys/              (instructions to generate keys)

Quick start (local POC):
1. Generate keys as described in `keys/README.md`.
2. Install Python deps: `pip install -r requirements.txt`.
3. Sign an example image: `python3 scripts/sign_image.py --key keys/private.pem --in example.bin --out example.bin.sig`.
4. Run HSM simulator: `python3 hsm/hsm_sim.py` (local POC to sign/verify).
5. Build the logging daemon: `make -C logging` and try `logging/logging_daemon ./logfile`.

Notes:
- This is a POC skeleton. Replace verification stubs with platform-specific secure verification (HW keys, HSM, secure boot ROM) when adapting to real hardware.
- Do not store production keys in this repo. Use HSM or secure elements for key storage.

Author: IIT Delhi - Prof. Kolin Paul
Project: Secure Boot Chain & Trusted Logging for Automotive ECUs
Timeline: Oct 2024 - Dec 2025
