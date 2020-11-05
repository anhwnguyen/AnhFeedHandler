#include "OrderBook.hpp"

std::string OrderBook::BuildStringFromOrderBookEntry(const size_t &level) const 
{
    size_t buySideDepth = m_BuySide.size();
    size_t sellSideDepth = m_SellSide.size();
    std::ostringstream ss;
    ss << m_Timestamp << ",";

    // The best bid price is the smallest entry
    std::map<Price, Size>::const_reverse_iterator buySideIterator = m_BuySide.rbegin();
    // The best ask price is the biggest entry
    std::map<Price, Size>::const_iterator sellSideIterator = m_SellSide.begin();

    for (unsigned i = 0; i < level; i++){
        if(i < buySideDepth){
            ss << buySideIterator->first << ","<< buySideIterator->second << ",";
            ++buySideIterator;
        }
        else {
            ss << ",,";
        }

        if (i < sellSideDepth){
            ss << sellSideIterator->first << "," << sellSideIterator->second << ",";
            ++sellSideIterator;
        }
        else{
            ss << ",,";
        }
    }

    ss.seekp(-1, std::ios_base::end);
    ss << std::endl;

    return ss.str();
}

void OrderBook::ModifyNumberOfShares(Price price, Size size, Side side)
{
    if (side) {
        m_SellSide[price] += size;
        if (m_SellSide[price] == 0) {
            m_SellSide.erase(price);
        }
    }
    else {
        m_BuySide[price] += size;
        if (m_BuySide[price] == 0) {
            m_BuySide.erase(price);
        }
    }
}

bool OrderBook::NoPendingUnmatchedBid()
{
    if (!m_BuySide.empty() && !m_SellSide.empty()) {
        return ((m_BuySide.rbegin()->first) <= (m_SellSide.begin()->first));
    }
    return true;
}

void OrderBook::SetTimestamp(const Time &time)
{
    m_Timestamp = time;
}
