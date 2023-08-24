# Fix Parser
FIX parser is a method to decode FIX information <br>

It is crucial for proprietary trading system to have their own Order Books (OB) but in order
to ensure that their OB are updated. To do that, trading systems must receive updates from
exchanges such as Nasdaq, NYSE, etc for the latest price information, BID, ASKS. 

FIX is one of the most commonly used formats in the realm as it is lightweight, concise and thus fast. 

An example of a FIX message is:
```
8=FIX.4.2|9=123|35=D|49=XYZ|56=ABC|34=12|52=20220409-10:00:00|11=12345|55=AAPL|54=1|38=100|40=1|44=150|10=123|
```

This is unreadable and difficult to comprehend to a normal trader, so we would need to parse it (decode it)
and using the decode information we can update the OB, to generate signals. 


## Some definitions beforehand

### Explanation of the format
FIX basically consist of multiple key-value pairs. Keys are pre defined such that it will never change and this can be
found on the FIX information (https://www.onixs.biz/fix-dictionary/4.2/fields_by_tag.html)

Then the value is the information we want to pass. 

### Breaking down the example above
1. 8 == FIX4.2 -> states the version of FIX
2. 9 == 123 -> Count how many tags starting from tag 35, basically after this 9. Tells us how many key-value pairs to expect
3. 35 == D -> We are making a SINGLE ORDER type
4. 49 , 56 is the sender and receiver's ID
5. 34 = 12 -> FIX message start with a sequence num of 1, will increment. Next should be expecting 13
6. 55 = AAPL -> which stock you want to buy
7. For the full list, we would need to refer to the link above. 

### Further explanation
Using the Keys we can find out what kind of order message it is going to be, and then there would be keys further down
the message to provide more information about this order message. 

To parse is properly, we would probably use if-else statements

## Code Repo Structure
```
├── CMakeLists.txt
├── fixParser.cpp
├── fixParser_main.hpp
├── README.md
```

### fixParser.cpp
Each FIX message is a string, and key value are separated by \t

Pass string into parser.parse -> then call private function to splitFixMessage

```
std::vector<std::string> splitFixMessage(const std::string& fixMessage) {
  // Split the FIX message by delimiter (usually '\t') and return a vector of tags.
  // You can implement your own split function or use libraries like Boost or std::regex.
  std::vector<std::string> tags; 
  // ... Implement your splitting logic here ...
  std::stringstream ss(fixMessage);
  std::string tag;
  while (std::getline(ss, tag, SOH)) {
      std::cout << tag <<'\n';
      tags.push_back(tag);
  }
  return tags;
}
```

This method will give us a tags vector: [8=FIX, 1=Value1, ...], keys and value together in 1 index of the vector

Take note of the vector `tags` we use above, will discuss more in detail later. 


### fixParser_main.cpp

If we look at the parsing logic, the slowest or portion we need to optimize the most is
the `spliting logic` and the portion where we use `tags` as mentioned before.

To optimize that:
1. Reuse the same vector to store the key,value pairs. This way we do not have to dynamically allocate a vector each 
time we call the method. This helped to reduce splitting logic by up to 50%

2. Boost library has a string split function, however it appeared slower than `find_first_of`




