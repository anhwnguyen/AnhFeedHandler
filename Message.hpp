#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <cstring>
#include <sstream>
#include <iostream>
#include "utility.hpp"

class Message{
public:
    Message() = default;
    Message(const char& type,const ID &id, const Time &timestamp);

    void SetMessageType(const char &type);
    void SetID(const ID &currentID);
    void SetTimestamp(const Time &timestamp);
    void SetSide(const Side &side);
    void SetPrice(const Price &price);
    void SetRemainingSize(const Size &size);
    void SetCancelSize(const Size &size);
    void SetOrderExecutedSize(const Size &size);
    void SetOriginalID(const ID &id);
    void SetOriginalPrice(const Price &price);
    void SetOriginalSize(const Size &price);
    void SetMPID(const char &MPID);

    char GetMessageType() const;
    ID GetID() const;
    Time GetTimestamp() const;
    Side GetOrderSide() const;
    Price GetPrice() const;
    Size GetRemainingSize() const;
    Size GetOrderCancelSize() const;
    Size GetOrderExecutedSize() const;
    ID GetOriginalID() const;
    Price GetOriginalPrice() const;
    Size GetOriginalSize() const;
    const char *GetMPID() const;

    bool Empty() const;
    std::string BuildString() const;

private:
    char    m_Type              = 0;
    ID      m_ID                = d_InvalidID;
    Time    m_Timestamp         = 0;
    Side    m_Side              = d_InvalidSide;
    Price   m_Price             = d_InvalidPrice;
    Size    m_RemainingSize     = d_InvalidSize;
    Size    m_OrderCancelSize   = d_InvalidSize;
    Size    m_OrderExecuteSize  = d_InvalidSize;
    ID      m_OriginalID        = d_InvalidID;
    Price   m_OriginalPrice     = d_InvalidPrice;
    Size    m_OriginalSize      = d_InvalidSize;
    char    m_MPID[5]           = "";
};


#endif
