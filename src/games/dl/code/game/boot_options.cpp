// Boot option wire format recovered from 0x1579F0 and 0x157B30.
// Eight little-endian bytes encoded as sixteen uppercase hexadecimal digits.
extern "C" {
extern unsigned char bootSettings[] __asm__("D_171D38");
extern unsigned int progressiveScan __asm__("D_0021DE6C");
extern unsigned int displayX __asm__("D_0021DAA8");
extern unsigned int displayY __asm__("D_0021DAAC");

void __attribute__((section(".boot_get_options"))) GetBootOptionsFromSettings(char *output)
{
    unsigned int words[2];
    words[0] = (bootSettings[0xB3] & 1)
             | ((progressiveScan & 1) << 1)
             | ((*reinterpret_cast<unsigned int *>(bootSettings + 8) & 1) << 2)
             | ((*reinterpret_cast<unsigned int *>(bootSettings + 12) & 0x7FF) << 3)
             | ((*reinterpret_cast<unsigned int *>(bootSettings + 16) & 0x7FF) << 14)
             | ((bootSettings[0xBD] & 7) << 25);
    // Bits 28..31 were uninitialized stack padding in the original encoder.
    // They are ignored by the decoder; emit zero for a deterministic string.
    words[1] = (displayX & 0xFFFF) | (displayY << 16);
    for (unsigned int i = 0; i < 8; ++i) {
        unsigned int byte = (words[i >> 2] >> ((i & 3) * 8)) & 0xFF;
        unsigned int high = byte >> 4;
        unsigned int low = byte & 15;
        *output++ = high < 10 ? high + '0' : high + 'A' - 10;
        *output++ = low < 10 ? low + '0' : low + 'A' - 10;
    }
    *output = 0;
}

void __attribute__((section(".boot_apply_options"))) ApplyBootOptionsToSettings(const char *input)
{
    unsigned int words[2] = {0, 0};
    unsigned char *bytes = reinterpret_cast<unsigned char *>(words);
    // Valid game input contains exactly eight pairs. Bound malformed input
    // instead of reproducing the original stack overflow/uninitialized reads.
    for (unsigned int i = 0; i < 8 && input[0] && input[1]; ++i, input += 2) {
        unsigned int high = static_cast<unsigned char>(input[0]);
        unsigned int low = static_cast<unsigned char>(input[1]);
        high = high - '0' < 10 ? high - '0' : high - 'A' < 6 ? high - 'A' + 10 : ~0U;
        low = low - '0' < 10 ? low - '0' : low - 'A' < 6 ? low - 'A' + 10 : ~0U;
        bytes[i] = static_cast<unsigned char>((high << 4) + low);
    }
    unsigned int flags = words[0];
    progressiveScan = (flags >> 1) & 1;
    bootSettings[0xB3] = flags & 1;
    bootSettings[0xBD] = (flags >> 25) & 7;
    *reinterpret_cast<unsigned int *>(bootSettings + 8) = (flags >> 2) & 1;
    *reinterpret_cast<unsigned int *>(bootSettings + 12) = (flags >> 3) & 0x7FF;
    *reinterpret_cast<unsigned int *>(bootSettings + 16) = (flags >> 14) & 0x7FF;
    displayX = words[1] & 0xFFFF;
    displayY = words[1] >> 16;
}
}
