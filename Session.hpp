#ifndef BOOKCONSTRUCTOR_H_
#define BOOKCONSTRUCTOR_H_

#include "Message.hpp"
#include "Order.hpp"
#include "OrderPool.hpp"
#include "OrderBook.hpp"
#include "FeedReader.hpp"
#include "FeedWriter.hpp"


class Session
{
public:
    Session(const std::string &inputMessageFile,
                    const std::string &outputMessageFile,
                    const std::string &outputBookFile,
                    const std::string &_stock,
                    const size_t &_levels);
    ~Session();
    void Process();
    void OnReceive();
    bool UpdateMessage();
    void UpdateBook();
    void UpdatePool();
    void WriteBookAndMessage();
private:
    Message m_Message;
    OrderBook m_OrderBook;
    OrderPool m_OrderPool;
    FeedReader m_MessageFeedReader;
    FeedWriter m_MessageFeedWriter;
    FeedWriter m_OrderBookWriter;
    size_t m_PriceLevels;
};

#endif
