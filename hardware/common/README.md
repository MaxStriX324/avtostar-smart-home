# Common hardware modules (not yet designed)

- ESP-12F boot/flash circuit: EN, RST, GPIO0, GPIO2, GPIO15 strapping; regulated 3.3 V and RF antenna keepout.
- MAX3485 WR: UART0 DI/RO, DE//RE direction pin and default disabled transmitter, bus ESD/TVS and connector.
- **Programming conflict**: UART0 RX GPIO3 must not have two competing push-pull drivers (RO and USB-UART). Provide isolation or receiver-disable option during flashing.
- Differential A/B routing, common reference, optional isolation, configurable endpoint termination (often 120 Ω), biasing network chosen by electrical calculation.
- W variant: MAX3485, protections/connector DNP as an assembly option; avoid unused floating MCU inputs.
- Board ID / assembly detection, factory test pads, defined output state while bootloader runs.

See [MAX3485 design notes](../../docs/rs485-hardware.md).
