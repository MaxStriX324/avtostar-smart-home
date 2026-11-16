# Requirements — revision 0.2 / ESP-12F + MAX3485

## Devices

- **Switch 2**: two capacitive keys through external touch-sensing ICs (e.g. TTP223, selection not final), with optional status indication.
- **Relay 2**: two outputs, explicit power-on, reset, offline and fault behavior; avoid unsafe GPIO boot transients.
- MCU for both endpoints: **ESP-12F / ESP8266** at regulated **3.3 V**.
- Each endpoint design has **one PCB revision** and two component population options: W (wireless), WR (wireless + RS-485).
- WR adds a **MAX3485 (3.3 V, half-duplex RS-485)**; does not remove Wi-Fi / ESP-NOW.
- Switch ↔ Relay direct **ESP-NOW** operation without a central controller or internet.
- Store pairing, identity and channel mappings in nonvolatile memory.
- Offer commissioning, authorized re-binding and factory reset.
- Never execute stale or repeated switching commands unexpectedly.

## Wired requirements

- Use ESP8266 UART0 with dedicated, safe MAX3485 direction control.
- Keep MAX3485 DE low at startup; /RE and DE may share a direction signal subject to final circuit review.
- Ensure RS-485 RO cannot electrically interfere with UART flashing/diagnostics.
- Provide bus ESD/transient protection, reference ground strategy, **termination only at physical bus ends**, and calculated idle bias.
- Define serial frame, CRC, addressing, node lifetime and ACK/timeout behavior.
- Require bus arbitration/access policy. RS-485 is not CAN; no inherent collision avoidance.
- Initial UART bit rate target for prototypes: **115200 baud**, subject to line length, EMI and test results.

## Gateway

- ESP32-S3 provisional, local Web UI/PWA, device inventory, state and logs.
- RS-485 bridge and optional Wi-Fi IP integration; endpoint safety does not depend on gateway availability.
- Remote access is opt-in and authenticated; no default public port exposure.

## Open items before PCB

1. Switch input voltage/power source and mounting constraints.
2. Relay electrical rating, load type, vehicle LV vs mains AC product splits.
3. Pin allocation and safe boot/programming interface.
4. RS-485 connector choice, cable, GND reference, isolation and bias/termination.
5. Maximum bus node count and whether a single coordinator is acceptable.
6. Security model for direct radio and wired commands.
