# Firmware scaffold — ESP-12F and MAX3485 RS-485

PlatformIO environments reflect the selected endpoint hardware. **None of these builds currently controls real hardware**: there are no touch sensing, relay drivers, ESP-NOW, RS-485 UART driver, web interface, OTA or commissioning implementations.

## Build targets

```sh
cd firmware
pio run -e switch2_w
pio run -e switch2_wr
pio run -e relay2_w
pio run -e relay2_wr
pio run -e control
```

- `switch2_w`, `switch2_wr`, `relay2_w`, `relay2_wr`: `espressif8266`, `esp12e` PlatformIO reference module target. Actual ESP-12F module flash size/board settings must be confirmed against purchased part.
- `control`: `espressif32`, provisional ESP32-S3 development board.
- `AVTOSTAR_RS485_ENABLED` is currently an **assembly compile-time label only**, **not a functioning bus driver**.
- The scaffold writes diagnostic UART0 logs only. On WR production hardware UART0 is reserved for MAX3485, so debug logging, programming isolation and boot chatter must be designed appropriately.

## Native codec test

```sh
g++ -std=c++17 -Wall -Wextra -pedantic -I firmware/include firmware/test/test_protocol.cpp -o /tmp/avtostar-protocol-test
/tmp/avtostar-protocol-test
```

Run these commands from the **repository root**. This test checks only encoding and decoding of the version-1 16-byte RS-485 frame and CRC; it does **not** validate UART timing, DE direction control, bus arbitration, or hardware safety.

The old ESP32-C3 CAN/TWAI/WC environments are discontinued.
