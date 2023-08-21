//
// Created by Willy Seah on 7/8/23.
//
#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <vector>


class FixParser {
public:

    FixParser() {
        // Initialize the dictionary with known FIX tags and their corresponding names.
        // You may need to add more entries to this dictionary depending on your use case.
        dictOfTags = {
                {8,  "BeginString"},
                {35, "MsgType"},
                {49, "SenderCompID"},
                {55, "Symbol"},
                {22, "IdSource"},
                {1, "Account"},
                {48, "SecurityId"},


                // Add more tags here...
        };
    }

    void parse(const std::string& fixMessage) {
        //Split Fix messsage into individual tags
        std::vector<std::string> tags = splitFixMessage(fixMessage);

        for(const std::string& tag : tags) {
            int tagNum;
            std::string value;

            if (parseTag(tag, tagNum, value)) {
                std::string tagName = getTagName(tagNum);
                if (!tagName.empty()) {
                    std::cout << "Tag: " << tagName << ", Value: " << value << std::endl;
                    // Handle the parsed tag and value here as per your requirement.
                } else {
                    std::cout << "Unknown Tag: " << tagNum << ", Value: " << value << std::endl;
                    // Handle unknown tags if needed.
                }
            }

        }
    }

private:
    std::map<int, std::string> dictOfTags;

    #define SOH '\t'

    std::vector<std::string> splitFixMessage(const std::string& fixMessage) {
        // Split the FIX message by delimiter (usually '\x01') and return a vector of tags.
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

    bool parseTag(const std::string& tag, int& tagNum, std::string& value) {
        // Parse an individual tag (e.g., "35=D") and extract the tag number and value.
        // You can implement your own parsing logic here.
        // Return true if parsing is successful, false otherwise.
        // ...
        size_t equalsPos = tag.find('=');
        if (equalsPos == std::string::npos) { //npos means end position which means cannot find
            // Invalid tag format, no '=' found
            return false;
        }

        try {
            tagNum = std::stoi(tag.substr(0, equalsPos));
            value = tag.substr(equalsPos + 1);
        } catch (const std::exception& e) {
            // Failed to parse the tag number as an integer
            return false;
        }
        return true;
    }

    std::string getTagName(int tagNum) {
        // Get the name of the tag from the dictionary using its tag number.
        auto it = dictOfTags.find(tagNum);
        if (it != dictOfTags.end()) {
            return it->second;
        }
        return ""; // Return empty string for unknown tags.
    }


};


int main() {
    std::string fixMessage = "8=FIX.4.4\t1=VALUE1\t35=D\t10=VALUE2\t";

    FixParser parser;
    parser.parse(fixMessage);
    //parse -> splitFixMessage -> parseTag -> getTagName

    return 0;
}