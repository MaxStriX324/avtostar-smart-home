# Application protocol — RS-485/UART + ESP-NOW, draft v0.2

> **Not yet implemented on hardware.** The packet format below is a first deterministic test envelope, not a finalized secure network protocol.

## Fixed-length initial UART/RS-485 frame (16 bytes)

A small explicit frame avoids directly serializing an ABI-dependent C++ structure.

| Offset | Size | Field |
| --- | --- | --- |
| 0..1 | 2 | Start marker `A5 5A` |
| 2 | 1 | Version (1) |
| 3 | 1 | Opcode (SET=1, STATE=2, ACK=3, HEARTBEAT=4, ERROR=5) |
| 4..5 | 2 | Source node ID, little-endian |
| 6..7 | 2 | Destination node ID, little-endian |
| 8..9 | 2 | Sequence number, little-endian |
| 10 | 1 | Channel (0=system, 1/2=endpoints) |
| 11 | 1 | Flags, reserved/role-specific |
| 12..13 | 2 | Value, little-endian |
| 14..15 | 2 | CRC-16/Modbus (poly 0xA001, init 0xFFFF), little-endian, over bytes 0..13 |

Nodes 1..1023 are reserved for addressing; 0 may be used for **strictly limited** broadcast discovery. Validate frame length, version, opcode, address and CRC before routing it. A CRC detects accidental corruption; it does **not** authenticate commands.

ESP-NOW transport should encode the same logical fields but add a separately designed authenticated wireless envelope and replay protection. Do **not** assume this 16-byte UART frame is secure just because it has a CRC.

## Behaviors to implement

- Prefer **SET(ON/OFF)** commands (idempotent) to repeated toggle commands.
- Link-layer delivery, application ACK and authoritative STATE are distinct events.
- Deduplicate by (sender, boot/session ID, sequence) and handle sequence wrapping and restarts.
- Only allow commands from commissioned and authorized devices.
- If the gateway bridges channels, preserve logical message identity and prevent loops.
- Define relay behavior on offline, reconnect, undervoltage, watchdog and power-up.
- Do **not** transmit concurrently onto a shared RS-485 pair. A bus scheduler/ownership model is required.

## Initial bus access plan (unproven)

1. Two nodes, one initiator: switch sends request, relinquishes DE, relay replies after specified turn-around gap.
2. Multiple nodes: pick **one active coordinator** with grant/response windows; gateway takeover/election requires additional design and failure testing.
3. Without coordinator, direct ESP-NOW can still drive a commissioned switch-relay pair. Purely wired multi-master autonomy remains a future requirement, not a verified feature.

Protocol test code: `firmware/include/protocol.hpp` and `firmware/test/test_protocol.cpp`.
