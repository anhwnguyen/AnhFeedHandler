#include "Order.hpp"

Order::Order(ID referenceNumber, bool side, Size size, Price price, const char *MPID):
        m_OrderReferenceNumber(referenceNumber), m_OrderSide(side), m_OrderSize(size), m_OrderPrice(price) 
{
    strncpy(m_MPID, MPID, 4); 
    m_MPID[4] = 0;
}

ID Order::GetOrderReferenceNumber() const
{
    return m_OrderReferenceNumber;
}

bool Order::GetOrderSide() const
{
    return m_OrderSide;
}

Size Order::GetOrderSize() const
{
    return m_OrderSize;
}

Price Order::GetOrderPrice() const
{
    return m_OrderPrice;
}

const char * Order::GetMPID()const
{
    return m_MPID;
}

void Order::AddSize(Size size)
{
    m_OrderSize += size;

    if(m_OrderSize < 0) {
        std::cerr << "Invalid Updated Order Size." << std::endl;
    }
}

bool Order::Empty() const
{
    return (m_OrderReferenceNumber == d_InvalidID);
}
