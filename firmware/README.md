# Firmware scaffolding

PlatformIO environments represent product roles and assembly variants. They currently **only print identity and a protocol test frame to UART**. No real touch, relay, CAN, ESP-NOW, provisioning, HTTP server, or OTA driver exists. Nothing in this folder is ready for deployment to a powered output product.

Commands (requires PlatformIO):

```sh
pio run -e switch2_w
pio run -e switch2_wc
pio run -e relay2_w
pio run -e relay2_wc
pio run -e control
```

Host protocol header smoke test:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude test/test_protocol.cpp -o /tmp/avtostar-test
/tmp/avtostar-test
```

Pin map, support for real board targets and variants detection will be added after electrical review. The current `-DAVTOSTAR_CAN_ENABLED` build flag **does not imply working CAN**.
