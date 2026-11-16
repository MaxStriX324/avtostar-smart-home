# Hardware (planning only)

No validated KiCad schematics/PCBs are provided yet.

- `esp12f-debug-module/`: **separate universal solder-on development/debug module** with an approved v1.0 specification; no verified KiCad design yet.
- `switch-2/`: ESP-12F, two externally sensed capacitive touch buttons. W or WR assembly.
- `relay-2/`: ESP-12F, two output drivers. W or WR assembly.
- `control/`: provisional ESP32-S3 gateway, wired RS-485 and wireless LAN.
- `common/`: power, MAX3485 and programming/EMC notes.

**One PCB layout per endpoint product, two population variants (W/WR).** MAX3485, its connector and protection are fitted on WR. ESP-NOW remains available on both variants.

The [universal debug module](esp12f-debug-module/README.md) always includes MAX3485 and is **not** a replacement for endpoint-specific W/WR assembly rules.
