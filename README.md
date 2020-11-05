To compile:
reset && clang++ -O3 -o anh main.cpp Message.cpp utility.cpp Session.cpp FeedReader.cpp FeedWriter.cpp Order.cpp OrderBook.cpp OrderPool.cpp -std=c++17 
To Run: 
./anh <Input File From NASDAQ> <number of Levels> <Ticker> E.g: 
./anh 01302020.NASDAQ_ITCH50 2 SPY
