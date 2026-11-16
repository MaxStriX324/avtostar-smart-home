# Switch 2 — ESP-12F, 2-touch wall switch (no schematic yet)

- ESP-12F / ESP8266.
- Two external capacitive touch IC outputs to MCU GPIO.
- Two optional indicator LEDs, subject to pin and current budget.
- W: Wi-Fi + ESP-NOW, no RS-485 components fitted.
- WR: **same PCB** plus MAX3485 UART0 half-duplex transceiver, protection and terminal connector.
- Pin map **provisional**: GPIO4/5 touch inputs, GPIO12/13 indicators, GPIO14 DE; GPIO1/3 UART0 for WR.
- Check ESP8266 boot straps (GPIO0/2/15) and UART flashing isolation before committing schematic.
- Power and electrical safety need dedicated review for wall installation.

See [MAX3485 interface notes](../../docs/rs485-hardware.md).
