# Relay 2 — ESP-12F, two-channel output (no schematic yet)

- ESP-12F / ESP8266, two independently controlled outputs.
- W: Wi-Fi + ESP-NOW; wired RS-485 parts not populated.
- WR: **same PCB** with MAX3485 UART0 half-duplex transceiver and connector/protection fitted.
- Pin map **provisional**: GPIO4/5 drive output-driver input stages; GPIO14 DE, GPIO1/3 UART0 on WR.
- Each output must have a **hardware safe-off reset state**, irrespective of ESP firmware and GPIO boot behavior.
- 12/24 V DC camper loads and 230 V AC building loads require distinct power/output safety evaluations and possibly separate PCBs or power stages; do not assume interchangeable relays.
- Verify relay contact ratings for high-current DC/inductive loads, snubbers, fusing and isolation.

See [MAX3485 interface notes](../../docs/rs485-hardware.md).
