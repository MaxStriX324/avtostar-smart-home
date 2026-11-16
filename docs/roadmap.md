# Roadmap — ESP-12F / MAX3485 direction

## M0 — specifications and repo

- [x] Establish product family (Switch 2, Relay 2, Control).
- [x] Select ESP-12F for Switch 2 and Relay 2; MAX3485 for optional half-duplex RS-485.
- [x] Define **W (wireless)** / **WR (wireless + RS-485)** PCB assembly options.
- [x] Replace old CAN/TWAI scaffold with draft UART frame + host codec tests.
- [ ] Freeze power requirements, GPIO assignments and programming isolation topology.
- [ ] Approve low-voltage / mains product boundaries and component BOM.

## M1 — direct wireless pair

- [ ] ESP-12F Switch 2 W proof of concept, two external touch sensor inputs.
- [ ] ESP-12F Relay 2 W proof of concept with low-voltage dummy loads.
- [ ] Implement secure commissioning and direct ESP-NOW peer messaging.
- [ ] Implement idempotent commands, state reports, retries and deduplication.
- [ ] Test loss of router, gateway and Internet; measure latency and RF range.

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
