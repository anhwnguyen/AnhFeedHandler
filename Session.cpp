#include "Session.hpp"
#include "FeedReader.hpp"
#include "FeedWriter.hpp"

Session::Session(const std::string &inputMessageFile,
    const std::string &outputMessageFile,
    const std::string &outputBookFile,
    const std::string &ticker,
    const size_t &levels)
    :
    m_MessageFeedReader(inputMessageFile, ticker),
    m_MessageFeedWriter(outputMessageFile),
    m_OrderBookWriter(outputBookFile),
    m_PriceLevels(levels)
{
    m_MessageFeedWriter.WriteOutputString("Timestamp,MessageType,RefNumber,side,Share,Price,orderCancelSize,orderExecuteSize,OriginalRefNumber,OriginalSize,OriginalPrice,mpid\n");
    std::string orderBookHeader = "time,";
    for(size_t i = 1; i <= m_PriceLevels; i++){
        std::string currentLevel = std::to_string(i);
        orderBookHeader +=  currentLevel + "_bid_price," + 
                            currentLevel + "_bid_vol," +
                            currentLevel + "_ask_price," +
                            currentLevel + "_ask_vol,";
    }
    m_OrderBookWriter.WriteOutputString(orderBookHeader.substr(0, orderBookHeader.size() - 1)+'\n');
}

Session::~Session(){}

void Session::Process(void)
{
    while(!m_MessageFeedReader.FinishedReading()){
        OnReceive();
    }
}

void Session::OnReceive()
{
    m_Message = m_MessageFeedReader.ParseMessage();
    if(!m_Message.Empty()){
        bool validMessage = UpdateMessage();
        if(validMessage){
            UpdatePool();
            UpdateBook();
            WriteBookAndMessage();
        }
    }
}

bool Session::UpdateMessage(void)
{
    char messageType = m_Message.GetMessageType();

    if(messageType == 'A' || messageType == 'P' || messageType == 'F'){
        return true;
    }

    ID orderRefNumber = (messageType == 'U') ? m_Message.GetOriginalID() : m_Message.GetID();

    Order matchedOrder = m_OrderPool.SearchOrderInPool(orderRefNumber);
    if(matchedOrder.Empty()){
        return false;
    }

    m_Message.SetMPID(*(matchedOrder.GetMPID()));
    m_Message.SetSide(matchedOrder.GetOrderSide());

    if(messageType == 'D' || messageType == 'X'){
        if (m_Message.GetOrderCancelSize() == d_InvalidSize) {
            m_Message.SetCancelSize(matchedOrder.GetOrderSize());
        }

        Size remainingSize = matchedOrder.GetOrderSize() - m_Message.GetOrderCancelSize();
        m_Message.SetRemainingSize(remainingSize);
        m_Message.SetPrice(matchedOrder.GetOrderPrice());
    }

    else if(messageType == 'U') {
        m_Message.SetOriginalSize(matchedOrder.GetOrderSize());
        m_Message.SetOriginalPrice(matchedOrder.GetOrderPrice());
    }

    else if(messageType == 'E') {
        m_Message.SetPrice(matchedOrder.GetOrderPrice());
        Size remainingSize = matchedOrder.GetOrderSize() - m_Message.GetOrderExecutedSize();
        m_Message.SetRemainingSize(remainingSize);
    }

    else if(messageType == 'C') {
        Size remainingSize = matchedOrder.GetOrderSize() - m_Message.GetOrderExecutedSize();
        m_Message.SetRemainingSize(remainingSize);
        m_Message.SetOriginalPrice(matchedOrder.GetOrderPrice());
    }

    else{
        std::cerr << "Invalid Type: " << messageType << std::endl;
        return false;
    }
    return true;
}

void Session::UpdateBook(void)
{
    m_OrderBook.SetTimestamp(m_Message.GetTimestamp());
    auto messageType = m_Message.GetMessageType();
    auto orderSide = m_Message.GetOrderSide();

    switch (messageType) {
        case 'A':
        case 'F':
            m_OrderBook.ModifyNumberOfShares(m_Message.GetPrice(),m_Message.GetRemainingSize(), orderSide);
            break;
        case 'U':
            // TODO: OPTIMIZE
            m_OrderBook.ModifyNumberOfShares(m_Message.GetOriginalPrice(),-m_Message.GetOriginalSize(), orderSide);
            m_OrderBook.ModifyNumberOfShares(m_Message.GetPrice(),m_Message.GetRemainingSize(), orderSide);
            break;
        case 'D':
        case 'X':
            m_OrderBook.ModifyNumberOfShares(m_Message.GetPrice(),-m_Message.GetOrderCancelSize(), orderSide);
            break;
        case 'E':
            m_OrderBook.ModifyNumberOfShares(m_Message.GetPrice(),-m_Message.GetOrderExecutedSize(), orderSide);
            break;
        case 'C':
            m_OrderBook.ModifyNumberOfShares(m_Message.GetOriginalPrice(),-m_Message.GetOrderExecutedSize(), orderSide);
            break;
        case 'P':
            break;
        default:
            std::cerr << "Invalid Type: " << messageType << std::endl;
            break;
    }

    if(!m_OrderBook.NoPendingUnmatchedBid()){
        std::cerr << "Pending order found." << std::endl;
    }
}

void Session::UpdatePool(void)
{
    char messageType = m_Message.GetMessageType();

    switch (messageType) {
        case 'A':
        case 'F':
            m_OrderPool.AddOrderToPool(m_Message.GetID(), m_Message.GetOrderSide(), m_Message.GetRemainingSize(), m_Message.GetPrice(), m_Message.GetMPID());
            break;
        case 'U':
            m_OrderPool.ModifyOrderInPool(m_Message.GetOriginalID(), m_Message.GetOriginalSize());
            m_OrderPool.AddOrderToPool(m_Message.GetID(), m_Message.GetOrderSide(), m_Message.GetRemainingSize(), m_Message.GetPrice(), m_Message.GetMPID());
            break;
        case 'D':
        case 'X':
            m_OrderPool.ModifyOrderInPool(m_Message.GetID(), m_Message.GetOrderCancelSize());
            break;
        case 'E':
        case 'C':
            m_OrderPool.ModifyOrderInPool(m_Message.GetID(), m_Message.GetOrderExecutedSize());
            break;
        case 'P':
            break;
        default:
            std::cerr << "Invalid type: " << messageType << std::endl;
            break;
    }
}

void Session::WriteBookAndMessage(void){
    m_OrderBookWriter.WriteOutputString(m_OrderBook.GetString(m_PriceLevels));
    m_MessageFeedWriter.WriteOutputString(m_Message.GetString());
}
