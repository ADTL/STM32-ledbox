#include <stdlib.h>

// This algorithm is extracted for ISO/IEC 9899:TC2 
// It is portable but not so pseudo random
// TODO: look for another algorithm or maybe, offer a syscall entry
// Some MCU chip embed special peripheral for random number generation

static unsigned long int next = 1;
int frand(void) // RAND_MAX assumed to be 32767
{
        next = next * 1103515245 + 12345;
        return (unsigned int)(next/65536) % 32768;
}

void fsrand(unsigned int seed)
{
        next = seed;
} 
