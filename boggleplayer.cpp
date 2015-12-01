
//boggleplayer.cpp

#include "boggleplayer.h"

// before implementing the functions below, note that
// there will be two data structure in this class boggleplayer
// 1. hold the dictionary
// 2. hold the board

/**
 * takes in the official lexicon and loads the words into a efficient data structure (multiway tries)
 * as the interal field of boggleplayer. the tries is used for maintain the BogglePlayer's lexicon,
 * and should be implemented in boggleutil.h/cpp
 */
void BogglePlayer::buildLexicon(const set<string>& word_list){
}

/**
 * set the board by diceArray[row][coloumn]
 * Note: 1. all string in the dice should be lower case, if not, convert them in this function
 *		 2. 
 */
void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray) {
}

/**
 * After the buildLexicon and setBoard has been called, this method will return true:
 * it will find all legitimate words by the minimum length from the lexicon just built,
 * and store them into the words set
 * Note: all validation needs to meet in this method (i.e. 1. no duplicate; 2. no acyclic simple path;
 * 3. from lexicon; 4. meet min length
 */
bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words) {
        return true;
}

/** check if word_to_check is in the dictionary builded by buildLexicon() */
bool BogglePlayer::isInLexicon(const string& word_to_check) {
        return true;
}

/**
 * check if the word can be found on the board builded by setBoard() by acyclic simple path,
 * if FOUND, return a vector of int specifying the location of dice that can be used to form
 * the word(in the order to spell it). Empty vector means: 1. NOT FOUND; 2. board not set up yet
 * ex. if one of the letter is in Row R and C, it will be represented as R * Width + C
 */
vector<int> BogglePlayer::isOnBoard(const string& word) {
         vector<int> result;
         return result;
}


/**
 * use the setBoard() in this function to customize the arrayDice[][], note that the new_board
 * is not allocated for us, we need to allocate its memory by ourselves.
 */
void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols) {
}

