//
// Created by Willy Seah on 6/8/23.
//

#include <iostream>
#include <boost/algorithm/string.hpp>
#include <vector>

#define SOH "\x01"
#define TAB "\t"


void string_split_optim(std::vector<std::string>& output, const std::string &s, const char delimiter)
{
    output.clear();

    size_t start = 0;
    size_t end = s.find_first_of(delimiter);


    while (end <= std::string::npos)
    {
        output.emplace_back(s.substr(start, end - start));

        if (end == std::string::npos)
            break;

        start = end + 1;
        end = s.find_first_of(delimiter, start);
    }

}

std::vector<std::string> string_split(std::string s, const char delimiter)
{
    size_t start=0;
    size_t end=s.find_first_of(delimiter);

    std::vector<std::string> output;

    while (end <= std::string::npos)
    {
        output.emplace_back(s.substr(start, end-start));

        if (end == std::string::npos)
            break;

        start=end+1;
        end = s.find_first_of(delimiter, start);
    }

    return output;
}

int main() {
    const int NUM_RUNS = 15000;
    const std::string s = "1128=9\u00019=174\u000135=X\u000149=CME\u000175=20170403\u000134=1061\u000152=20170402211926965794928\u000160=20170402211926965423233\u00015799=10000100\u0001268=1\u0001279=1\u0001269=1\u000148=9006\u000155=ESM7\u000183=118\u0001270=236025.0\u0001271=95\u0001346=6\u00011023=9\u000110=088\u0001";

    std::vector<std::string> vec;

    // standard
    clock_t tStart = clock();
    for (int i = 0; i < NUM_RUNS; ++i)
    {
        vec = string_split(s, '=');
    }

    printf("Time taken using not reused vector: %.2fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);

    // reused vector
    tStart = clock();
    for (int i = 0; i < NUM_RUNS; ++i)
    {
        string_split_optim(vec, s, '=');

        vec.clear();
    }

    printf("Time taken using reused vector: %.2fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);


    //use boost

    tStart = clock();
    for (int i = 0; i < NUM_RUNS; ++i)
    {
        //string_split_optim(vec, s, '=');
        std::vector<std::string> strs;

        boost::split(strs, s, boost::is_any_of("="));
        //vec.clear();
    }

    printf("Time taken using boost library: %.2fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);

}
