#include "MarkovChainText.h"

MarkovChainText::MarkovChainText(std::istream &inStream, unsigned int initOrder) : order(initOrder) {
    std::string curLine;

    // TODO this never exits if inStream is std::cin; perhaps just take a file name rather than an istream
    while (std::getline(inStream, curLine)){

        if (curLine.empty()){
            continue;
        }

        AddText(curLine);
    }
}

void MarkovChainText::AddText(const std::string &text) {
    std::vector<std::string> wordsCurText = SplitStringIntoVector(text);

    if (wordsCurText.size() < order){
        return;
    }

    for (size_t curGram = 0; curGram < wordsCurText.size() - order; ++curGram){

        std::string curKey = ConcatenateVectorOfStrings(wordsCurText.begin()+curGram, wordsCurText.begin()+curGram+order);

        table[curKey].push_back(wordsCurText[curGram+order]);

        if (isupper(curKey[0]) && (curGram == 0 || wordsCurText[curGram-1].back() == '.' || wordsCurText[curGram-1].back() == '!' || wordsCurText[curGram-1].back() == '?')){
            if (std::find(startKeys.begin(), startKeys.end(), curKey) == startKeys.end()){
                startKeys.push_back(curKey);
            }
        }
    }
}

std::string MarkovChainText::Generate(unsigned int minNumberOfWords) const {

    std::vector<std::string> result;

    int seedVal = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seedVal);

    std::string curKey = *(startKeys.begin() + (generator()/(1.f*generator.max()))*startKeys.size());
    std::vector<std::string> curKeyVector = SplitStringIntoVector(curKey);
    result.insert(result.end(), curKeyVector.begin(), curKeyVector.end());

    while (result.size() < minNumberOfWords || result.back().back() != '.'){

        if (table.count(curKey) == 0){ // Dead end
            curKey = *(startKeys.begin() + (generator()/(1.f*generator.max()))*startKeys.size()); // Randomly select a new key
            curKeyVector = SplitStringIntoVector(curKey);
            result.insert(result.end(), curKeyVector.begin(), curKeyVector.end());
        }

        std::string nextWord = table.at(curKey)[(generator()/(1.f*generator.max()))*table.at(curKey).size()];
        result.push_back(nextWord);
        curKey = ConcatenateVectorOfStrings(result.end()-order, result.end());
    }

    std::string outputString(MarkovChainText::ConcatenateVectorOfStrings(result.begin(), result.end(), " "));

    //std::copy(result.begin(), result.end(), std::ostream_iterator<std::string>(std::cout, " "));

    return outputString;
}

std::string MarkovChainText::ConcatenateVectorOfStrings(std::vector<std::string>::iterator first, std::vector<std::string>::iterator last, const std::string &delimiter) const {
    std::string result;
    for (auto curIter = first; curIter != last; ++curIter){
        if (curIter != first){
            result += delimiter;
        }
        result += *curIter;
    }
    return result;
}

std::vector<std::string> MarkovChainText::SplitStringIntoVector(const std::string &input) const {
    std::vector<std::string> result;
    std::stringstream converter(input);
    std::string word;
    while (converter >> word){
        result.push_back(word);
    }
    return result;
}
