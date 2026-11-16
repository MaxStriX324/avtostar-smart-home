# Verification and safety plan — ESP-12F + RS-485

## Core function

- Pair Switch 2 W to Relay 2 W over ESP-NOW with no access point, router, internet or gateway.
- Verify two distinct touch events and two independently controlled outputs, with physical safe test loads.
- Repeat WR test via MAX3485 on a correctly wired and terminated two-node RS-485 line.
- Confirm UART flashing/debug setup cannot contend with an enabled MAX3485 RO driver.
- Confirm UART ROM messages cannot leak onto A/B while DE is held inactive by hardware.
- Test idle bias, CRC corruption, half-duplex DE turn-around, ACK timeouts, retries and duplicate suppression.
- Two-node initiator/responder: ensure only one node drives the bus during any transmission window.
- Multinode bus: verify ownership scheduling and emergency gateway disappearance before release.

## Failure / environment

- Reboot one or both nodes and remove Control: direct ESP-NOW binding still works.
- Unplug RS-485, interfere with Wi-Fi and reset the gateway; outputs remain in documented safe states.
- Power cycling, brownout, 12/24 V surges, reverse polarity and voltage drop under simultaneous Wi-Fi TX and output drive.
- Validate ESP8266 bootstrapping GPIO levels under relay/touch front-end connection.
- RF range and coexistence in metal camper body and across house walls.
- Bus length and signal integrity over selected cable, TVS, grounding, termination and bias network.
- Separate AC mains dielectric, creepage/clearance and approval testing before any consumer installation.

## Release gate

- KiCad ERC/DRC, formal schematic review, board revision and BOM traceability.
- Host protocol codec tests + on-device transport reliability tests.
- Characterized load and thermal margins plus fault and reset test reports.
- Security and OTA rollback evaluation; never sell a device solely on scaffold build success.
