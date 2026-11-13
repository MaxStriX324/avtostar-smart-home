# Initial implementation backlog

Priority order:

1. ESP32-C3 GPIO map by board and bootstrapping limitations.
2. Endpoint voltage input targets, idle draw and protection.
3. CAN transceiver/ESD/connector/termination BOM and W/WC assembly drawing.
4. Direct ESP-NOW pairing / device binding without gateway.
5. Relay command/state machine: retry, ACK, duplicate suppression, watchdog and reboot state.
6. Physical two-channel touch design (external sensor ICs) and feedback LEDs.
7. CAN/TWAI abstraction and protocol conformance tests.
8. Gateway on ESP32-S3 and browser/PWA interface.
9. Security review, OTA, reproducible builds and hardware validation reports.

Every feature should have its implementation, test evidence and hardware revision traceability before it is marked released.
