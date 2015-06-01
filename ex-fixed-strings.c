#include "common.h"

int main() {
    uint32_t n32 = 0x68f7a38b;
    char str[] = "FooBar";
    size_t str_len = 10;
    uint16_t n16 = 0xee12;
    uint8_t ser[16];

    size_t str_real_len = strlen(str);
    size_t str_pad_len = str_len - str_real_len;

    *(uint32_t *)(ser) = bbp_eint32(BBP_LITTLE, n32);
    memcpy(ser + 4, str, str_real_len);
    memset(ser + 4 + str_real_len, '\0', str_pad_len);
    if (bbp_host_endian() != BBP_LITTLE) {
        bbp_reverse(ser + 4, str_len);
    }
    *(uint16_t *)(ser + 4 + str_len) = bbp_eint16(BBP_LITTLE, n16);

    /* 8ba3f768466f6f4261720000000012ee */
    bbp_print_hex("ser", ser, sizeof(ser));

    return 0;
}
