# Shared hardware blocks (to design)

- ESP32-C3 module / antenna keepout, boot and debug UART/USB provisioning.
- Supply input and protection appropriate to the chosen product/voltage.
- CAN TWAI (internal) → external 3.3 V logic transceiver with bus ESD and switchable end termination.
- CAN transceiver and connector DNP (do not populate) for W variant.
- Production test pads, unique board ID / assembly variant identification.
- Reference to the shared KiCad component library after checking symbols and footprints.
