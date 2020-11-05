#include "FeedWriter.hpp"

FeedWriter::FeedWriter(const std::string& fileName) : m_OutputFileName(fileName)
{
    m_OutputFile.open(fileName);
    if(!m_OutputFile.is_open()){
        std::cerr << "Invalid File: " << m_OutputFileName << std::endl;
    }
}

void FeedWriter::WriteOutputString(const std::string &parsedString)
{
    m_OutputFile << parsedString;
}

FeedWriter::~FeedWriter()
{
    if (m_OutputFile.is_open())
    {
        m_OutputFile.flush();
        m_OutputFile.close();
    }
}

std::string FeedWriter::GetOutputFileName() const
{
    return m_OutputFileName;
}