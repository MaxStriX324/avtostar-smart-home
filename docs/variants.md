# Assembly and product variants

## Per endpoint: one PCB, two BOM/assembly variants

| Assembly | MCU | Wi-Fi / ESP-NOW | CAN peripheral | CAN connector | Same PCB revision |
| --- | --- | --- | --- | --- | --- |
| **W** | ESP32-C3 | Yes | Not populated | Not populated | Yes |
| **WC** | ESP32-C3 | Yes | Populated | Populated | Yes |

**The application protocol, identifiers, commissioning model, firmware repository and mechanical outer footprint stay common** wherever feasible. Variant selected by manufacturing options (BOM / assembly), with a reliable firmware detection/configuration policy later. Do not rely on firmware configuration alone for assembly variant identification.

## Distinct boards by product

- `hardware/switch-2`: switch PCB, 2 external capacitive inputs, indicator LEDs, appropriate power.
- `hardware/relay-2`: relay PCB, 2 isolated outputs and independently verified load/power design.
- `hardware/control`: gateway PCB, ESP32-S3, CAN + RS-485 (initial provisional specification).

The W/WC variants are **not** two independent PCB layouts. They are population options of each endpoint PCB. The switch, relay and gateway still require different PCBs unless their mechanical/electrical designs are intentionally consolidated later.

## Output voltage classes (separate design review)

| Candidate | Target environment | Safety note |
| --- | --- | --- |
| Relay 2 LV | 12/24 V DC camper use | High current, inductive load and battery surge protection |
| Relay 2 AC | 230 V AC house use | Mains isolation, creepage/clearance, rated protective components and certification |

Do not simply mix 230 V AC and vehicle 12/24 V in one unreviewed layout to preserve board count.
