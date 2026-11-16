# Security and trust boundaries — draft

1. All commissioning and pairing must require physical user authorization or an equivalent secure method; no unauthenticated default relay control.
2. ESP-NOW direct peer traffic requires cryptographic sender authentication, anti-replay logic and key provisioning; do not infer that all peer/broadcast modes provide equivalent encryption.
3. A **CRC on RS-485 detects transmission errors but does not authenticate messages**; choose physical trust assumptions and add application authorization where the installation requires it.
4. Web UI requires authentication, session management and authorization controls. Do not expose it directly to the public Internet.
5. Unique device IDs and pairing keys must be provisioned per device; keep production secrets out of Git.
6. OTA must be verified, recoverable and compatible with limited ESP8266 flash/RAM and boot architecture.
7. The automation RS-485 bus should remain separate from any safety-critical vehicle communication and power circuitry. Do not bridge untrusted traffic into vehicle systems.
8. Secure factory reset must clear pairing and network credentials without transiently energizing relay outputs.
