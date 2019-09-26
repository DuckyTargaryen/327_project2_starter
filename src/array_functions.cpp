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
struct entry{	//The struct used for the entries
	string word;
	int occurrences;
};

entry wordArry[constants::MAX_WORDS];

int slot = 0;
//============================================================================

//============================================================================
/**
 * Clears the array
 */
void clearArray(){
	slot = 0;
}

/**
 * Gets the size of the array
 * return: An int representing the size of the array
 */
int getArraySize(){
	return slot;
}

/**
 * Returns the word located at the specified index
 * param: i The specified index
 * return: A string representing the word
 */
std::string getArrayWordAt(int i){
	return wordArry[i].word;
}

/**
 * Returns the number of occurrences of a word
 * at a specified index
 * param: i The specified index
 * return: An int representing the number of occurrences
 */
int getArrayWord_NumbOccur_At(int i){
	return wordArry[i].occurrences;
}

/**
 * Retrieves input from a file
 * param: myfstream The fstream of the input file
 * return: A bool representing if the retrieval was successful
 */
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

/**
 * Separates each line into individual tokens
 * param: myString A line of text
 */
void processLine(std::string &myString){
	stringstream strStream(myString);

	string token;

	while(getline(strStream, token, constants::CHAR_TO_SEARCH_FOR)){
		processToken(token);
	}

}

/**
 * Adds the token to the array
 * param: token The token or word
 */
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

/**
 * Opens the file and creates a fstream
 * param: myfile An unopened fstream
 * param: myFileName The name of the input file
 * param: mode The mode in which the file is opened
 * return: A bool indicating whether the file was able to be opened
 */
bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode){
	myfile.open(myFileName.c_str(), mode);
	processFile(myfile);
	return myfile.is_open();
}

/**
 * Closes the fstream if it is still open
 * param: myfile The fstream that needs to be closed
 */
void closeFile(std::fstream& myfile){
	if(myfile.is_open()){
		myfile.close();
	}
}

/**
 * Writes the contents of the array to the output file
 * param: outputfilename The name of the output file
 * return: An int representing the success or failure of writing to a file
 */
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

/**
 * Sorts the contents of the array using the
 * selection sort algorithm
 * param: so The order in which the contents will be sorted
 */
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
//============================================================================
