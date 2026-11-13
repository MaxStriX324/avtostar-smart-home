# Validation plan — draft

## Bench: basic endpoint operations

- Flash both endpoint W variants, pair without an access point, command both outputs and verify acknowledgements.
- Repeat using WC variants over a correctly terminated CAN bus.
- Restart only switch, only relay, and both together; verify safe boot states and re-pairing persistence.
- Repeated/reordered/lost frames, sequence wrap, stale commands and Wi-Fi channel interference.
- Controller completely powered off: local switch ↔ relay behavior still works.
- Switch CAN cable unplugged and Wi-Fi link lost: test defined fallback and recovery without output glitches.
- 12 V / 24 V supply brownout, reversal, load transients; inspect consumption and thermal behavior.

## RF and bus characterization

- Range and packet loss across walls and within camper metal body.
- ESP-NOW latency, coexistence with Wi-Fi AP/STA and channel pinning.
- CAN termination, stub lengths, wiring errors, ESD and EMC immunity.
- ≥10-node synthetic traffic tests and broadcast loop suppression at gateway.

## Power and safety gates

- Protective fuses, thermal rise, PCB trace rating, relay contact derating for DC inductive loads.
- For mains: appropriate separation, surge protection, enclosure, touch safety, dielectric and applicable compliance evaluation.
- Never release a household mains or vehicle-ready product from firmware build success alone.

## Release criteria

- KiCad schematic/ERC and PCB/DRC reviews passed.
- Prototype BOM and assembly drawings signed off.
- Pin allocation and production provisioning confirmed.
- Automated protocol tests + human bench tests documented.
- Safe failure modes documented and demonstrated.
