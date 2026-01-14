Secure Boot & Trusted Logging — Architecture

Overview
--------
The design enforces authenticated boot at every stage and tamper-evident runtime logging. The chain of trust follows:
- Boot ROM / Hardware Root -> First-stage bootloader -> U-Boot -> Secure Monitor / Secure OS -> Linux Kernel / User space

Design Goals
------------
- Enforce cryptographic signature verification at every hand-off.
- Store keys in hardware-backed HSM or secure element when available.
- Provide a minimal TEE to isolate critical services.
- Provide tamper-evident logging for runtime integrity checks.

Components
----------
1. Bootloader (first-stage)
   - Minimal runtime in C.
   - Verifies next-stage image signature using public key from hardware root or HSM.
2. U-Boot integration
   - U-Boot verifies kernel and device tree before boot.
   - Chain-of-trust hooks and environment variables described.
3. HSM simulator
   - Demonstrates how keys can be stored and used remotely for signing/verification.
4. TEE service
   - Stub to demonstrate isolating crypto ops and key usage.
5. Tamper-evident logging
   - Log entries chained using SHA-256; on-disk verification tool provided.

Threat model (brief)
--------------------
- Adversary may have physical access to device storage but not to hardware root or HSM.
- Attacker may attempt to replace boot images, modify logs, or interchange firmware components.
- This design assumes a hardware root-of-trust (fuse/HW-provisioned key) or equivalent secure keystore.

Performance and validation
--------------------------
- Target: authenticated boot with minimal runtime overhead (<5% overhead in measured boot flows on Raspberry Pi, per project results).
- Validation: measurement harness and logs to verify boot times and cryptographic costs.

Next steps
----------
- Port the verification API to use platform crypto (ARM CryptoCell / Infineon AURIX HSM APIs).
- Integrate with OP-TEE for TEE-based key usage.
- Add continuous attestation to remote server using tamper-evident logs.
