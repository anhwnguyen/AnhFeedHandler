#ifndef READER_H_
#define READER_H_

#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <inttypes.h>
#include <cstring>
#include "Message.hpp"

class FeedReader
{
public:
    FeedReader(const std::string &fileName, const std::string &ticker);
    FeedReader(const std::string &_stock);
    virtual ~FeedReader();

    Message ParseMessage();
    bool FinishedReading();
    void Progress();
    std::string GetInputFileName() const;
private:
    std::string     m_InputFileName;
    std::ifstream   m_InputFile;
    std::string     m_Ticker;
    char            m_Message[64];
    unsigned        count = 0;
    time_t          start;
};

#endif
