#include "VocabDictionary.h"

void VocabDictionary::writeFile(std::string wordIn, std::string defIn) {
	bool newWord;
	newWord = saveToDict(wordIn, defIn);
	if (newWord) {
		std::ofstream outFile;
		outFile.open(fileName_, std::ios_base::app); 
		if (outFile.is_open()) {
			outFile << (wordIn + ": " + defIn + "\n");
			outFile.close();
		}
		std::cout << "Saved to file!" << std::endl << std::endl;
	}
}

bool VocabDictionary::saveToDict(std::string wordIn, std::string defIn) {
	if (dictionary_.find(wordIn) == dictionary_.end()) {
		dictionary_[wordIn] = defIn; 
		return true; 
	}
	else {
		std::cout << "Word and definition already saved" << std::endl; 
		return false; 
	}
}

void VocabDictionary::readFile() {
	std::ifstream inFile; 
	inFile.open(fileName_, std::ios_base::in);
	std::string line; 
	std::string stringPart;
	std::vector<std::string> partsVector; 
	if (inFile.is_open()) {
		while (std::getline(inFile, line)) {
			std::stringstream ss(line); 
			while (std::getline(ss, stringPart, ':')) {
				partsVector.push_back(stringPart); 
			}
			dictionary_[partsVector[0]] = partsVector[1]; 
		}
	}
	inFile.close(); 
	std::cout << "Done reading!" << std::endl; 
}

