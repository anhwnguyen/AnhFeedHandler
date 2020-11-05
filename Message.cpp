#include "Message.hpp"

Message::Message(const char& type, const ID& currentID, const Time& timestamp) :
        m_Type(type), m_ID(currentID), m_Timestamp(timestamp){};

void Message::SetMessageType(const char& type)
{
    switch (type) {
        case 'A':
        case 'F':
        case 'D':
        case 'X':
        case 'U':
        case 'E':
        case 'P':
        case 'C':
            m_Type = type;
            break;
        default:
            std::cerr << "Invalid Type: " << type << std::endl;
            return;
    }
}

void Message::SetID(const ID& currentID) 
{
    m_ID = currentID;
}

void Message::SetTimestamp(const Time& timestamp) 
{
    m_Timestamp = timestamp;
}

void Message::SetSide(const Side& side) 
{
    m_Side = side;
}

void Message::SetPrice(const Price& price) 
{
    m_Price = price;
}

void Message::SetRemainingSize(const Size& size) 
{
    m_RemainingSize = size;
}

void Message::SetCancelSize(const Size& size) 
{
    m_OrderCancelSize = size;
}

void Message::SetOrderExecutedSize(const Size& size) 
{
    m_OrderExecuteSize = size;
}

void Message::SetOriginalID(const ID& id) 
{
    m_OriginalID = id;
}

void Message::SetOriginalPrice(const Price& price) 
{
    m_OriginalPrice = price;
}

void Message::SetOriginalSize(const Size& size) 
{
    m_OriginalSize= size;
}

void Message::SetMPID(const char& mpid) 
{
    strncpy(m_MPID, &mpid, 4);
    m_MPID[4] = 0;
}

char Message::GetMessageType() const
{
    return m_Type;
}

ID Message::GetID() const
{
    return m_ID;
}

Time Message::GetTimestamp() const
{
    return m_Timestamp;
}

Side Message::GetOrderSide() const
{
    return m_Side;
}

Price Message::GetPrice() const
{
    return m_Price;
}

Size Message::GetRemainingSize() const 
{
    return m_RemainingSize;
}

Size Message::GetOrderCancelSize() const 
{
    return m_OrderCancelSize;
}

Size Message::GetOrderExecutedSize() const 
{
    return m_OrderExecuteSize;
}

ID Message::GetOriginalID() const 
{
    return m_OriginalID;
}

Price Message::GetOriginalPrice() const 
{
    return m_OriginalPrice;
}

Size Message::GetOriginalSize() const 
{
    return m_OriginalSize;
}

const char * Message::GetMPID() const 
{
    return m_MPID;
}

bool Message::Empty() const 
{
    return (m_ID == d_InvalidID);
}

std::string Message::BuildString() const 
{
    std::ostringstream ss;
    if(!Empty()) {
        ss << m_Timestamp << ",";
    }
    else{
        ss << ",";
    }

    if(!Empty()) {
        ss << m_Type  << "," << m_ID << "," << m_Side << ",";
    }
    else{
        ss << ",,,";
    }
    if(m_RemainingSize!=d_InvalidSize) {
        ss << m_RemainingSize;
    }
    ss << ",";

    if(m_Price!=d_InvalidPrice) {
        ss << m_Price;
    }
    ss << ",";

    if(m_OrderCancelSize!=d_InvalidSize) {
        ss << m_OrderCancelSize;
    }
    ss << ",";

    if(m_OrderExecuteSize!=d_InvalidSize) {
        ss << m_OrderExecuteSize;
    }
    ss << ",";

    if(m_OriginalID != d_InvalidID) {
        ss << m_OriginalID;
    }
    ss << ",";

    if(m_OriginalPrice != d_InvalidSize) {
        ss << m_OriginalPrice;
    }
    ss << ",";

    if(m_OriginalSize!=d_InvalidPrice) {
        ss << m_OriginalSize;
    }
    ss << ",";
    ss << m_MPID;
    ss << std::endl;

    return ss.str();
}