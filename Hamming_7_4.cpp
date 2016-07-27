
/*
  Hamming_7_4.cpp - Library for computing Hamming[7,4] encoding.
  Created by Davide Imperati, July 25, 2016.
  Released into the public domain.
*/

#include "Hamming_7_4.h"
#include <stdio.h>

static const bool ParityTable256[256] = {
#define P2(n) n, n ^ 1, n ^ 1, n
#define P4(n) P2(n), P2(n ^ 1), P2(n ^ 1), P2(n)
#define P6(n) P4(n), P4(n ^ 1), P4(n ^ 1), P4(n)
    P6(0), P6(1), P6(1), P6(0)
};

static const uint8_t Mask8[8] = { 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40 };

Hamming_7_4::Hamming_7_4()
{
}

uint16_t Hamming_7_4::encode(uint8_t data)
{
    uint16_t res = 0;

    res = encodeHalf((data >> 4) & 0X0f);
    res <<= 8;
    res |= encodeHalf(data & 0X0f);
    return res;
}

uint8_t Hamming_7_4::encodeHalf(uint8_t data)
{
    // pow: 128, 64, 32, 16, 8, 4, 2, 1
    // bit:   7,  6,  5,  4, 3, 2, 1, 0
    // fun:   p,  3,  2,  1, c, 0, c, c
    // p: partity, c: correction code, #: bit position

    // prepare data
    uint8_t res = 0x00;
    uint8_t work = data & 0X0f;
    work <<= 2;
    res |= work & 0x04;
    work <<= 1;
    res |= work & 0x70;

    printf("res:%d, %x\n", res, res);

    // bit masks for
    //		MASK1 = 0x55; // 0101 0101 // Contains 2^0
    //		MASK2 = 0x66; // 0110 0110 // Contains 2^1
    //		MASK4 = 0x78; // 0111 1000 // Contains 2^2

    work = ParityTable256[res & 0x55];
    printf("work:%d, %x\n", work, work);
    res |= work;

    work = ParityTable256[res & 0x66];
    printf("work:%d, %x, %x\n", work, work, work << 1);
    res |= (work << 1);

    work = ParityTable256[res & 0x78];
    printf("work:%d, %x, %x\n", work, work, work << 3);
    res |= (work << 3);

    work = ParityTable256[res];
    res |= (work << 7);

    return res;
}

uint8_t Hamming_7_4::decode(uint16_t data)
{
    uint8_t corr;
    return decode(data, corr);
}

uint8_t Hamming_7_4::decode(uint16_t data, uint8_t& corr)
{
    uint8_t res;
    res = decodeHalf((data >> 8) & 0xFF, corr) << 4;
    corr <<= 4;
    res |= decodeHalf(data & 0xFF, corr);
    return res;
}

uint8_t Hamming_7_4::decodeHalf(const uint8_t data, uint8_t& corr)
{
    uint8_t res = 0x00;
    uint8_t parity = 0x00;

    corr |= (ParityTable256[data & 0x55]) & 0x0F;
    corr |= (ParityTable256[data & 0x66] << 1) & 0x0F;
    corr |= (ParityTable256[data & 0x78] << 2) & 0x0F;

    parity = ParityTable256[data];

    if (((parity == 0) && (corr != 0)) || ((parity != 0) && (corr == 0))) {
	//			/throw exception
    }
    uint8_t err = Mask8[corr];
    res = ((data ^ err) >> 2) & 0x01;
    printf("data: %x, data_corr: %x, parity: %x, corr: %x, res: %x\n", data, data ^ err, parity, corr, res);
    res |= ((data ^ err) >> 3) & 0x0E;
    printf("data: %x, parity: %x, corr: %x, err: %X, res: %x\n", data, parity, corr, err, res);

    return res;
}
