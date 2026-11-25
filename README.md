# AVTOSTAR Smart Home

**Local-first modular automation for stationary houses and camper vans**  
**Powered by MaxStriX324**

> Status: engineering concept / firmware scaffold (November 2026). The ESP-12F debug module KiCad design is available; endpoint firmware and product qualification remain in development.

## Универсальный отладочный модуль ESP-12F

Отдельная дочерняя плата для пайки на материнскую плату: ESP-12F, MAX3485, AMS1117-3.3, пять универсальных GPIO, ADC, кнопки BOOT и RESET, перемычка RO↔RX0 для прошивки по UART0. Модуль предназначен для разработки и отладки решений AVTOSTAR.

- [Техническое описание модуля](hardware/esp12f-debug-module/README.md)
- [Исходный проект KiCad](hardware/esp12f-debug-module/kicad/)
- [Конфигурация модуля](docs/esp12f-debug-module-decisions.md)

## Objective

Two types of autonomous endpoints — a two-touch-button wall switch and a two-output relay module — can operate directly over Wi-Fi/ESP-NOW without an internet connection, router or central controller. A future central gateway adds browser/PWA control, scenarios, scheduling, diagnostics and wired RS-485 device management.

## Devices

| Product | Processor | Functions | Communications |
| --- | --- | --- | --- |
| **Switch 2** | **ESP-12F / ESP8266** | Two external capacitive touch inputs, optional indicators | Wi-Fi / ESP-NOW, optional RS-485 |
| **Relay 2** | **ESP-12F / ESP8266** | Two independently controlled outputs | Wi-Fi / ESP-NOW, optional RS-485 |
| **Control** | ESP32-S3 (tentative) | Local web dashboard, automation, network bridging | Wi-Fi + RS-485 planned |

**MAX3485 is an RS-485 transceiver, not a CAN controller or CAN transceiver. CAN and MCP2515 have been removed from the selected endpoint baseline.**

## One PCB per endpoint, two assembly variants

- **W — Wireless:** ESP-12F + Wi-Fi / ESP-NOW; the MAX3485 and its wired interface components are not populated.
- **WR — Wireless + RS-485:** **the same Switch 2 or Relay 2 PCB** with MAX3485, wired connector and required protection components fitted. Wireless functions remain present.

Switch 2 and Relay 2 are **different PCB designs**, each with a common W/WR layout and population options. A mains-power relay and an automotive low-voltage relay may also need different power/output hardware, to be evaluated separately. The central Control is its own board.

## Core design principles

1. Store paired-device binding and safe configuration locally, at the endpoints; Control is optional for basic wireless use.
2. Use direct **ESP-NOW** for the first switch-to-relay prototype. ESP-NOW alone does **not** deliver automatic multihop mesh routing.
3. For WR, use **3.3 V MAX3485 + ESP8266 UART0** on a **half-duplex RS-485 multidrop bus**, with explicit driver-enable management.
4. RS-485 has **no CAN-style collision arbitration**. Design a bus access/scheduling protocol before multi-node deployment; never let multiple independent masters transmit indiscriminately.
5. Use an application-level command and state protocol common to wireless and wired transports, with acknowledgements, deduplication and safe relay boot behavior.
6. Provide phone access initially through the gateway's authenticated local web interface, not by assuming a phone can speak ESP-NOW directly.
7. Protect supplies and outputs for the target environment. Do not assume 12/24 V vehicle and 230 V AC building variants are electrically interchangeable.

## Repository map

- [hardware/esp12f-debug-module/README.md](hardware/esp12f-debug-module/README.md) — описание универсального отладочного модуля
- [docs/esp12f-debug-module-decisions.md](docs/esp12f-debug-module-decisions.md) — принятые аппаратные решения
- [docs/architecture.md](docs/architecture.md) — topology, failover boundaries and gateway
- [docs/requirements.md](docs/requirements.md) — current endpoint requirements
- [docs/variants.md](docs/variants.md) — W / WR assembly variants
- [docs/rs485-hardware.md](docs/rs485-hardware.md) — MAX3485, UART and wiring constraints
- [docs/protocol.md](docs/protocol.md) — draft transport-neutral message framing
- [docs/security.md](docs/security.md) — commissioning and security
- [docs/validation-plan.md](docs/validation-plan.md) — safety and communication test gates
- [docs/roadmap.md](docs/roadmap.md) — phased build plan
- [hardware/](hardware/) — hardware projects and planning
- [firmware/](firmware/) — PlatformIO build scaffolds and wire-codec test

## Build scaffolds (not operational firmware)

```sh
cd firmware
pio run -e switch2_w
pio run -e switch2_wr
pio run -e relay2_w
pio run -e relay2_wr
pio run -e control
```

The firmware is a **nonfunctional scaffold**: neither relay drivers nor real RS-485, ESP-NOW, touch input, gateway web UI or OTA are implemented. Product pinouts remain provisional.

A native C++ wire-codec test can be compiled separately; see [firmware/README.md](firmware/README.md).

**Safety:** do not connect these prototypes to 230 V AC, safety-critical vehicle systems or unprotected high-energy supplies.

**AVTOSTAR Smart Home — Powered by MaxStriX324.**
