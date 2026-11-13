#include <cassert>
#include <cstdint>
#include <iostream>
#include "protocol.hpp"

int main() {
    using namespace avtostar;
    constexpr uint32_t id = makeCanId(3, MessageType::Command, 10, 23);
    static_assert(id <= 0x1FFFFFFFul, "CAN extended identifier overflow");
    static_assert(canPriority(id) == 3, "priority extract");
    static_assert(canMessageType(id) == 1, "type extract");
    static_assert(canSource(id) == 10, "source extract");
    static_assert(canDestination(id) == 23, "destination extract");

    const Message input{kProtocolVersion, Opcode::Set, 2, 0x81, 0x1234, 1};
    uint8_t raw[8] = {};
    encodePayload(input, raw);
    assert(raw[0] == 1 && raw[1] == 1 && raw[2] == 2 && raw[3] == 0x81);
    assert(raw[4] == 0x34 && raw[5] == 0x12 && raw[6] == 1 && raw[7] == 0);
    Message parsed{};
    assert(decodePayload(raw, parsed));
    assert(parsed.version == 1 && parsed.opcode == Opcode::Set);
    assert(parsed.channel == 2 && parsed.sequence == 0x1234);
    assert(parsed.value == 1 && parsed.flags == 0x81);
    raw[0] = 2;
    assert(!decodePayload(raw, parsed));
    raw[0] = 1;
    raw[1] = 0;
    assert(!decodePayload(raw, parsed));
    std::cout << "PASS: AVTOSTAR protocol header encoding and decoding\n";
}
