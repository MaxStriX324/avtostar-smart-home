#pragma once

#include <stdint.h>

namespace avtostar {

constexpr uint8_t kProtocolVersion = 1;
constexpr uint16_t kBroadcastNode = 0;
constexpr uint16_t kMaxNode = 1023;

enum class MessageType : uint8_t {
    Command = 1,
    State = 2,
    Ack = 3,
    Heartbeat = 4,
    Error = 5,
};

enum class Opcode : uint8_t {
    Set = 1,
    State = 2,
    Ack = 3,
    Heartbeat = 4,
    Error = 5,
};

struct Message {
    uint8_t version;
    Opcode opcode;
    uint8_t channel;
    uint8_t flags;
    uint16_t sequence;
    uint16_t value;
};

// CAN extended 29-bit identifier: [priority:3][type:6][src:10][dst:10]
constexpr uint32_t makeCanId(uint8_t priority, MessageType type,
                             uint16_t src, uint16_t dst) {
    return (static_cast<uint32_t>(priority & 0x07u) << 26u) |
           (static_cast<uint32_t>(static_cast<uint8_t>(type) & 0x3fu) << 20u) |
           (static_cast<uint32_t>(src & 0x03ffu) << 10u) |
           static_cast<uint32_t>(dst & 0x03ffu);
}

constexpr uint8_t canPriority(uint32_t id) {
    return static_cast<uint8_t>((id >> 26u) & 0x07u);
}
constexpr uint8_t canMessageType(uint32_t id) {
    return static_cast<uint8_t>((id >> 20u) & 0x3fu);
}
constexpr uint16_t canSource(uint32_t id) {
    return static_cast<uint16_t>((id >> 10u) & 0x03ffu);
}
constexpr uint16_t canDestination(uint32_t id) {
    return static_cast<uint16_t>(id & 0x03ffu);
}

inline void encodePayload(const Message& message, uint8_t out[8]) {
    out[0] = message.version;
    out[1] = static_cast<uint8_t>(message.opcode);
    out[2] = message.channel;
    out[3] = message.flags;
    out[4] = static_cast<uint8_t>(message.sequence & 0xffu);
    out[5] = static_cast<uint8_t>((message.sequence >> 8u) & 0xffu);
    out[6] = static_cast<uint8_t>(message.value & 0xffu);
    out[7] = static_cast<uint8_t>((message.value >> 8u) & 0xffu);
}

inline bool decodePayload(const uint8_t data[8], Message& out) {
    if (!data || data[0] != kProtocolVersion) return false;
    if (data[1] < 1u || data[1] > 5u) return false;
    out.version = data[0];
    out.opcode = static_cast<Opcode>(data[1]);
    out.channel = data[2];
    out.flags = data[3];
    out.sequence = static_cast<uint16_t>(data[4]) |
                   static_cast<uint16_t>(static_cast<uint16_t>(data[5]) << 8u);
    out.value = static_cast<uint16_t>(data[6]) |
                static_cast<uint16_t>(static_cast<uint16_t>(data[7]) << 8u);
    return true;
}

} // namespace avtostar
