#include <stdio.h>
#include <x86intrin.h>

int main() {
    unsigned int ui;
    // Capture start cycles
    // __rdtscp returns the 64-bit cycle count and writes the CPU ID to &ui
    unsigned long long start = __rdtscp(&ui);

    /* --- Code to measure starts --- */
    //for (int i = 0; i < 1000000; i++); 
    /* --- Code to measure ends --- */

    // Capture end cycles
    unsigned long long end = __rdtscp(&ui);

    printf("Total cycles: %llu %llu\n", end,start);
    return 0;
}