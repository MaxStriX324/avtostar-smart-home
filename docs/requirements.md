# Requirements — draft v0.1

## Must have: endpoints

- Two capacitive touch inputs, configurable short/long/double press; external touch IC for ESP32-C3.
- Two independent relay/control outputs; clearly defined default and reboot states.
- Switch ↔ Relay 2 communication without router or gateway.
- Per-device persistent identifiers, endpoint bindings, local nonvolatile configuration.
- **One PCB revision per endpoint product**, two assembly variants W and WC.
- WC assembly retains Wi-Fi and adds wired CAN connectivity.
- No duplicated relay actions when messages arrive on two paths or are retried.
- Relay output must fail predictably upon reboot, undervoltage and communications failure.
- Local commissioning and factory reset procedures.

## Must have: central controller

- Optional topology; endpoints continue basic operation when Control fails.
- Device inventory, status and event history; Web UI accessible on a local network.
- Gateway between transport domains without bridge loops and duplicate execution.
- Rules, scenes, grouping, schedules, and manual overrides as later milestones.

## Nonfunctional goals to measure, not assume

- No cloud dependency for on/off commands.
- Latency target: define after physical switch-to-relay trials (including retransmission).
- Power budget, idle draw, surge withstand, wireless range and EMC: measure on prototype.
- CAN classic, initial target 125 or 250 kbit/s, final bit timing/bus cable by validation.
- Offline availability, interference tolerance, reconnection and reboot behavior: test.
- Auto-updates only after signed-image and rollback design is validated.

## Open decisions

1. Product supply ranges and separate low-voltage/230 V output boards.
2. Radio commissioning without a router (BLE available on ESP32-C3, or temporary Wi-Fi AP).
3. CAN connector, pinout, isolation requirement and termination-switch design.
4. Target installed node count and maximum network diameter (to determine whether true mesh is needed).
5. Standalone switch and relay power supply concept / mounting options.
