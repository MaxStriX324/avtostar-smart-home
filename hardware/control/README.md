# AVTOSTAR Control board — concept

Central controller remains provisionally ESP32-S3; this is **not** an endpoint ESP-12F board.

- Wired network: half-duplex RS-485 to endpoint WR nodes via suitable transceiver (MAX3485 or alternative).
- Wireless: ordinary Wi-Fi/IP to local browser and ESP-NOW handling as design/testing permits.
- Scenarios, Web UI/PWA, diagnostics, secure commissioning and OTA planned.
- Optional RS-485 coordinator role; bus handover/failover must be deterministic and collision-free.
- Endpoint switch-to-relay direct ESP-NOW behavior must not require the gateway.

Power range, isolation, connectors and final microcontroller are not frozen.
