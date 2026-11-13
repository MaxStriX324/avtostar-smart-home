# Transport-independent protocol — draft v0.1

> Preliminary protocol for review. Not finalized, authenticated, or deployed.

## Addressing

- Node ID: 1...1023; `0` reserved for broadcast where safe.
- Stable globally unique device ID stored separately (e.g. 64-bit, not directly encoded in CAN ID).
- CAN uses extended 29-bit frames; no dependency on CAN FD.
- Proposed numeric CAN ID packing: `[priority:3][type:6][source:10][destination:10]` (most-significant bit first).
- On-wire priority: lower numerical value is higher CAN arbitration priority.

## Classic CAN 8-byte payload draft

| Byte(s) | Field | Meaning |
| --- | --- | --- |
| 0 | version | protocol version, currently 1 |
| 1 | opcode | SET=1, STATE=2, ACK=3, HEARTBEAT=4, ERROR=5 |
| 2 | channel | 0=system, 1=relay/key A, 2=relay/key B |
| 3 | flags | state, response and future options (must define exact bits) |
| 4–5 | sequence | uint16 little-endian deduplication token |
| 6–7 | value | uint16 little-endian command/status value |

The CAN ID includes source, destination, message type and priority. Payload is encoded explicitly, **never via raw C struct memory layout**. Wireless envelopes must carry comparable source/destination metadata, integrity, authenticated pairing and sequence context.

## Behavioral rules

- Prefer **idempotent SET(ON/OFF)** over retransmitting TOGGLE commands; retries must not cause additional switching.
- Confirm commands by an ACK and state report, not only successful radio send API return.
- Track recently accepted sequence values scoped to sender/device/session; define reboot/resync behavior.
- Commands with stale identifiers, unauthorized senders or invalid versions must be ignored.
- Transport bridging requires hop limit, origin marker, replay suppression and routing policy.
- State remains authoritative at the Relay endpoint, not in a switch UI or gateway cache.
- Automatic failover between CAN and ESP-NOW may resend **the same logical message ID**, not a new command.

## Next design steps

Formalize security envelope (ESP-NOW peers + payload authentication), persistent device identity, pairing, node address assignment, discovery, state subscription and compatibility/upgrade scheme. Add fuzz/negative/timeout tests prior to energizing outputs.
