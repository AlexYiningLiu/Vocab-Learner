// Vocab_Learner.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "VocabDictionary.h"

int main()
{
    bool loop = true;
    std::string word, def;
    int queryIndex;
    int choice;
    int num_words;
    std::vector <std::string> pair;
    VocabDictionary myDictionary("vocabulary.txt");

    myDictionary.readFile();
    num_words = myDictionary.displayVocab();
    std::cout << "Total word count: " << num_words << std::endl;

    while (loop) {
        std::cout << "Enter 1 to display vocab list, enter 2 to query word, enter 3 to add new word: ";
        std::cin >> choice;
        if (choice == 1) {
            num_words = myDictionary.displayVocab();
            std::cout << "Total word count: " << num_words << std::endl;
        }
        else if (choice == 2) {
            std::cout << "Enter query by word or index: ";
            std::cin >> word;
            if (std::isdigit(static_cast<unsigned char> (word[0]))) {
                queryIndex = std::stoi(word);
                pair = myDictionary.getDef(queryIndex);
                word = pair[0];
                def = pair[1];
            }
            else {
                def = myDictionary.getDef(word);
            }
            std::cout << word << ": " << def << std::endl;
        }
        else if (choice == 3) {
            std::cout << "Enter word: ";
            std::cin >> word;
            std::cout << "Word: " << word << std::endl;
            std::cout << "Enter definition: ";
            std::cin.ignore();
            std::getline(std::cin, def);
            std::cout << "Definition: " << def << std::endl;
            myDictionary.writeFile(word, def);
        }
        else {
            std::cout << "Invalid entry" << std::endl;
        }
    }
}


