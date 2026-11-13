# Switch 2 PCB — not yet designed

Planned: ESP32-C3, two **external** capacitive touch channels (C3 has no native touch sensor interface), status LEDs, low-voltage power and optional CAN transceiver/connector population.

- `Switch2-W`: same PCB, Wi-Fi / ESP-NOW only; CAN DNP.
- `Switch2-WC`: same PCB, Wi-Fi / ESP-NOW + CAN.

To decide: power feed, size, mounting, waterproofing, LED/current budget, PCB copper touch pad / overlay details, ESD, ESP32-C3 strapping-safe GPIO mapping.
