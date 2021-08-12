#pragma once
#include <string>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <tuple>

class VocabDictionary
{
public:
	VocabDictionary(std::string fileName) : fileName_(fileName) {}
	void writeFile(std::string wordIn, std::string defIn);
	void readFile();
	int displayVocab();
	std::string getRandomWord();
	std::string getDef(std::string word);
	std::vector <std::string> getDef(int queryIndex);
	std::vector <std::string> getAllDefinitions();

private:
	bool saveToDict(std::string wordIn, std::string defIn);
	std::string fileName_;
	std::unordered_map < std::string, std::string> dictionary_;
};

