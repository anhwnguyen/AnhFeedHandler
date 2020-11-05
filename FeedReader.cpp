#include "FeedWriter.hpp"
#include "FeedReader.hpp"

FeedReader::FeedReader(const std::string &inputFileName, const std::string &ticker) : m_InputFileName(inputFileName), m_Ticker(ticker)
{
    m_InputFile.open(m_InputFileName);
    if(!m_InputFile.is_open()) {
        std::cout << "Invalid input: " << m_InputFileName << std::endl;
        return;
    }
    start = time(0);
}

FeedReader::FeedReader(const std::string &ticker): m_Ticker(ticker){}

void FeedReader::Progress(){
    count ++;
    if(count % 10000000 == 0) {
        std::cout << "Messages Processed: " << count / 1000000 << "Million /423 Million. Speed: " << count/difftime(time(0), start) / 1000000 << " million messages/s." << std::endl;
    }
}

Message FeedReader::ParseMessage()
{
    Progress();
    Message currentMessage;

    // First 2 bytes are junk? 0C00 
    // TODO: Check if this is correct?
    m_InputFile.ignore(2);
    
    char messageType;
    m_InputFile.get(messageType);

    char currentTicker[9];
    strncpy(currentTicker,  m_Ticker.c_str(), 8); 
    currentTicker[8] = 0;

    switch(messageType){
        uint64_t timeStamp, orderId, originalOrderID, newOrderID;
        uint32_t size, price, orderExecuteSize, orderCancelSize, newSize, newPrice;
        char side;
        char mpid[5];

        case 'S':
            m_InputFile.read(m_Message, 11);
            break;
        case 'R':
            m_InputFile.read(m_Message, 38);
            break;
        case 'H':
            m_InputFile.read(m_Message, 24);
            break;
        case 'Y':
            m_InputFile.read(m_Message, 19);
            break;
        case 'L':
            m_InputFile.read(m_Message, 25);
            break;
        case 'V':
            m_InputFile.read(m_Message, 34);
            break;
        case 'W':
            m_InputFile.read(m_Message, 11);
            break;
        case 'K':
            m_InputFile.read(m_Message, 27);
            break;
        case 'J':
            m_InputFile.read(m_Message, 34);
            break;
        case 'h':
            m_InputFile.read(m_Message, 20);
            break;
        case 'A':
            m_InputFile.read(m_Message, 35);
            timeStamp = ParseTimestamp(m_Message + 4);
            orderId = ConvertToUINT64(m_Message + 10);
            side = m_Message[18];
            size = ConvertToUINT32(m_Message + 19);
            strncpy(currentTicker,  m_Message + 23, 8); currentTicker[8] = 0;
            price = ConvertToUINT32(m_Message + 31);
            
            currentMessage.SetMessageType(messageType);
            currentMessage.SetTimestamp(static_cast<Time>(timeStamp));
            currentMessage.SetID(static_cast<ID>(orderId));
            currentMessage.SetSide(static_cast<Side>(side == 'S'));
            currentMessage.SetRemainingSize(static_cast<Size>(size));
            currentMessage.SetPrice(static_cast<Price>(price)/10000);
            break;
        case 'F':
            m_InputFile.read(m_Message, 39);

            timeStamp = ParseTimestamp(m_Message + 4);
            orderId = ConvertToUINT64(m_Message + 10);
            side = m_Message[18];
            size = ConvertToUINT32(m_Message + 19);
            strncpy(currentTicker,  m_Message + 23, 8); 
            currentTicker[8] = 0;
            price = ConvertToUINT32(m_Message + 31);
            
            strncpy(mpid, m_Message + 35, 4); 
            mpid[4] = 0;
            
            currentMessage.SetMessageType(messageType);
            currentMessage.SetTimestamp(static_cast<Time>(timeStamp));
            currentMessage.SetID(static_cast<ID>(orderId));
            currentMessage.SetSide(static_cast<Side>(side == 'S'));
            currentMessage.SetRemainingSize(static_cast<Size>(size));
            currentMessage.SetPrice(static_cast<Price>(price)/10000);
            currentMessage.SetMPID(*mpid);
            break;
        case 'E':
            m_InputFile.read(m_Message, 30);
            timeStamp = ParseTimestamp(m_Message + 4);
            orderId = ConvertToUINT64(m_Message + 10);
            orderExecuteSize = ConvertToUINT32(m_Message + 18);

            currentMessage.SetMessageType(messageType);
            currentMessage.SetTimestamp(static_cast<Time>(timeStamp));
            currentMessage.SetID(static_cast<ID>(orderId));
            currentMessage.SetOrderExecutedSize(static_cast<Size>(orderExecuteSize));
            break;
        case 'C':
            m_InputFile.read(m_Message, 35);
            timeStamp = ParseTimestamp(m_Message + 4);
            orderId = ConvertToUINT64(m_Message + 10);
            orderExecuteSize = ConvertToUINT32(m_Message + 18);
            price = ConvertToUINT32(m_Message + 31);
            
            currentMessage.SetMessageType(messageType);
            currentMessage.SetTimestamp(static_cast<Time>(timeStamp));
            currentMessage.SetID(static_cast<ID>(orderId));
            currentMessage.SetOrderExecutedSize(static_cast<Size>(orderExecuteSize));
            currentMessage.SetPrice(static_cast<Price>(price)/10000);
            break;
        case 'X':
            m_InputFile.read(m_Message, 22);
            timeStamp = ParseTimestamp(m_Message + 4);
            orderId = ConvertToUINT64(m_Message + 10);
            orderCancelSize = ConvertToUINT32(m_Message + 18);
            
            currentMessage.SetMessageType(messageType);
            currentMessage.SetTimestamp(static_cast<Time>(timeStamp));
            currentMessage.SetID(static_cast<ID>(orderId));
            currentMessage.SetCancelSize(static_cast<Size>(orderCancelSize));
            break;
        case 'D':
            m_InputFile.read(m_Message, 18);
            timeStamp = ParseTimestamp(m_Message + 4);
            orderId = ConvertToUINT64(m_Message + 10);
            
            currentMessage.SetMessageType(messageType);
            currentMessage.SetTimestamp(static_cast<Time>(timeStamp));
            currentMessage.SetID(static_cast<ID>(orderId));
            break;
        case 'U':
            m_InputFile.read(m_Message, 34);
            timeStamp = ParseTimestamp(m_Message + 4);
            originalOrderID = ConvertToUINT64(m_Message + 10);
            newOrderID = ConvertToUINT64(m_Message + 18);
            newSize = ConvertToUINT32(m_Message + 26);
            newPrice = ConvertToUINT32(m_Message + 30);
            
            currentMessage.SetMessageType(messageType);
            currentMessage.SetTimestamp(static_cast<Time>(timeStamp));
            currentMessage.SetID(static_cast<ID>(newOrderID));
            currentMessage.SetOriginalID(static_cast<ID>(originalOrderID));
            currentMessage.SetRemainingSize(static_cast<Size>(newSize));
            currentMessage.SetPrice(static_cast<Price>(newPrice)/10000);
            break;
        case 'P':
            m_InputFile.read(m_Message, 43);
            timeStamp = ParseTimestamp(m_Message + 4);
            orderId = ConvertToUINT64(m_Message + 10);
            side = m_Message[18];
            size = ConvertToUINT32(m_Message + 19);
            strncpy(currentTicker,  m_Message + 23, 8); currentTicker[8] = 0;
            price = ConvertToUINT32(m_Message + 31);
            
            currentMessage.SetMessageType(messageType);
            currentMessage.SetTimestamp(static_cast<Time>(timeStamp));
            currentMessage.SetID(static_cast<ID>(orderId));
            currentMessage.SetSide(static_cast<Side>(side == 'S'));
            currentMessage.SetOrderExecutedSize(static_cast<Size>(size));
            currentMessage.SetPrice(static_cast<Price>(price)/10000);
            break;
        case 'Q':
            m_InputFile.read(m_Message, 39);
            break;
        case 'B':
            m_InputFile.read(m_Message, 18);
            break;
        case 'I':
            m_InputFile.read(m_Message, 49);
            break;
        case 'N':
            m_InputFile.read(m_Message, 19);
            break;
        default:
            if(!FinishedReading()){
                std::cerr << "Invalid Type: " << messageType << std::endl;
            }
            break;
    }

    if(0 != strcmp(currentTicker, m_Ticker.c_str())){
        // let's just read 1 ticker for now otherwise we would go pretty crazy.
        return Message();
    }
    return currentMessage;
}

bool FeedReader::FinishedReading()
{
    return m_InputFile.eof();
}

FeedReader::~FeedReader()
{
    if (m_InputFile.is_open()){
        m_InputFile.close();
        std::cout << "Total messages processed: " << count << std::endl;
        std::cout << "Time processed: " << difftime(time(0), start) << "seconds."  << std::endl;
    }
}
