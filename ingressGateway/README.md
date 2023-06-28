# Gateway
This provides the tools to query financial data from yahoo-finance. <br>

This gateway is part of the trading system where ingest data from exchanges
into our system. It is primarily used to update our OrderBook, which 
would then generate signals for our Strategy Service to execute orders. 

Areas of improvements are listed below. 


## Some definitions beforehand

### What is Spot
Spot is similar to a OHLC Chart (Open High Low Close) chart

Spot consists of: 
1. date
2. open - price of stock during market opening hours
3. high - highest price over the day
4. low - lowest price over the day
5. close - price of stock during market closing hours


### What is Quote
Quote contains of a std::string, symbol, which represents the stock symbol, or ticker. 
<br>
For example Apple stocks is: AAPL, EURUSD=X, more examples can be found here (https://finance.yahoo.com/lookup/)

## Code Repo Structure
```
├── CMakeLists.txt
├── Quote.cpp
├── Quote.hpp
├── README.md
├── Spot.cpp
├── Spot.hpp
├── main.cpp
└── utils
    ├── curl_utils.cpp
    ├── curl_utils.hpp
    ├── time_utils.cpp
    └── time_utils.hpp
```
### Utils folder
utils contains mainly the:
1. curl_utils : Used to send a curl request over to yahoo finance
2. time_utils : Used to convert date to and from epoch time, which is the format needed for yahoo's API

### main.cpp
To get a quote price, we would first create a Quote. 
```
Quote *appleQuote = new Quote("AAPL");
appleQuote->getHistoricalSpots("2023-05-01", "2023-05-09", "1d");
appleQuote->printSpots();

Output:
{ date: 2023-05-01 open: 169.28 high: 170.45 low: 168.64 close: 169.59 }
{ date: 2023-05-02 open: 170.09 high: 170.35 low: 167.54 close: 168.54 }
{ date: 2023-05-03 open: 169.5 high: 170.92 low: 167.16 close: 167.45 }
{ date: 2023-05-04 open: 164.89 high: 167.04 low: 164.31 close: 165.79 }
{ date: 2023-05-05 open: 170.98 high: 174.3 low: 170.76 close: 173.57 }
{ date: 2023-05-08 open: 172.48 high: 173.85 low: 172.11 close: 173.5 }
```

It is also possible to get a specific spot from the above list:
```
Spot spot = appleQuote->getSpot("2023-05-02");
spot.printSpot();

Output:
{ date: 2023-05-02 open: 170.09 high: 170.35 low: 167.54 close: 168.54 }
```

## Area of Improvements

1. Tradtionally, there should be an In and Out Gateway, one for receiving price updates
and another for executing orders if the Strategy we are employing decides to. 

2. Currently this In Gateway only takes in in historical data, in order to get real time we would need to subscribe to an external company API that provides
access to real time data or receive updates from the Exchange directly.

3. Could upgrade to use UDP multicast to obtain market data feed, but for sending orders TCP is safer. (Ref: https://www.pico.net/kb/what-are-the-relative-merits-of-tcp-and-udp-in-high-frequency-trading/)

More explanation about UDP Multicast:

1. UDP is used over TCP at least for market updates because its more time sensitive
2. UDP multicast is used, similar to kafka pub/sub, but in a faster manner. 
3. IGMP is used to control multicast traffic forwarding on L2 domain. If the consumer and producer
are on the same switch, IGMP is sufficient. Consumer will need to send a IGMP Join to the switch listening to that
ip address: 123.1.2.3, and then the switch will only forward that to the consumer.
It will not send to all consumers.
When it leaves it will send a IGMP Leave or else, it will regularly send a IGMP membership query
to see if the consumer still requires updates. 
4. For this to work IGMP Snooping must be enabled, else it will multicast to everyone.
5. PIM is used to route multicast traffic between different subnets. 
6. IGMP is for Layer 2, PIM is for Layer 3. (Ref: https://www.wrsccie.com/post/multicast-igmp-and-pim-overview, https://www.youtube.com/watch?v=W5oMvrMRM3Q)
7. Take note: Layer 2 is data link layer and provides node-to-node transfer with MAC address identification
while Layer 3, network later rotues data packets to specific nodes identified by IP addresses. 
8. But since HFTs is usually co located in the Exchange's servers hence, dont really need PIM. Furthermore since only a handful of
consumer are able to be co located in the Exchange's server scalability is not a concern and layer 2 switch are sufficient. 



