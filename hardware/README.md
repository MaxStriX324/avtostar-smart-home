# Hardware (planning only)

No validated KiCad schematics/PCBs are provided yet.

- `switch-2/`: ESP-12F, two externally sensed capacitive touch buttons. W or WR assembly.
- `relay-2/`: ESP-12F, two output drivers. W or WR assembly.
- `control/`: provisional ESP32-S3 gateway, wired RS-485 and wireless LAN.
- `common/`: power, MAX3485 and programming/EMC notes.

**One PCB layout per endpoint product, two population variants (W/WR).** MAX3485, its connector and protection are fitted on WR. ESP-NOW remains available on both variants.
