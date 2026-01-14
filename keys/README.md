Key generation (example)

Use OpenSSL to generate an RSA key pair for POC testing. In a real system, use an HSM or secure element.

Generate private key:

  openssl genpkey -algorithm RSA -out keys/private.pem -pkeyopt rsa_keygen_bits:2048

Extract public key:

  openssl rsa -in keys/private.pem -pubout -out keys/public.pem

Do NOT commit private keys to source control. Keep them in secure storage or HSM in production.
