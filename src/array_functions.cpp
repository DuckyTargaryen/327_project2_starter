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
	int occurances;
};

entry words[constants::MAX_WORDS];

int slot = 0;

//TODO define all functions in header file
void clearArray(){
	slot = 0;
}

int getArraySize(){
	return slot;
}

std::string getArrayWordAt(int i){
	return words[i].word;
}

int getArrayWord_NumbOccur_At(int i){
	return words[i].occurances;
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
	string tempToken = token;
	toUpper(tempToken);
	cout << token << endl;
	for(entry e : words){
		string temp = e.word;
		toUpper(temp);
		if(token == e.word){
			e.occurances += 1;
			return;
		}
	}
	entry ent;
	ent.word = token;
	ent.occurances = 1;
	words[slot] = ent;

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
	return 0;
}

void sortArray(constants::sortOrder so){

}
//TODO look in utilities.h for useful functions, particularly strip_unwanted_chars!
