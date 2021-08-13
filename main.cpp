// This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <algorithm>
#include <random>
#include "VocabDictionary.h"
#include "RequesterSocket.h"

const int numQuizCandidates = 5;

//void startPythonServer()
//{
//    std::string filename = "../../scripts/oxford_server.py";
//    std::string command = "python ";
//    command += filename;
//    system(command.c_str());
//}

void quizRandomWord(VocabDictionary * myDictionary, int & mistakes)
{
    static std::vector <std::string> quizzedWords;
    static std::vector <std::string> allDefinitions;
    std::vector <std::string> candidateWords;
    std::vector <std::string> candidateDefinitions;
    std::string selectedRandomWord;
    std::string possibleCandidate;
    int userInput;
    std::string answer;
    int counter = 0;

    allDefinitions = myDictionary->getAllDefinitions();
    // Randomly select the word and definition to be quizzed on
    while (true)
    {
        selectedRandomWord = myDictionary->getRandomWord();
        if (std::find(quizzedWords.begin(), quizzedWords.end(), selectedRandomWord) == quizzedWords.end())
        {
            quizzedWords.push_back(selectedRandomWord);
            break;
        }
    }
    answer = myDictionary->getDef(selectedRandomWord);
    candidateDefinitions.push_back(answer);

    // Randomly select a number of candidate definitions 
    while (counter < numQuizCandidates)
    {
        possibleCandidate = myDictionary->getRandomWord();
        if (std::find(candidateWords.begin(), candidateWords.end(), possibleCandidate) == candidateWords.end() && !(possibleCandidate == selectedRandomWord))
        {
            candidateWords.push_back(possibleCandidate);
            counter++;
        }
    }
    for (int i=0; i<candidateWords.size(); i++)
    {
        candidateDefinitions.push_back(myDictionary->getDef(candidateWords[i]));
    }
    auto rd = std::random_device{};
    auto rng = std::default_random_engine{ rd() };    
    std::shuffle(std::begin(candidateDefinitions), std::end(candidateDefinitions), rng);

    // Show the user all the available definitions 
    std::cout << "Select definition for: " << selectedRandomWord << std::endl;
    std::cout << "Available choices: " << std::endl;
    for (int i=0; i<candidateDefinitions.size(); i++)
    {
        std::cout << (i+1) << ": " << candidateDefinitions[i] << std::endl;
        std::cout << std::endl;
    }
    while (true)
    {
        std::cout << "Enter answer by index ";
        std::cin >> userInput;
        userInput -= 1;
        if (candidateDefinitions[userInput] == answer)
        {
            std::cout << "Correct!" << std::endl;
            std::cout << answer << std::endl;
            break;
        }
        else
        {
            mistakes++;
            std::cout << "Incorrect, try again." << std::endl;
        }
    }
}

int main()
{
    srand((unsigned int)time(NULL));

    bool loop = true;
    std::string word, def;
    int queryIndex;
    int choice;
    int num_words;
    int result; 
    int wordsQuizzed = 0;
    int mistakes = 0;
    std::vector <std::string> pair;
    VocabDictionary myDictionary("vocabulary.txt");

    RequesterSocket client(54000, "127.0.0.1");
    client.connectToServer();

    myDictionary.readFile();
    num_words = myDictionary.displayVocab();
    std::cout << "Total word count: " << num_words << std::endl;

    while (loop) 
    {
        std::cout << "Enter 1 to display vocab list, enter 2 to query word, enter 3 to add new word, enter 4 to quiz random words: ";
        std::cin >> choice;
        std::cout << std::endl;
        if (std::cin.fail())
        {
            std::cout << "Invalid entry" << std::endl;
            std::cin.clear();
            std::cin.ignore(256, '\n');
            continue; 
        }
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
        else if (choice == 4)
        {
            quizRandomWord(&myDictionary, mistakes);
            wordsQuizzed++;
            std::cout << "Quizzed " << wordsQuizzed << " words, made " << mistakes << " wrong choices." << std::endl;
            std::cout << std::endl;
        }
        else {
            std::cout << "Invalid entry" << std::endl;
        }
    }
}


