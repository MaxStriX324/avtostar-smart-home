# ESP-12F universal debug module — accepted design record

**Decision date:** 2026-11-16  
**Design revision:** 1.0 (documentation baseline)  
**Implementation state:** no verified schematic, PCB, or prototype yet.

**Approved scope:** a standalone solder-on debugging/development module, independent from the Switch 2 / Relay 2 product PCBs and their W/WR assembly variants.

**Locked for v1 schematic:**

1. Three main ICs: ESP-12F + MAX3485 + AMS1117-3.3 UMW SOT-223; regulated 5 V input.
2. Five general digital lines: GPIO4/5/12/13/14; GPIO0/2/15 kept only for correct boot.
3. GPIO16 solely for MAX3485 DE and /RE, external 10 kΩ to GND. No Deep Sleep GPIO16→RST wake.
4. UART0 TX0/RX0 shared with RS-485; MAX3485 RO connected to RX0 through a removable jumper.
5. Right-angle **1x5** programming connector, pins **5V, GND, TX0, RX0, RO**, with jumper on adjacent pins **4–5**.
6. Onboard **BOOT** (GPIO0→GND) and **RESET** (RST→GND) momentary switches.
7. Two LEDs: +5 V and +3.3 V only. No activity or GPIO LEDs, no logic buffer IC.
8. 12 solder-on motherboard pads; 5 GPIOs plus ADC 0–1 V, 5V/GND/+3V3, RS485 A/B and second GND.
9. Motherboard is responsible for input protection, ADC divider, I²C pulls, bus termination/bias and TVS.

**Not yet validated:** UMW capacitor ESR/stability, thermal design, DIR boot glitches, RS-485 wiring/ground protection, mechanical/antenna keepout and firmware transport drivers.

**Full engineering specification:** [hardware/esp12f-debug-module/README.md](../hardware/esp12f-debug-module/README.md). Do not label this a manufactured, tested or released product.
