#include <Arduino.h>
#include "protocol.hpp"

#ifndef AVTOSTAR_ROLE
#error AVTOSTAR_ROLE must be defined by the selected PlatformIO environment
#endif

#ifndef AVTOSTAR_CAN_ENABLED
#error AVTOSTAR_CAN_ENABLED must be defined by the selected PlatformIO environment
#endif

namespace {
const char* roleName() {
#if AVTOSTAR_ROLE == 1
    return "Switch 2";
#elif AVTOSTAR_ROLE == 2
    return "Relay 2";
#elif AVTOSTAR_ROLE == 3
    return "Control";
#else
    return "Unknown";
#endif
}
}

void setup() {
    Serial.begin(115200);
    delay(500);
    Serial.printf("AVTOSTAR Smart Home | %s | CAN assembly flag=%d\n",
                  roleName(), AVTOSTAR_CAN_ENABLED);
    Serial.println("Firmware scaffold: NO relay, touch, ESP-NOW, CAN or Web control initialized.");

    const avtostar::Message msg{avtostar::kProtocolVersion,
                                avtostar::Opcode::Set, 1, 0, 42, 1};
    uint8_t payload[8] = {};
    avtostar::encodePayload(msg, payload);
    Serial.printf("Protocol v%u sample CAN id: 0x%08lX, data:",
                  avtostar::kProtocolVersion,
                  static_cast<unsigned long>(avtostar::makeCanId(
                      3, avtostar::MessageType::Command, 1, 2)));
    for (uint8_t b : payload) Serial.printf(" %02X", b);
    Serial.println();
}

void loop() {
    delay(1000);
}
