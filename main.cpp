// Vocab_Learner.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "VocabDictionary.h"
#include "RequesterSocket.h"

//void startPythonServer()
//{
//    std::string filename = "../../scripts/oxford_server.py";
//    std::string command = "python ";
//    command += filename;
//    system(command.c_str());
//}

int main()
{
    bool loop = true;
    std::string word, def;
    int queryIndex;
    int choice;
    int num_words;
    int result; 
    std::vector <std::string> pair;
    VocabDictionary myDictionary("vocabulary.txt");

    RequesterSocket client(54000, "127.0.0.1");
    client.connectToServer();

    myDictionary.readFile();
    num_words = myDictionary.displayVocab();
    std::cout << "Total word count: " << num_words << std::endl;

    while (loop) 
    {
        std::cout << "Enter 1 to display vocab list, enter 2 to query word, enter 3 to add new word: ";
        std::cin >> choice;
        if (choice == 1) 
        {
            num_words = myDictionary.displayVocab();
            std::cout << "Total word count: " << num_words << std::endl;
        }
        else if (choice == 2) 
        {
            while (true) {
                std::cout << "Enter query by word or index, enter 0 to return: ";
                std::cin >> word;
                if (word == "0") 
                {
                    break; 
                }
                if (std::isdigit(static_cast<unsigned char> (word[0]))) 
                {
                    queryIndex = std::stoi(word);
                    pair = myDictionary.getDef(queryIndex);
                    word = pair[0];
                    def = pair[1];
                }
                else 
                {
                    def = myDictionary.getDef(word);
                }
                std::cout << word << ": " << def << std::endl << std::endl;                
            }
        }
        else if (choice == 3) {
            while (true) 
            {
                std::cout << "Enter new word, enter 0 to return: ";
                std::cin >> word;
                if (word == "0") 
                {
                    break; 
                }
                std::cout << "Word: " << word << std::endl;
                // Send word to server and wait for response 
                result = client.queryWord(word, def);
                std::cout << "Definition: " << def << std::endl;
                if (result == 1)
                {
                    myDictionary.writeFile(word, def);
                }
                else
                {
                    std::cout << "Not saved" << std::endl;
                }
            }
        }
        else {
            std::cout << "Invalid entry" << std::endl;
        }
    }
}


