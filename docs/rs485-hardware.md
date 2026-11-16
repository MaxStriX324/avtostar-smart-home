# MAX3485 + ESP-12F hardware design notes

> These are design constraints, **not** a production-ready schematic.

## MAX3485 interface (3.3 V half-duplex)

| MAX3485 signal | MCU/interface | Meaning |
| --- | --- | --- |
| VCC | regulated 3.3 V | Power, local bypass required |
| GND | common signal reference | Evaluate isolation where grounds differ |
| DI | ESP8266 UART0 TX (GPIO1) | Transmitter data |
| RO | ESP8266 UART0 RX (GPIO3) | Receiver data |
| DE | proposed ESP GPIO14 | Active-high transmitter enable |
| /RE | tied to DE in simple half-duplex direction circuit | Receive enabled when DE=0; review hardware behavior |
| A / B | RS-485 bus pair | Differential pair, labels/polarity must be verified at connector level |

**Default driver state:** 10 kΩ (provisional) pull-down on DE so the transmitter is disabled during reset, flashing and ROM boot serial output; confirm thresholds over all supply/brownout cases. When DE and /RE are tied: DE=0 → receive enabled/transmit off, DE=1 → transmit enabled/receive off. Change direction only after the last UART stop bit has physically left the transmitter; software "buffer empty" alone may not always equal shift-register empty.

**UART programming conflict:** ESP8266 ROM bootloader uses GPIO1/GPIO3. A populated MAX3485 receiver can actively drive RO onto GPIO3 while a USB-UART adapter also drives the programming RX input. Design positive separation: programming jumper, receiver-enable control plus isolation, or a verified switching circuit; do not just wire two push-pull outputs together. UART0 debug prints are also incompatible with unrestricted RS-485 transmission.

## Tentative GPIO plan (verify against exact module and PCB)

| GPIO | Switch 2 | Relay 2 | Notes |
| --- | --- | --- | --- |
| GPIO1 | MAX3485 DI (WR only) | MAX3485 DI (WR only) | UART0 TX / programming |
| GPIO3 | MAX3485 RO (WR only) | MAX3485 RO (WR only) | UART0 RX / programming; needs isolation |
| GPIO14 | MAX3485 DE + /RE control | MAX3485 DE + /RE control | External pull-down, default off |
| GPIO4 | Touch 1 digital output | Relay driver 1 | Relay boot state must be hardwired safe |
| GPIO5 | Touch 2 digital output | Relay driver 2 | Relay boot state must be hardwired safe |
| GPIO12 | LED feedback 1 | Optional diagnostics | Confirm no unsafe load |
| GPIO13 | LED feedback 2 | Optional diagnostics | Confirm no unsafe load |
| GPIO0/GPIO2/GPIO15 | Boot-strapping, reserve | Boot-strapping, reserve | Do not disturb required reset logic |

GPIO16 may be available subject to sleep/wake/board needs. This is **only a proposed pin map**, not a hardware design. Touch sensing uses external ICs; ESP8266 has no dedicated native touch inputs.

## RS-485 cable and topology

- Prefer a linear bus (daisy-chain) with short stubs; no uncontrolled star fan-out.
- Differential pair plus a defined signal reference; choose isolated transceiver/supply for relevant building wiring or ground-potential differences.
- Fit **120 Ω end termination only at the two physical ends**, when it matches the chosen cable impedance. Intermediate nodes should have termination disabled.
- Calculate **idle biasing** at system level; MAX3485 open-input fail-safe is not a replacement for a verified terminated-bus idle network.
- Fit suitable bus TVS / ESD components, account for common-mode and supply protection.
- MAX3485 datasheet permits up to 10 Mbit/s under appropriate conditions; **do not use that figure as a guaranteed installed-bus data rate**. Prototype at 115200 baud and evaluate cable length, EMI and signal margins.

## Software scheduling / bus ownership

MAX3485 provides only the electrical layer. For the first two-node test, one switch can act as the **only initiator**, while the relay responds in a bounded window. For multiple switches, relays and a gateway, **one active scheduler / token control / bus ownership mechanism** must be designed before allowing independent transmission. An ordinary Modbus RTU controller/slave model is a possible wired alternative but does not by itself provide arbitrary peer-to-peer masters.

## References

- MAX3485 official product/datasheet: https://www.analog.com/en/products/max3485.html
- Espressif ESP8266EX datasheet: https://documentation.espressif.com/0a-esp8266ex_datasheet_en.html
- ESP8266 hardware design guidelines: https://documentation.espressif.com/esp8266_hardware_design_guidelines_en.html
