#ifndef _ORDER_H_
#define _ORDER_H_

#include <iostream>
#include "utility.hpp"
#include "Message.hpp"

class Order
{
public:
    Order() = default;
    Order(ID referenceNumber, Side side, Size size, Price price, const char *mpid);

    void AddSize(Size size);

    ID GetOrderReferenceNumber() const;
    Side GetOrderSide() const;
    Size GetOrderSize() const;
    Price GetOrderPrice() const;
    const char * GetMPID() const;

    bool Empty() const;

private:
    ID      m_OrderReferenceNumber = d_InvalidID;
    Side    m_OrderSide;
    Size    m_OrderSize = d_InvalidSize;
    Price   m_OrderPrice = d_InvalidPrice;
    char    m_MPID[5] = "";

};

#endif
