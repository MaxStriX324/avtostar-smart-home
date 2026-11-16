#pragma once

// Transport-neutral logical message with a draft RS-485 UART wire envelope.
// A CRC is not a command authenticator. No real bus arbitration/driver lives here.

#include <stddef.h>
#include <stdint.h>

namespace avtostar {

constexpr uint8_t kProtocolVersion = 1;
constexpr uint16_t kBroadcastNode = 0;
constexpr uint16_t kMaxNode = 1023;
constexpr size_t kFrameSize = 16;
constexpr uint8_t kFrameMarker1 = 0xA5;
constexpr uint8_t kFrameMarker2 = 0x5A;

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
    uint16_t source;
    uint16_t destination;
    uint16_t sequence;
    uint8_t channel;
    uint8_t flags;
    uint16_t value;
};

inline uint16_t crc16Modbus(const uint8_t* data, size_t length) {
    uint16_t crc = 0xFFFFu;
    for (size_t i = 0; i < length; ++i) {
        crc ^= static_cast<uint16_t>(data[i]);
        for (uint8_t bit = 0; bit < 8u; ++bit) {
            crc = (crc & 1u) != 0u
                ? static_cast<uint16_t>((crc >> 1u) ^ 0xA001u)
                : static_cast<uint16_t>(crc >> 1u);
        }
    }
    return crc;
}

inline void write16(uint8_t* bytes, uint16_t value) {
    bytes[0] = static_cast<uint8_t>(value & 0xFFu);
    bytes[1] = static_cast<uint8_t>((value >> 8u) & 0xFFu);
}

inline uint16_t read16(const uint8_t* bytes) {
    return static_cast<uint16_t>(
        static_cast<uint16_t>(bytes[0]) |
        static_cast<uint16_t>(static_cast<uint16_t>(bytes[1]) << 8u));
}

inline bool validOpcode(uint8_t opcode) {
    return opcode >= static_cast<uint8_t>(Opcode::Set) &&
           opcode <= static_cast<uint8_t>(Opcode::Error);
}

inline bool encodeFrame(const Message& msg, uint8_t* output, size_t length) {
    if (output == nullptr || length < kFrameSize ||
        msg.version != kProtocolVersion ||
        !validOpcode(static_cast<uint8_t>(msg.opcode)) ||
        msg.source == 0 || msg.source > kMaxNode ||
        msg.destination > kMaxNode) {
        return false;
    }

    output[0] = kFrameMarker1;
    output[1] = kFrameMarker2;
    output[2] = msg.version;
    output[3] = static_cast<uint8_t>(msg.opcode);
    write16(output + 4, msg.source);
    write16(output + 6, msg.destination);
    write16(output + 8, msg.sequence);
    output[10] = msg.channel;
    output[11] = msg.flags;
    write16(output + 12, msg.value);
    write16(output + 14, crc16Modbus(output, 14));
    return true;
}

inline bool decodeFrame(const uint8_t* input, size_t length, Message& msg) {
    if (input == nullptr || length != kFrameSize ||
        input[0] != kFrameMarker1 || input[1] != kFrameMarker2 ||
        input[2] != kProtocolVersion || !validOpcode(input[3])) {
        return false;
    }
    if (read16(input + 14) != crc16Modbus(input, 14)) {
        return false;
    }
    const uint16_t source = read16(input + 4);
    const uint16_t destination = read16(input + 6);
    if (source == 0 || source > kMaxNode || destination > kMaxNode) {
        return false;
    }
    Message parsed;
    parsed.version = input[2];
    parsed.opcode = static_cast<Opcode>(input[3]);
    parsed.source = source;
    parsed.destination = destination;
    parsed.sequence = read16(input + 8);
    parsed.channel = input[10];
    parsed.flags = input[11];
    parsed.value = read16(input + 12);
    msg = parsed;
    return true;
}

}  // namespace avtostar
