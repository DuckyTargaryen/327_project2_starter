/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: keith
 */

//============================================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "array_functions.h"
#include "utilities.h"
#include "constants.h"
using namespace std;
//============================================================================

//============================================================================
//	stuff you will need
//============================================================================
struct entry{
	string word;
	int occurrences;
};

entry wordArry[constants::MAX_WORDS];

int slot = 0;

void clearArray(){
	slot = 0;
}

int getArraySize(){
	return slot;
}

std::string getArrayWordAt(int i){
	return wordArry[i].word;
}

int getArrayWord_NumbOccur_At(int i){
	return wordArry[i].occurrences;
}

bool processFile(std::fstream &myfstream){
	if(!myfstream.is_open()){
		return false;
	}
	string line;
	while(!myfstream.eof()){
		getline(myfstream, line);
		processLine(line);
	}

	return myfstream.is_open();
}

void processLine(std::string &myString){
	stringstream strStream(myString);

	string token;

	while(getline(strStream, token, constants::CHAR_TO_SEARCH_FOR)){
		processToken(token);
	}

}

void processToken(std::string &token){
	strip_unwanted_chars(token);
	if(token != ""){
		string tempToken = token;
		toUpper(tempToken);
		for(int i = 0; i<slot; i++){
			string temp = wordArry[i].word;
			toUpper(temp);
			if(tempToken == temp){
				wordArry[i].occurrences += 1;
				return;
			}
		}
		entry ent;
		ent.word = token;
		ent.occurrences = 1;
		wordArry[slot] = ent;
		slot += 1;
	}
}

bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode){
	myfile.open(myFileName.c_str(), mode);
	processFile(myfile);
	return myfile.is_open();
}

void closeFile(std::fstream& myfile){
	if(myfile.is_open()){
		myfile.close();
	}
}

int writeArraytoFile(const std::string &outputfilename){
	ofstream outputStream;
	outputStream.open(outputfilename.c_str());
	if(!outputStream.is_open()){
		return constants::FAIL_FILE_DID_NOT_OPEN;
	}
	else if(slot == 0){
		outputStream.close();
		return constants::FAIL_NO_ARRAY_DATA;
	}
	else{
		for(int i = 0; i < slot; i++){
			outputStream << wordArry[i].word + " " + intToString(wordArry[i].occurrences) << endl;
		}
		outputStream.close();
		return constants::SUCCESS;
	}
}

void sortArray(constants::sortOrder so){
	if(so == constants::ASCENDING){
		for(int i = 0; i < slot; i++){
			string minWord = wordArry[i].word;
			string tempMinWord = minWord;
			toUpper(tempMinWord);
			int minIndex = i;
			for(int j = i; j < slot; j++){
				string tempWord = wordArry[j].word;
				toUpper(tempWord);
				if(tempWord < tempMinWord){
					minIndex = j;
					minWord = wordArry[j].word;
					tempMinWord = wordArry[j].word;
					toUpper(tempMinWord);
				}
			}
			if(minWord != wordArry[i].word){
				entry swap = wordArry[i];
				wordArry[i] = wordArry[minIndex];
				wordArry[minIndex] = swap;
			}
		}

	}
	else if(so == constants::DESCENDING){
		for(int i = 0; i < slot; i++){
			string maxWord = wordArry[i].word;
			string tempMaxWord = maxWord;
			toUpper(tempMaxWord);
			int maxIndex = i;
			for(int j = i; j < slot; j++){
				string tempWord = wordArry[j].word;
				toUpper(tempWord);
				if(wordArry[j].word > maxWord){
					maxIndex = j;
					maxWord = wordArry[j].word;
					tempMaxWord = wordArry[j].word;
					toUpper(tempMaxWord);
				}
			}
			if(maxWord != wordArry[i].word){
				entry swap = wordArry[i];
				wordArry[i] = wordArry[maxIndex];
				wordArry[maxIndex] = swap;
			}
		}
	}
	else if(so == constants::NUMBER_OCCURRENCES){
		for(int i = 0; i < slot; i++){
			int minOccur = wordArry[i].occurrences;
			int minIndex = i;
			for(int j = i; j < slot; j++){
				if(wordArry[j].occurrences < minOccur){
					minIndex = j;
					minOccur = wordArry[j].occurrences;
				}
			}
			if(minOccur != wordArry[i].occurrences){
				entry swap = wordArry[i];
				wordArry[i] = wordArry[minIndex];
				wordArry[minIndex] = swap;
			}
		}
	}

}
