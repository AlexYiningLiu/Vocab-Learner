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
	std::ifstream inFile(fileName_);
	std::string line;
	std::string stringPart;
	std::vector<std::string> partsVector;
	while (std::getline(inFile, line)) {
		std::stringstream ss(line);
		while (std::getline(ss, stringPart, ':')) {
			partsVector.push_back(stringPart);
		}
		dictionary_[partsVector[0]] = partsVector[1];
		partsVector.clear();
	}
	std::cout << "Done reading!" << std::endl;
}

int VocabDictionary::displayVocab() {
	int counter = 0;
	for (const auto& [word, def] : dictionary_) {
		counter += 1;
		std::cout << counter << ". " << word << std::endl << std::endl;
	}
	return counter;
}

std::string VocabDictionary::getDef(std::string word) {
	if (dictionary_.find(word) != dictionary_.end()) {
		return dictionary_[word];
	}
	else {
		std::cout << "Word not found!" << std::endl;
		return "";
	}
}

std::vector <std::string> VocabDictionary::getDef(int queryIndex) {
	int counter = 0;
	std::vector <std::string> pair(2);
	if (queryIndex > dictionary_.size()) {
		std::cout << "Index out of range!" << std::endl;
		return pair;
	}
	else {
		for (const auto& [word, def] : dictionary_) {
			counter += 1;
			if (counter == queryIndex) {
				pair[0] = word;
				pair[1] = def;
				return pair;
			}
		}
		return pair;
	}
}