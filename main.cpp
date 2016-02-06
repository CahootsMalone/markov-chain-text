#include <iostream>

#include "MarkovChainText.h"

int main(){

    std::string filePath("owls.txt");

    std::ifstream testFile(filePath, std::ios::in);

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
