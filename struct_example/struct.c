#include <stdio.h>
#include <stdint.h>

union t64 {
        uint64_t rax;
        struct u64_32{
            uint32_t none;
            union t32{
                uint32_t eax;
                struct u32_16{
                    uint16_t none;
                    union t16{
                        uint16_t ax;
                        struct u16_8{
                            uint8_t ah;
                            uint8_t al;
                        } u16_8;
                    } t16;
                } u32_16;
            } t32;
        } u64_32;
    } t64;

int main(void)
{
    t64.u64_32.t32.u32_16.t16.u16_8.ah = 255;
    

    return 0;
}