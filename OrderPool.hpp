#ifndef _ORDERPOOL_H_
#define _ORDERPOOL_H_

#include <unordered_map>
#include "Order.hpp"
#include "utility.hpp"

class OrderPool
{
public:
    OrderPool() = default;
    Order SearchOrderInPool(ID referenceNumber);
    void AddOrderToPool(ID referenceNumber, bool side, Size size, Price price, const char *MPID);
    void ModifyOrderInPool(ID referenceNumber, Size size = 0);
    bool Empty() const;
private:
    std::unordered_map<ID, Order> m_OrderPool;
};

#endif
