# MAX3485 + ESP-12F hardware design notes

> These are design constraints, **not** a production-ready schematic.

## MAX3485 interface (3.3 V half-duplex)

| MAX3485 signal | MCU/interface | Meaning |
| --- | --- | --- |
| VCC | regulated 3.3 V | Power, local bypass required |
| GND | common signal reference | Evaluate isolation where grounds differ |
| DI | ESP8266 UART0 TX (GPIO1) | Transmitter data |
| RO | ESP8266 UART0 RX (GPIO3), through 100 Ω and removable J1.4–J1.5 shunt on debug module | Receiver data; shunt removed for flashing |
| DE | **ESP GPIO16 on accepted universal debug module** | Active-high transmitter enable |
| /RE | tied to DE in simple half-duplex direction circuit | Receive enabled when DE=0; review hardware behavior |
| A / B | RS-485 bus pair | Differential pair, labels/polarity must be verified at connector level |

**Default driver state:** 10 kΩ (provisional) pull-down on DE so the transmitter is disabled during reset, flashing and ROM boot serial output; confirm thresholds over all supply/brownout cases. When DE and /RE are tied: DE=0 → receive enabled/transmit off, DE=1 → transmit enabled/receive off. Change direction only after the last UART stop bit has physically left the transmitter; software "buffer empty" alone may not always equal shift-register empty.

**UART programming conflict:** ESP8266 ROM bootloader uses GPIO1/GPIO3. A populated MAX3485 receiver can actively drive RO onto GPIO3 while a USB-UART adapter also drives the programming RX input. Design positive separation: programming jumper, receiver-enable control plus isolation, or a verified switching circuit; do not just wire two push-pull outputs together. UART0 debug prints are also incompatible with unrestricted RS-485 transmission.

## Debug-module GPIO map (v1.0)

**Reference:** [Universal ESP-12F debug module v1.0](../hardware/esp12f-debug-module/README.md).

| ESP GPIO | Fixed debug-module function |
| --- | --- |
| GPIO1 TX0 | MAX3485 DI via 100 Ω and service UART TX |
| GPIO3 RX0 | Service UART RX, or MAX3485 RO via removable J1.4–J1.5 jumper |
| GPIO16 | MAX3485 DE + /RE direction; 10 kΩ pull-down |
| GPIO4, GPIO5, GPIO12, GPIO13, GPIO14 | Five general-purpose motherboard signals, no fixed LEDs or loads |
| GPIO0/2/15 | Boot straps only; FLASH button to GPIO0 |
| ADC | Direct 0–1 V to carrier; scaling/protection external |

This accepted map applies to the **new debug daughterboard**. Legacy endpoint pin suggestions that used **GPIO14 for DE** are superseded *for this module*. Dedicated Switch 2 / Relay 2 W/WR product PCB pin maps remain provisional until designed and tested. With GPIO16 consumed by DIR, RTC Deep Sleep timed wake via GPIO16→RST is unavailable.

The debug module has an SM712 TVS and 10 Ω series resistors on A/B, plus 100 Ω series resistors on DI and RO. J1.1 is the +3.3 V rail.

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
