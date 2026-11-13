# Roadmap / implementation phases

## M0 — repository and specification (this commit)

- [x] Define product names, roles and W/WC shared-PCB assembly concept.
- [x] Create protocol message schema draft, initial test and compile skeleton.
- [x] Draft architecture, threat model, validation and engineering checklist.
- [ ] Choose component part numbers and power requirements.
- [ ] Choose per-product schematic pin allocation and connector conventions.

## M1 — two-node wireless prototype

- [ ] Build Switch 2 W on ESP32-C3 reference hardware with two touch sensors.
- [ ] Build Relay 2 W on a safe low-voltage reference board with dummy loads.
- [ ] Implement pairing, credential storage, direct ESP-NOW messages and status.
- [ ] Implement idempotent commands, per-peer deduplication, retries, watchdog.
- [ ] Record latency, power and packet loss test data.

## M2 — CAN/WC prototype

- [ ] Select and verify transceiver and connector, termination and bus protection.
- [ ] Design per-product W/WC KiCad boards and assembly BOM options.
- [ ] Implement TWAI transport and peer-to-peer control without Control.
- [ ] Validate bus disconnect, redundant-path failure and error recovery.

## M3 — gateway and browser

- [ ] ESP32-S3 Control board with CAN/RS-485 and provisioning.
- [ ] Web UI / PWA: devices, channels, state, binding, logs, rules.
- [ ] Transport bridge with loop avoidance and state synchronization.
- [ ] Optional integration with MQTT / Home Assistant.

## M4 — productization

- [ ] Manufacturing/diagnostics fixtures, installation manuals, enclosure design.
- [ ] Signed OTA and recoverable rollback.
- [ ] Separate LV/AC electrical and regulatory reviews, EMC and load testing.
- [ ] Select firmware/hardware/documentation licenses and trademark policy.
- [ ] Define serial numbers, provisioning, support and production test reports.
