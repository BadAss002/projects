//стандартная crc просто как по закону блять, все идеально, но медленно
#include <stdint.h>
#include <stddef.h>

#define const_poly 0x04C11DB7u

static uint8_t reverse8(uint8_t byte)
{
    uint8_t result = 0;

    for (int i = 0; i < 8; i++)
    {
        result <<= 1;
        result |= (byte & 1u);
        byte >>= 1;
    }

    return result;
}

static uint32_t reverse32(uint32_t value)
{
    uint32_t result = 0;

    for (int i = 0; i < 32; i++)
    {
        result <<= 1;
        result |= (value & 1u);
        value >>= 1;
    }

    return result;
}

uint32_t crc32(const unsigned char *text, size_t current_length)
{
    uint32_t crc = 0xFFFFFFFFu;

    for (size_t i = 0; i < current_length; i++)
    {
        crc ^= ((uint32_t)reverse8(text[i]) << 24);

        for (int j = 0; j < 8; j++)
        {
            if (crc & 0x80000000u)
                crc = (crc << 1) ^ const_poly;
            else
                crc <<= 1;
        }
    }

    return reverse32(crc) ^ 0xFFFFFFFFu;
}
