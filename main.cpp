#include <stdio.h>
#include "Hamming_7_4.h"

int main(int argc, char** argv)
{
    Hamming_7_4* ham = new Hamming_7_4();

    printf("\nEncoding...\n");
    uint8_t dataIn = 0x2F;
    uint16_t hamming = ham->encode(dataIn);
    printf("dataIn: %x, Hamming: %x\n", dataIn, hamming);

    printf("\nDecoding...\n");

    uint8_t corr = 0x00;
    uint8_t dataOut = ham->decode(hamming, corr);
    printf("Hamming: %x, dataOut: %x, corr:%x\n", hamming, dataOut, corr);

    printf("\nDecoding with Err...\n");
    uint8_t err = 0x40;
    dataOut = ham->decode(hamming ^ err, corr);
    printf("Hamming^%x: %x, dataOut: %x, corr:%x\n", err, hamming ^ err, dataOut, corr);

    return 0;
}
