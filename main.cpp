// Vocab_Learner.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "VocabDictionary.h"

int main()
{
    VocabDictionary myDictionary("vocabulary.txt");
    myDictionary.readFile(); 
    bool loop = true;
    std::string word, def; 
    while (loop) {
        std::cout << "Enter word: ";
        std::cin >> word; 
        std::cout << "Word: " << word << std::endl;
        std::cout << "Enter definition: ";
        std::cin.ignore();
        std::getline(std::cin, def); 
        std::cout << "Definition: " << def << std::endl;
        myDictionary.writeFile(word, def);
    }
}


