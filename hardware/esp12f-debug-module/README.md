# AVTOSTAR ESP-12F Universal Debug Module — hardware baseline v1.0

**Status:** design decisions accepted on **2026-11-16**; schematic, PCB and performance are **not built or electrically verified**.
**Brand:** AVTOSTAR — Powered by MaxStriX324.
**Purpose:** small solder-on *development/debug daughterboard* for prototyping ESP-12F applications, wired RS-485 and Wi-Fi/ESP-NOW, suitable for installation on a separately designed carrier/motherboard.

> This is a **separate reference/debug board**. It does **not** replace the dedicated Switch 2, Relay 2 or Control designs, and it does not silently change their W (wireless) / WR (wireless + RS-485) assembly options. The debug module always has the MAX3485 populated. A product-specific carrier remains responsible for inputs, outputs, isolation, protection, connectors and safety.

## 1. Accepted scope and exclusions

- **Exactly three main ICs:** ESP-12F / ESP8266, MAX3485 (3.3 V RS-485 transceiver), **AMS1117-3.3 UMW in SOT-223**.
- **Input:** regulated +5 V and common GND. Onboard 3.3 V rail.
- **Five application digital pins only:** GPIO4, GPIO5, GPIO12, GPIO13, GPIO14; **no LEDs, permanent pulls or fixed RC filters** on these lines.
- **One ADC/TOUT** exposed without divider. The ESP8266 input range at the module pin is **0–1.0 V**; design scaling/RC/protection on the carrier board.
- GPIO0, GPIO2 and GPIO15 are reserved for reliable bootstrapping and **never exposed as general I/O**; GPIO0 is accessible through the local BOOT button only.
- GPIO16 is dedicated to RS-485 direction (DE and /RE tied together). No GPIO16-to-RST deep-sleep wake wire on v1.0.
- UART0 (GPIO1 TX0 / GPIO3 RX0) is shared between MAX3485 and ROM flashing. Disconnect **RO ↔ RX0** with a removable jumper for wired flashing.
- Two power LEDs only: 5V and 3V3; **no GPIO/RX/TX/DE activity LEDs**, logic buffer or additional ICs.
- On the module: BOOT and RESET tactile buttons, one angled 1x5 service header, 12 solder pads to the motherboard.
- RS-485 termination, failsafe bias, TVS, ground reference/isolation, external-signal dividers and driver circuitry belong on the *motherboard*; design them for each installation.

The choices above are **frozen for the first schematic**. Capacitor/ESR selection, startup behavior and mechanical dimensions are engineering verification items, not assumed validated facts.

## 2. Accessible GPIO and interfaces

| Module pad/signal | Normal use | Supported alternative uses |
| --- | --- | --- |
| GPIO4 | General 3.3 V digital I/O | Software I²C SDA, software UART, PWM, 1-Wire, interrupts |
| GPIO5 | General 3.3 V digital I/O | Software I²C SCL, software UART, PWM, 1-Wire, interrupts |
| GPIO12 | General 3.3 V digital I/O | HSPI MISO, PWM, 1-Wire, interrupts |
| GPIO13 | General 3.3 V digital I/O | HSPI MOSI, PWM, 1-Wire, interrupts |
| GPIO14 | General 3.3 V digital I/O | HSPI SCK, PWM, 1-Wire, interrupts |
| ADC/TOUT | Analog input, **0–1 V only** | External divider and input filtering are on motherboard |
| GPIO16 (internal) | MAX3485 DE + /RE | **Not** user-accessible; no RTC wake-to-RST |
| GPIO1/GPIO3 (service) | UART0 TX0/RX0 | RS-485 or flashing, **not independent interfaces** |

Reference combinations:

- **I²C + 3 I/O:** GPIO4 = SDA, GPIO5 = SCL; GPIO12/13/14 = independent lines. I²C external pull-ups (typically 4.7 kΩ to 3.3 V) belong on the motherboard; the actual value depends on bus capacitance and frequency.
- **HSPI + up to 1 extra I/O:** GPIO14 = SCK, GPIO13 = MOSI, GPIO12 = MISO, GPIO4 = CS, GPIO5 = I/O. Second SPI chip select could use GPIO5 instead.
- **5 generic I/O:** GPIO4/5/12/13/14, each configured in firmware.
- **1-Wire, PWM, software UART:** possible on suitable GPIO with firmware/latency limits; time-critical software protocols can suffer with Wi-Fi enabled.
- **RS-485:** MAX3485 UART0, half-duplex; e.g. Modbus RTU or AVTOSTAR transport, subject to firmware protocol.
- **Wi-Fi / ESP-NOW:** available in ESP-12F firmware; ESP-NOW is direct peer messaging, **not automatic multihop mesh**.

ESP-12F digital pins are **not 5 V tolerant**. A general-purpose pad is an MCU I/O, **not a protected 5/12/24 V terminal**. Add matching input resistors, transistor drivers, voltage adaptation and ESD protection on the carrier. GPIO6–GPIO11 are reserved for onboard Flash.

## 3. ESP-12F power-on straps, reset and boot

| ESP net | Approved baseline connection |
| --- | --- |
| EN / CH_PD | 10 kΩ pull-up to 3.3 V |
| RST | 10 kΩ pull-up to 3.3 V; momentary RESET button to GND |
| GPIO0 | 10 kΩ pull-up to 3.3 V; momentary BOOT button to GND |
| GPIO2 | 10 kΩ pull-up to 3.3 V; no external general-I/O connection |
| GPIO15 | 10 kΩ pull-down to GND; no external general-I/O connection |
| GPIO16 | Direction net DIR with 10 kΩ pull-down to GND |
| VCC | 3.3 V with local 10 µF and 100 nF bypass near ESP-12F |
| RST capacitor | 100 nF *DNP option*, fit only after checking reset/programming timing |

**Normal boot:** GPIO0 = HIGH, GPIO2 = HIGH, GPIO15 = LOW at sampling. **ROM UART download:** keep BOOT pressed (GPIO0 LOW), pulse RESET, release BOOT. The five universal GPIOs have no hardcoded boot straps, LEDs or pull networks on this module. Connected devices may still require firmware pin planning.

## 4. RS-485 — MAX3485

| MAX3485 pin | Signal | Debug-module connection |
| --- | --- | --- |
| 1 | RO | Service header J2.5; reaches ESP GPIO3/RX0 **only through J2.4–J2.5 jumper** |
| 2 | /RE | DIR from ESP GPIO16 |
| 3 | DE | Same DIR from ESP GPIO16 |
| 4 | DI | ESP GPIO1/TX0 (place optional 100 Ω footprint, default 0 Ω if not populated) |
| 5 | GND | Digital GND |
| 6 | A | Motherboard pad A |
| 7 | B | Motherboard pad B |
| 8 | VCC | 3.3 V; 100 nF bypass at package |

| DIR level | DE | /RE | Action |
| --- | --- | --- | --- |
| LOW | 0 | 0 | Transmitter disabled, receiver enabled |
| HIGH | 1 | 1 | Transmitter enabled, receiver disabled |

The **10 kΩ DIR pulldown** is a hardware fail-safe intention, **not proof** GPIO16 never glitches high during startup/brownout. Measure DIR, TX0 and A/B during power-up, RESET and ROM flashing before attaching to a live multidrop bus. Firmware must set DIR LOW early and wait until the **last stop bit is transmitted** before returning to receive.

Do not permanently terminate A/B with 120 Ω on this module. The **motherboard** selects end-of-line termination, biasing and TVS near the exposed bus connector. Validate cable impedance, ground reference and common-mode voltages; assess galvanic isolation separately for long building/vehicle runs.

**Important:** USB-UART TX and MAX3485 RO must never simultaneously drive RX0. Inserting the jumper while a programming adapter is connected and driving TX can cause electrical contention. Removing the jumper isolates RO, but MAX3485 *DI* stays connected to TX0; DE is held LOW during flashing.

## 5. Angled programming header, RO jumper and buttons

**J2: 1×5, 2.54 mm, right-angle male header.** The physical silk labels describe the **ESP side** of the connection:

| Pin | Label | Circuit |
| --- | --- | --- |
| J2.1 | 5V | Regulated +5 V supply for standalone flashing; don't backfeed an already powered carrier |
| J2.2 | GND | Common reference |
| J2.3 | TX0 | ESP GPIO1 TX → USB-UART **RX** |
| J2.4 | RX0 | ESP GPIO3 RX ← USB-UART **TX**; jumper side 1 |
| J2.5 | RO | MAX3485 receiver output; jumper side 2 |

**Default use:** removable jumper between J2.4–J2.5; no USB-UART transmitter attached. **Flashing:** remove J2.4–J2.5 jumper, then connect a **3.3 V logic-level** USB-UART adapter. On J2 there is **5 V for power, not 5 V UART logic**.

Manual programming sequence:
1. Disconnect normal external UART adapter or verify there are no two +5 V sources. Remove J2.4–J2.5 jumper.
2. Connect USB-UART GND→GND, adapter RX→TX0 (J2.3), adapter TX→RX0 (J2.4). Use J2.1 +5 V only when no other supply powers the module.
3. Hold **BOOT**; briefly press and release **RESET**; release BOOT.
4. Flash over UART0. Disconnect USB-UART, restore J2.4–J2.5 jumper, press RESET to run the firmware.

OTA does not need jumper removal, but firmware must not accidentally enable RS-485 during programming/boot logs.

## 6. Power supply, BOM and thermal limits

**Accepted production-of-prototype choice:** **AMS1117-3.3, UMW, SOT-223**. Alternative considered but **not selected**: AP2112K-3.3TRG1, SOT-23-5, 600 mA.

**Price snapshot from user's saved ChipDip HTML pages (not a live stock quote):**
- AMS1117-3.3 UMW SOT-223, listed as 1 A: **6.79 RUB** single-unit.
- AP2112K-3.3TRG1 Diodes, listed as 600 mA: **19.40 RUB** single-unit.

Baseline rail: regulated **5 V input → AMS1117-3.3 → 3.3 V** to ESP and MAX3485. Suggested input placement **10 µF + 100 nF**. At output reserve the *manufacturer-required* capacitor with **ESR compatible with the specific UMW part** (at least 10 µF as preliminary selection), and local ESP 10 µF + 100 nF, MAX3485 100 nF. Do not approve an all-ceramic-only layout without verifying this part's stability data. Match capacitors and layout to UMW datasheet before schematic signoff.

LDO heat at 5 V input is approximately **0.425 W at 250 mA**, **0.85 W at 500 mA**. Provide SOT-223 thermal copper and test temperature / rail dips during Wi-Fi TX peaks. External +3V3 pad is for *limited carrier loads*, within measured power/thermal budget.

Preliminary BOM (not released for purchasing):

| Ref group | Component / population |
| --- | --- |
| U1 | ESP-12F / ESP8266 module |
| U2 | MAX3485 transceiver, SOIC-8 |
| U3 | AMS1117-3.3 UMW, SOT-223 |
| R_STRAP | 10 kΩ × 6: EN, RST, GPIO0, GPIO2, GPIO15, DIR(GPIO16) |
| R_DI | TX0→DI optional 100 Ω footprint; choose fit value at schematic stage |
| R_IO | Five 0 Ω series link footprints on GPIO4/5/12/13/14 (optional diagnostic breaks) |
| C_PWR | UMW-approved CIN/COUT; local ESP 10 µF + 100 nF, MAX3485 100 nF |
| C_RST | 100 nF on RST, DNP pending reset validation |
| LED1/2 | 5V and 3V3 power indicators, each with its own ~4.7 kΩ resistor |
| SW1/2 | Momentary RESET-to-GND and BOOT(GPIO0)-to-GND switches |
| J2 | 1×5 right-angle 2.54 mm service header + removable shunt J2.4–J2.5 |
| TP | 3.3 V, GND and DIR test pads |
| J1 | 12 castellated or solderable module-to-motherboard pads (geometry TBD) |

No I/O status LEDs, no activity buffers, no extra logic devices, no ADC divider and no fixed I²C pull-ups on the daughterboard.

## 7. Motherboard solder-pad map — 12 contacts

| Pad | Signal | Pad | Signal |
| --- | --- | --- | --- |
| 1 | +5V IN | 7 | GPIO5 / I²C SCL |
| 2 | GND | 8 | GPIO12 / HSPI MISO |
| 3 | +3V3 OUT | 9 | GPIO13 / HSPI MOSI |
| 4 | RS485 A | 10 | GPIO14 / HSPI SCK |
| 5 | RS485 B | 11 | ADC / TOUT (0–1 V) |
| 6 | GPIO4 / I²C SDA | 12 | GND |

Mechanics: **two groups of six solder pads** on the module; exact order above is the net-number contract, while left/right placement, pitch, courtyard and overall size are to be finalized in KiCad. Place ESP-12F antenna at the module edge and keep copper, tracks and metal away from its RF keepout **on both daughterboard and motherboard**. Suggested 40×30 mm board envelope is only a placement starting point, not a manufacturing drawing.

## 8. GPIO16 compromise and firmware interoperability

GPIO16 is from the RTC GPIO domain; it is **not a boot-strap pin**, so choosing it for DIR preserves all five generic GPIOs. This is acceptable for the intended **continuously powered 5 V** development module.

**Lost capability:** automatic RTC timed wake from Deep Sleep normally needs GPIO16→RST. v1.0 expressly does not connect those nets and is **not the planned hardware for battery-powered periodic wake**. Deep Sleep entry without automatic wake may still be possible; the application must not assume an RTC wake path.

UART0 is reserved for RS-485 and ROM flashing. Unmodified firmware that uses Serial/UART0 for general logs or data may conflict with this topology. Boot ROM can emit UART0 traffic; correct DE=LOW must prevent bus transmission. Other firmware GPIO defaults can still cause conflicts with attached carrier circuits: reliable MCU boot is not the same as arbitrary firmware compatibility.

## 9. Validation required before release

- [ ] Check exact ESP-12F pin 1 / flash size / symbol footprint and program/boot behavior.
- [ ] Check exact **UMW** AMS1117-3.3 pinout, CIN/COUT, output capacitor ESR/stability and thermal limits from the vendor datasheet.
- [ ] Verify 5 V current capability, 3.3 V brownout and decoupling under Wi-Fi transmission peaks.
- [ ] Measure GPIO0/2/15 straps and reset timing with carrier I/O connected.
- [ ] Measure GPIO16/DIR during cold start, brownout, RESET and BOOT-to-ROM transitions; confirm A/B driver always off until firmware controls it.
- [ ] Flash through J2 with RO jumper removed; restore jumper and confirm RS-485 reception.
- [ ] Validate RS-485 direction switching after full stop bit, CRC and 115200-baud initial tests under expected cable conditions.
- [ ] Verify I²C on 4/5 and HSPI on 12/13/14 without hardwired conflicts.
- [ ] Validate ADC input scaling is performed externally and never exceeds 1.0 V at TOUT.
- [ ] Check RF keepout on motherboard, KiCad ERC/DRC, solderability, thermal measurements and EMC/ESD system-level requirements.

**Engineering status: accepted specification, not a completed / tested board.** Next deliverables: KiCad schematic → review/ERC → footprint and board layout → prototypes → measurements → revised BOM.

## 10. External primary references

- [ESP8266EX hardware design guidelines](https://documentation.espressif.com/esp8266_hardware_design_guidelines_en.html)
- [ESP8266EX datasheet](https://documentation.espressif.com/0a-esp8266ex_datasheet_en.html)
- [MAX3485 data](https://www.analog.com/en/products/max3485.html)
- Existing [RS-485 project notes](../../docs/rs485-hardware.md) and [validation plan](../../docs/validation-plan.md).
