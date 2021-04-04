#include <iostream>
#include <vector>
#include <cstddef>
#include <cassert>

bool is1ByteUtf8(std::byte code_point) {
    return static_cast<uint8_t>(code_point) <= 0x7F;
}

size_t getFollowByteCount(std::byte code_point) {
    if ((static_cast<uint8_t>(code_point) >> 5) == 6) {
        return 1; // 1 byte more to scan
    }
    if ((static_cast<uint8_t>(code_point) >> 4) == 0xE) {
        return 2; // 2 byte more to scan
    }
    if ((static_cast<uint8_t>(code_point) >> 3) == 0x1E) {
        return 3; //3 bytes more to scan
    }
    return 0;
}

bool isUtf8FollowByte(std::byte code_point) {
    if ((static_cast<uint8_t>(code_point) >> 6) != 2) {
        return false;
    }
    return true;
}

bool isUtf8(const std::vector<std::byte> &buffer) {
    auto bytes_following = 0U;
    for (auto code_point : buffer) {
        if (bytes_following) {
            if (isUtf8FollowByte(code_point)) {
                --bytes_following;
                continue;
            }
            return false;
        }
        if (is1ByteUtf8(code_point)) {
            continue;
        }
        bytes_following = getFollowByteCount(code_point);
        if (bytes_following == 0) {
            return false;
        }
    }
    return (bytes_following == 0);
}

int main() {
    {
        std::vector<std::byte> bad_utf8_1byte{std::byte{0x80}};
        assert(!isUtf8(bad_utf8_1byte));
        std::vector<std::byte> utf8_1byte{std::byte(0x7F)};
        assert(isUtf8(utf8_1byte));
    }
    {
        std::vector<std::byte> bad_utf8_2byte{std::byte(0xC0), std::byte(0xC0)};
        assert(!isUtf8(bad_utf8_2byte));
        std::vector<std::byte> bad_utf8_2byte_short{std::byte(0xC0)};
        assert(!isUtf8(bad_utf8_2byte_short));
        std::vector<std::byte> utf8_2byte{std::byte(0xC0), std::byte(0x80)};
        assert(isUtf8(utf8_2byte));
    }
    {
        std::vector<std::byte> bad_utf8_3byte{std::byte(0xE0), std::byte(0x80), std::byte(0xC0)};
        assert(!isUtf8(bad_utf8_3byte));
        std::vector<std::byte> bad_utf8_3byte_short{std::byte(0xE0), std::byte(0x80)};
        assert(!isUtf8(bad_utf8_3byte_short));
        std::vector<std::byte> utf8_3byte{std::byte(0xE0), std::byte(0x80), std::byte(0x80)};
        assert(isUtf8(utf8_3byte));
    }
    {
        std::vector<std::byte> bad_utf8_4byte{std::byte(0xF0), std::byte(0x80), std::byte(0x80), std::byte(0xC0)};
        assert(!isUtf8(bad_utf8_4byte));
        std::vector<std::byte> bad_utf8_4byte_short{std::byte(0xF0), std::byte(0x80), std::byte(0x80)};
        assert(!isUtf8(bad_utf8_4byte_short));
        std::vector<std::byte> utf8_4byte{std::byte(0xF0), std::byte(0x80), std::byte(0x80), std::byte(0x80)};
        assert(isUtf8(utf8_4byte));
    }

    std::cout << "All tests succeeded\n";
}