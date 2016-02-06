#ifndef MARKOVCHAINTEXT_H_INCLUDED
#define MARKOVCHAINTEXT_H_INCLUDED

#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>
#include <set>
#include <cctype>
#include <random>
#include <chrono>

class MarkovChainText {
public:
    MarkovChainText(std::istream &inStream, unsigned int initOrder = 2);
    void AddText(const std::string &text);
    std::string Generate(unsigned int minNumberOfWords = 0) const;

private:
    unsigned int order;

    std::vector<std::string> startKeys; // List of keys that begin with an uppercase letter
    std::map<std::string, std::vector<std::string>> table;

    std::string ConcatenateVectorOfStrings(std::vector<std::string>::iterator first, std::vector<std::string>::iterator last, const std::string &delimiter = " ") const;
    std::vector<std::string> SplitStringIntoVector(const std::string &input) const;
};

#endif // MARKOVCHAINTEXT_H_INCLUDED
