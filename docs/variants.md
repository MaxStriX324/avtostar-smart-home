# Hardware assembly variants — fixed concept

There is **one PCB layout per endpoint role** and **two production assembly variants**.

| Population | Endpoint MCU | Wireless | MAX3485 | Wired interface |
| --- | --- | --- | --- | --- |
| **W** | ESP-12F | Wi-Fi + ESP-NOW | DNP | Not fitted |
| **WR** | ESP-12F | Wi-Fi + ESP-NOW | Fitted | RS-485 half-duplex |

Both assembly options use the same PCB artwork and largely shared firmware. Production detection/configuration must be deliberate: a compile flag alone does **not** detect a populated MAX3485.

- `hardware/switch-2/`: a dedicated two-touch-key Switch 2 board.
- `hardware/relay-2/`: a separate Relay 2 board with two output drivers.
- `hardware/control/`: separate gateway board (ESP32-S3 tentative), RS-485 to endpoints.

W is **not** a fully wired CAN product. WR provides **Wi-Fi + RS-485**, not CAN. The former WC naming and the ESP32-C3/TWAI/MCP2515 branch are superseded.

## Safety and power variants

A **single W/WR PCB population choice** does not imply a single universal power/output design for all voltage classes. Vehicle 12/24 V DC and mains 230 V AC require independent electrical, insulation, load and regulatory reviews; there may be different relay power/output board revisions even when the logical device protocol is the same.

## BOM population logic

| Designator/function | W | WR |
| --- | --- | --- |
| ESP-12F / 3.3 V power / flash access | Fit | Fit |
| Role-specific sensing or output drivers | Fit | Fit |
| MAX3485, RS-485 connector, protection | DNP | Fit |
| RS-485 termination and idle bias | Site/position specific | Site/position specific |
| Wireless antenna keepout | Required | Required |

The board must keep termination **configurable**, not always enabled at every WR node.

## Separate development/debug module

The accepted [ESP-12F universal debug module](../hardware/esp12f-debug-module/README.md) has ESP-12F, MAX3485 and AMS1117-3.3 fitted on a small solder-on daughterboard. It is a **separate engineering test article**, not an additional W/WR population of the Switch 2 or Relay 2 PCB. The endpoint W/WR assembly rules above remain as specified.
