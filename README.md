# AVTOSTAR Smart Home

**Modular automation for stationary homes and camper vans**  
**Powered by MaxStriX324**

> **Status: concept / initial engineering scaffold, 2026-11-14.** No verified schematic, PCB, wiring instructions, tested firmware, or certified products are published yet. The firmware builds are placeholders and **do not operate physical relays**.

## Goal

Local-first automation where **Switch 2** can control **Relay 2** with no router, internet connection, or central controller. Optional **Control** gateway adds a web dashboard, scenarios, CAN/RS-485 integration and device management.

## Product family

| Device | MCU (provisional) | Functions | Connectivity |
| --- | --- | --- | --- |
| Switch 2 | ESP32-C3 | 2 capacitive keys (external touch ICs), indicators | Wi-Fi / ESP-NOW, optional CAN |
| Relay 2 | ESP32-C3 | 2 independently controlled outputs | Wi-Fi / ESP-NOW, optional CAN |
| Control | ESP32-S3 | gateway, rules, scheduling, web UI, diagnostics | Wi-Fi, CAN, RS-485 (planned) |

## One PCB, two configurations

There are **two assembly variants of each endpoint PCB** (Switch 2 and Relay 2):

- **W (Wireless):** ESP32-C3 + Wi-Fi / ESP-NOW, CAN components not populated.
- **WC (Wireless + CAN):** the **same PCB and the same firmware codebase**, with CAN transceiver/protection/connectors populated and CAN enabled in configuration.

The CAN-capable version **retains Wi-Fi**, it is not a CAN-only unit. The central controller is a different PCB. The wall switch and the relay also have **different power/output PCBs**; "one PCB" refers to one unified revision *per product*, not one PCB shared by a mains relay and a wall switch.

## Key architectural decisions

1. The switch–relay binding and last valid settings must reside on endpoints; Control is optional.
2. Direct **ESP-NOW** is the v0 wireless transport. It is peer-to-peer and **not automatically multihop mesh**. Multihop routing is a later, separately verified feature.
3. CAN is the wired peer transport using ESP32-C3's built-in **TWAI** controller with an external transceiver.
4. Shared transport-independent application protocol. Deduplication, acknowledgements and synchronized state must be implemented before outputs become active.
5. Phone access via the Control gateway's local Web UI / PWA; internet/cloud is optional and is **not required for basic control**.
6. Separate variants for 12/24 V DC and 230 V AC output safety. Never assume a single relay power layout is suitable for both.

## Layout

| Path | Purpose |
| --- | --- |
| [docs/architecture.md](docs/architecture.md) | Overall topology, device responsibilities, network resilience |
| [docs/requirements.md](docs/requirements.md) | Functional / nonfunctional requirements |
| [docs/variants.md](docs/variants.md) | Two PCB assembly variants and preliminary product variants |
| [docs/protocol.md](docs/protocol.md) | Draft message model and CAN mapping |
| [docs/security.md](docs/security.md) | Commissioning, authentication, secure OTA, network separation |
| [docs/validation-plan.md](docs/validation-plan.md) | Safety / bench / fault tests |
| [docs/roadmap.md](docs/roadmap.md) | Phased engineering plan and milestone checklist |
| [hardware/](hardware/) | KiCad source folders (no electrical designs released) |
| [firmware/](firmware/) | PlatformIO firmware skeleton and protocol header |
| [LICENSING.md](LICENSING.md) | Licensing decisions outstanding |

## Build scaffold (not deployable)

```bash
cd firmware
pio run -e switch2_w
pio run -e switch2_wc
pio run -e relay2_w
pio run -e relay2_wc
pio run -e control
```

The chosen development board names are temporary references, **not** a confirmed product pinout. These builds print boot diagnostics only and deliberately do not drive GPIO, relays or CAN. Unit test for the standalone protocol header:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -Ifirmware/include firmware/test/test_protocol.cpp -o /tmp/avtostar-test
/tmp/avtostar-test
```

**Safety:** do not connect unvalidated boards to 230 V mains, safety-critical vehicle circuits, batteries without proper protections, or public internet interfaces.

**AVTOSTAR Smart Home — Powered by MaxStriX324.**
