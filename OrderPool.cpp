#include "OrderPool.hpp"

Order OrderPool::SearchOrderInPool(ID referenceNumber)
{
    Order orderFound;
    auto it = m_OrderPool.find(referenceNumber);
    if (m_OrderPool.find(referenceNumber) != m_OrderPool.end()){
        orderFound = it->second;
    }
    return orderFound;
}

void OrderPool::AddOrderToPool(ID referenceNumber, bool side, Size size, Price price, const char *MPID)
{
    Order newOrder(referenceNumber, side, size, price, MPID);
    m_OrderPool[referenceNumber] = newOrder;
}

void OrderPool::ModifyOrderInPool(ID referenceNumber, Size size)
{
    m_OrderPool[referenceNumber].AddSize(-size);
    if (m_OrderPool[referenceNumber].GetOrderSize() == 0) {
        m_OrderPool.erase(referenceNumber);
    }
}

bool OrderPool::Empty() const
{
    return m_OrderPool.empty();
}