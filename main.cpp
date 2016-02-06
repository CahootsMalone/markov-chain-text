#include <iostream>

#include "MarkovChainText.h"

int main(){

    std::cout << "Enter path of file to use:" << std::endl;

    std::string filePath;

    std::getline(std::cin, filePath);

    std::ifstream testFile(filePath, std::ios::in);

    if (!testFile.is_open()){
        std::cout << "Unable to open specfied file." << std::endl;
        return -1;
    }

    MarkovChainText mChain(testFile);

    testFile.close();

    std::cout << "*** Using " << filePath << " as source for Markov chain. ***" << std::endl;

    while (true){
        std::cout << "*** g to generate text, q to quit ***" << std::endl << ">";
        std::string input;
        std::getline(std::cin, input);
        if (input == "g"){
            std::cout << mChain.Generate() << std::endl;
        }
        else if (input == "q"){
            break;
        }
        else{
            std::cout << "Unknown input." << std::endl;
        }
    }

    return 0;
}
