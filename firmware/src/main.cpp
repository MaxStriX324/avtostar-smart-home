#include <Arduino.h>
#include "protocol.hpp"

#ifndef AVTOSTAR_ROLE
#error "AVTOSTAR_ROLE must be set by a PlatformIO environment"
#endif
#ifndef AVTOSTAR_RS485_ENABLED
#error "AVTOSTAR_RS485_ENABLED must be set by a PlatformIO environment"
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

}  // namespace

void setup() {
    // This is a **nonfunctional** development sketch.
    // Production WR firmware must coordinate UART0 with MAX3485 and flashing.
    Serial.begin(115200);
    delay(300);

    Serial.printf("AVTOSTAR Smart Home | %s | RS-485 assembly flag=%d\n",
                  roleName(), AVTOSTAR_RS485_ENABLED);
    Serial.println("SCAFFOLD ONLY: no real touch, relay, RS-485, ESP-NOW or web driver.");

    const avtostar::Message sample{
        avtostar::kProtocolVersion, avtostar::Opcode::Set,
        1, 2, 42, 1, 0, 1
    };
    uint8_t bytes[avtostar::kFrameSize] = {};
    if (avtostar::encodeFrame(sample, bytes, sizeof(bytes))) {
        Serial.print("Draft RS-485 frame:");
        for (uint8_t item : bytes) {
            Serial.printf(" %02X", item);
        }
        Serial.println();
    }
}

void loop() {
    delay(1000);
}
