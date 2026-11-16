# Engineering backlog / immediate work

1. **ESP-12F GPIO map** per board with reset/boot/flash constraints and two output/input pins.
2. **MAX3485 design:** DI/RO/DE//RE, boot-safe DE pull-down, flash/programming isolation and direction timing.
3. **RS-485 bus:** A/B reference/polarity pinout, termination, idle bias, TVS, ground/isolation and cable requirements.
4. **Power design:** board supply, 3.3 V rail and protections for house vs camper installations.
5. **KiCad:** Switch 2 and Relay 2 distinct layouts, W/WR BOM population options per board.
6. ESP-NOW pairing and transport-independent application protocol.
7. Reliable state machine: ACK/STATE, duplicate suppression, retry, fault behavior and security.
8. RS-485 ownership/scheduler for >2 nodes; **not arbitrary concurrent multi-master UART**.
9. ESP32-S3 gateway and local web/PWA control.
10. OTA, production test and regulatory/safety gates.

None of these implementation items should be marked complete without measured, versioned validation evidence.
