#pragma once
#include <string>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

class VocabDictionary
{
public:
	VocabDictionary(std::string fileName) : fileName_(fileName) {}
	void writeFile(std::string wordIn, std::string defIn); 
	void readFile(); 
	std::unordered_map < std::string, std::string> dictionary_;

private:
	bool saveToDict(std::string wordIn, std::string defIn);
	std::string fileName_; 
};

