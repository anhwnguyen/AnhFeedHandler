#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <climits>

typedef double      Price;
typedef long        Size;
typedef uint64_t    ID;
typedef long long   Time;
typedef bool        Side;

extern ID       d_InvalidID;
extern Side     d_InvalidSide;
extern Size     d_InvalidSize;
extern Price    d_InvalidPrice;


uint16_t bswap_16(uint16_t value);
uint32_t bswap_32(uint32_t value);
uint64_t bswap_64(uint64_t value);

uint16_t ConvertToUINT16(char * a);
uint32_t ConvertToUINT32(char * a);
uint64_t ConvertToUINT64(char * a);

uint64_t ParseTimestamp(char * a);

#endif
