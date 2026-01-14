U-Boot Integration Notes

This file contains guidance for integrating image verification into U-Boot.

1. U-Boot supports verified boot via `bootm`/`bootz` wrappers and verified image formats.
2. Strategy:
   - Keep a small trusted U-Boot (stage1) that verifies and loads the main U-Boot.
   - Use signed FIT images for kernel+dtb+ramdisk and verify using U-Boot's crypto commands.
3. Example environment variables:
   - `verifycmd` : calls a custom verification binary to check signatures before boot.
4. For production automotive systems use secure storage for public keys and optionally integrate HSM to perform signature operations.

See `docs/architecture.md` for higher-level design.
