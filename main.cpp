#include <iostream>
#include <string>
#include "Session.hpp"

int main(int argc, char * argv[])
{
    if(argc<3){
        std::cerr << "./Anh input numberOfLevels Ticker" << std::endl;
        return 1;
    }

    std::string inputFile               = argv[1];
    size_t      levels                  = std::stoul(argv[2]);
    std::string stock                   = argv[3];
    std::string nameFile                = "01302020.NASDAQ_ITCH50";
    std::string outputOrderBookFileName = "./" + stock + std::to_string(levels) + "_book.csv";
    std::string outputMessageFileName   = "./" + stock + "_message.csv";
    std::string formattedStock          = stock;
    formattedStock.insert(formattedStock.end(), 8 - formattedStock.size(), ' ');

    std::cout << "Book: " << outputOrderBookFileName << std::endl;
    std::cout << "Message: " << outputMessageFileName << std::endl;

    Session Session(inputFile, outputMessageFileName, outputOrderBookFileName, formattedStock, levels);
    Session.Process();

    return 0;
}
