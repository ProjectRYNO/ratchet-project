#include <cassert>
#include <cstring>
#include <cstdio>
extern "C" {
void GetBootOptionsFromSettings(char *output);
void ApplyBootOptionsToSettings(const char *input);
unsigned char bootSettings[0xC0] __attribute__((aligned(4)));
unsigned int progressiveScan;
unsigned int displayX;
unsigned int displayY;
}

static unsigned int &setting(unsigned int offset)
{
    return *reinterpret_cast<unsigned int *>(bootSettings + offset);
}

static void checkDecode(const char *text, unsigned int flags, unsigned int positions)
{
    std::memset(bootSettings, 0xA5, sizeof(bootSettings));
    ApplyBootOptionsToSettings(text);
    assert(progressiveScan == ((flags >> 1) & 1));
    assert(bootSettings[0xB3] == (flags & 1));
    assert(bootSettings[0xBD] == ((flags >> 25) & 7));
    assert(setting(8) == ((flags >> 2) & 1));
    assert(setting(12) == ((flags >> 3) & 0x7FF));
    assert(setting(16) == ((flags >> 14) & 0x7FF));
    assert(displayX == (positions & 0xFFFF));
    assert(displayY == (positions >> 16));
    for (unsigned int i = 0; i < sizeof(bootSettings); ++i)
        if (!(i >= 8 && i < 20) && i != 0xB3 && i != 0xBD)
            assert(bootSettings[i] == 0xA5);
}

int main()
{
    checkDecode("0000000000000000", 0, 0);
    checkDecode("FFFFFFFFFFFFFFFF", ~0U, ~0U);
    checkDecode("78563412CDAB3412", 0x12345678, 0x1234ABCD);
    // Original invalid-nibble behavior: -1 nibbles are added after shifting.
    checkDecode("gg00000000000000", 0xEF, 0);
    checkDecode("", 0, 0);
    checkDecode("F", 0, 0);
    checkDecode("12F", 0x12, 0);
    checkDecode("0000000000000000FFFFFFFF", 0, 0);
    unsigned int random = 0x12345678;
    for (unsigned int iteration = 0; iteration < 4096; ++iteration) {
        unsigned int values[8];
        for (unsigned int i = 0; i < 8; ++i) {
            random = random * 1664525U + 1013904223U;
            values[i] = random;
        }
        bootSettings[0xB3] = values[0];
        progressiveScan = values[1];
        setting(8) = values[2];
        setting(12) = values[3];
        setting(16) = values[4];
        bootSettings[0xBD] = values[5];
        displayX = values[6];
        displayY = values[7];
        unsigned int flags = (values[0] & 1) | ((values[1] & 1) << 1)
            | ((values[2] & 1) << 2) | ((values[3] & 0x7FF) << 3)
            | ((values[4] & 0x7FF) << 14) | ((values[5] & 7) << 25);
        unsigned int positions = (values[6] & 0xFFFF) | (values[7] << 16);
        char actual[19], expected[17];
        std::memset(actual, '#', sizeof(actual));
        GetBootOptionsFromSettings(actual + 1);
        assert(actual[0] == '#' && actual[18] == '#' && actual[17] == 0);
        unsigned int words[2] = {flags, positions};
        for (unsigned int i = 0; i < 8; ++i)
            std::sprintf(expected + i * 2, "%02X", (words[i / 4] >> ((i % 4) * 8)) & 255);
        assert(std::strcmp(actual + 1, expected) == 0);
        checkDecode(actual + 1, flags, positions);
    }
    std::puts("PASS: boot-option known vectors, malformed bounds, untouched fields, and 4096 round trips");
}
