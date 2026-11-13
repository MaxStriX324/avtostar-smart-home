# Security and trust boundaries — draft

1. Local operation must not mean unauthenticated control: each device must use authenticated commissioning and revoke/reset procedures.
2. ESP-NOW pairing: configure peers and encryption where supported, review multicast limitations, and implement application-level sender authorization and replay resistance.
3. Web UI: authenticated administration, least-privilege roles, CSRF/session defense where relevant, no default passwords.
4. Remote access: do not expose the ESP device admin HTTP port directly to the internet; prefer authenticated VPN / trusted reverse access solutions.
5. OTA: signed firmware verification, approved version tracking, rollback on failed boot where supported, controlled update window.
6. Physical CAN is not authenticated simply because it is wired: define physical trust assumptions and gateway validation. Avoid forwarding vehicle safety-critical CAN traffic into automation bus.
7. Secure storage and device unique IDs: provision secrets per-device; never commit private production keys.
8. Factory reset must clear all pairings and credentials and should not unexpectedly energize relays.
