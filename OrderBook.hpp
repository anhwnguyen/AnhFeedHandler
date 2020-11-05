#ifndef _OrderBook_H_
#define _OrderBook_H_

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include "utility.hpp"

class OrderBook
{
public:
    OrderBook() = default;

    std::string BuildStringFromBookEntry(const size_t &string) const;
    void ModifyNumberOfShares(Price, Size, Side);
    void SetTimestamp(const Time &time);
    bool NoPendingUnmatchedBid();
private:
    Time m_Timestamp;
    std::map<Price, Size> m_BuySide;
    std::map<Price, Size> m_SellSide;

};


#endif
