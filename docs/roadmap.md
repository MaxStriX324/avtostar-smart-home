# Roadmap — ESP-12F / MAX3485 direction

## M0 — specifications and repo

- [x] Establish product family (Switch 2, Relay 2, Control).
- [x] Select ESP-12F for Switch 2 and Relay 2; MAX3485 for optional half-duplex RS-485.
- [x] Define **W (wireless)** / **WR (wireless + RS-485)** PCB assembly options.
- [x] Replace old CAN/TWAI scaffold with draft UART frame + host codec tests.
- [x] Accept separate ESP-12F universal debug-module v1.0 hardware decisions (pin map, LDO, removable RO/RX0 jumper, BOOT/RESET); schematic and PCB added.
- [ ] Validate that debug-module schematic/PCB meets its frozen specification (UMW capacitor stability, power, GPIO16 startup, RF, UART flashing).
- [ ] Freeze endpoint-specific power requirements, GPIO assignments and programming isolation topology.
- [ ] Approve low-voltage / mains product boundaries and component BOM.

## M1 — direct wireless pair

- [ ] ESP-12F Switch 2 W proof of concept, two external touch sensor inputs.
- [ ] ESP-12F Relay 2 W proof of concept with low-voltage dummy loads.
- [ ] Implement secure commissioning and direct ESP-NOW peer messaging.
- [ ] Implement idempotent commands, state reports, retries and deduplication.
- [ ] Test loss of router, gateway and Internet; measure latency and RF range.

## M1a — universal debug-module hardware validation

- [x] Freeze the [universal ESP-12F debug-module specification](../hardware/esp12f-debug-module/README.md).
- [x] Create and review ESP-12F + MAX3485 + AMS1117 KiCad schematic.
- [x] Implement 12-contact solder-on footprint and vertical 1x5 UART/jumper assembly.
- [x] Route PCB and publish KiCad project and BOM.
- [ ] Run native KiCad ERC/DRC, export STEP and complete Gerber/Excellon manufacturing set.
- [ ] Confirm UMW output-capacitor ESR, thermal budget, stable 3.3 V during Wi-Fi peaks.
- [ ] Validate GPIO16/DIR at power-up, reset, brownout; ensure no unintended RS-485 driver enable.
- [ ] Prototype BOOT/RESET and UART flashing with the RX0–RO jumper removed, then RS-485 with jumper installed.
- [ ] Prove I²C, HSPI, ADC and antenna keepout; capture measurements and BOM.

## M2 — wired WR prototype

- [ ] Draw MAX3485 UART0 circuit with boot/flash isolation and safe DE state.
- [ ] Draw one KiCad PCB for each endpoint with W/WR BOM variants.
- [ ] Implement UART0 + DE shift-register-safe turn-around handling.
- [ ] Prove 2-node controlled initiator/response RS-485.
- [ ] Select multi-node bus ownership, gateway integration and failure policy.
- [ ] Test termination, bias, surge, ESD, wiring errors and brownout.

## M3 — central controller and web

- [ ] ESP32-S3 Control proof of concept with RS-485.
- [ ] Local authenticated web UI / PWA for devices, channels, state and logs.
- [ ] Rules, scenes, scheduler, secure network bridge and update management.
- [ ] Optional MQTT / Home Assistant integration.

## M4 — product engineering

- [ ] Verified electrical schematics, KiCad board/ERC/DRC, assembly and manufacturing tests.
- [ ] Reliable recovery / update policies and security validation.
- [ ] Appropriate EMC, electrical isolation, load and safety testing for each use case.
- [ ] Final licensing, support strategy and commercialization requirements.
