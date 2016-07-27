#ifndef Hamming_7_4_h
#define Hamming_7_4_h
#include "stdint.h"

// the #include statment and code go here...
class Hamming_7_4
{
private:
    uint8_t encodeHalf(uint8_t data); // expands the low 4 bits to a Hamming byte, leaving space for corrector codes and
                                      // parity
    uint8_t decodeHalf(uint8_t data, uint8_t& corr); // decode data, return 0: fine, 1-8: fine with correction on bit,
                                                     // throw exception is unrecoverable
public:
    Hamming_7_4();
    uint16_t encode(uint8_t data); // encode data
    uint8_t decode(uint16_t data); // decode data, return decoded with error correction, throw exception if code is
                                   // unrecoverable
    uint8_t decode(uint16_t data, uint8_t& corr); // decode data, return decoded with error correction, throw exception
                                                  // if code is unrecoverable, corr carries the wrong bit
};
#endif