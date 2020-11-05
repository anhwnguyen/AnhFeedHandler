#ifndef WRITER_H_
#define WRITER_H_

#include <iostream>
#include <string>
#include <fstream>

class FeedWriter
{
public:
    FeedWriter() = default;
    FeedWriter(const std::string& fileName);
    ~FeedWriter();

    void WriteOutputString(const std::string & parsedString);
    std::string GetOutputFileName() const;
private:
    std::string     m_OutputFileName;
    std::ofstream   m_OutputFile;
};

#endif
