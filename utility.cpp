#include "utility.hpp"

Side d_InvalidSide = 0;
ID d_InvalidID = LLONG_MAX;
Price d_InvalidPrice = -1;
Size d_InvalidSize = -1;

uint16_t bswap_16(uint16_t value)
{
    return static_cast<uint16_t>(((value) & 0xff) << 8 | ((value) >> 8));
}

uint32_t bswap_32(uint32_t value)
{
    return ((static_cast<uint32_t>(bswap_16(static_cast<uint16_t>((value) & 0xffff))) << 16) |
    static_cast<uint32_t>(bswap_16(static_cast<uint16_t>((value) >> 16))));
}

uint64_t bswap_64(uint64_t value)
{
    return ((static_cast<uint64_t>(bswap_32(static_cast<uint32_t>((value) & 0xffffffff))) << 32) |
    static_cast<uint64_t>(bswap_32(static_cast<uint32_t>((value) >> 32))));
}

uint16_t ConvertToUINT16(char * a)
{
    return bswap_16(*(reinterpret_cast<uint16_t *>(a)));
}

uint32_t ConvertToUINT32(char * a)
{
    return bswap_32(*(reinterpret_cast<uint32_t *>(a)));
}

uint64_t ConvertToUINT64(char * a)
{
    return bswap_64(*(reinterpret_cast<uint64_t *>(a)));
}

uint64_t ParseTimestamp(char * a)
{
    return (((static_cast<uint64_t>(bswap_16(*(reinterpret_cast<uint16_t *>(a))))) << 32) |
    static_cast<uint64_t>(bswap_32(*(reinterpret_cast<uint32_t *>(a+2)))));
}
