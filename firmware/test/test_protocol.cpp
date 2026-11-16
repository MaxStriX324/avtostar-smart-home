#include <cassert>
#include <cstdint>
#include <iostream>
#include "protocol.hpp"

int main() {
    using namespace avtostar;

    const Message send{kProtocolVersion, Opcode::Set, 12, 27, 0x1234, 2, 0x80, 1};
    uint8_t wire[kFrameSize] = {};
    assert(encodeFrame(send, wire, sizeof(wire)));
    assert(wire[0] == 0xA5 && wire[1] == 0x5A);
    assert(wire[2] == 1 && wire[3] == 1);
    assert(wire[4] == 12 && wire[5] == 0);
    assert(wire[6] == 27 && wire[7] == 0);
    assert(wire[8] == 0x34 && wire[9] == 0x12);
    assert(wire[10] == 2 && wire[11] == 0x80);
    assert(wire[12] == 1 && wire[13] == 0);

    Message received;
    assert(decodeFrame(wire, sizeof(wire), received));
    assert(received.source == send.source &&
           received.destination == send.destination &&
           received.sequence == send.sequence &&
           received.channel == send.channel &&
           received.flags == send.flags &&
           received.value == send.value &&
           received.opcode == send.opcode);

    // Bad payload CRC must be rejected.
    wire[12] ^= 0x01;
    assert(!decodeFrame(wire, sizeof(wire), received));
    wire[12] ^= 0x01;

    // Unknown version, opcode, truncation, illegal source, and wrong SOF.
    wire[2] = 2;
    assert(!decodeFrame(wire, sizeof(wire), received));
    wire[2] = 1;
    wire[3] = 0;
    assert(!decodeFrame(wire, sizeof(wire), received));
    wire[3] = 1;
    assert(!decodeFrame(wire, sizeof(wire)-1, received));

    const Message noSource{kProtocolVersion, Opcode::Set, 0, 27, 7, 1, 0, 1};
    assert(!encodeFrame(noSource, wire, sizeof(wire)));

    // Standard CRC-16/Modbus check vector.
    const uint8_t probe[] = {'1','2','3','4','5','6','7','8','9'};
    assert(crc16Modbus(probe, sizeof(probe)) == 0x4B37u);

    std::cout << "PASS: AVTOSTAR RS-485 draft frame and CRC-16 codec\n";
    return 0;
}
