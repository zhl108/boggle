
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
	b = new Board(rows, cols, diceArray);
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
		 int pos=0;

		 if(b==0)
			 return result;								//board not set up yet

		 /*
		 for(int i=0;i<b->getList().size();i++)
		 {
			 b->resetVisit();							//toggle all Cells to be unvisited
			 result = dfs(b->getList()[i], word);
			 if(result.size() != 0)
				 break;
		 }
		 */
		 for(int i=0;i<b->getList().size();i++)
		 {
			 if(dfs(b->getList()[i], word, pos, result))
				 break;

			 b->resetVisit();							//toggle all Cells to be unvisited
			 pos=0;
			 result.clear();

		 }
         return result;
}

bool BogglePlayer::dfs(Cell* c, const string& word, int& pos, vector<int>& vec){

	string sub_word;
	string cString = c->getString();
	int cSize = cString.length();
	if(cSize <= word.length()-pos)
		sub_word = word.substr(pos, cSize);
	else
		sub_word = word.substr(pos);

	if(cString != sub_word)
		return false;
	//above is to check if the dice match the word

	//else match, update path and word mark
	c->markVisit();
	pos+=cSize;
	vec.push_back(c->getIndex());

	if(pos == word.length())
		return true;

	for(int i=0;i<c->nSize();i++)
	{
		if(!c->getNeighbor()[i]->isVisit())				//unvisited neighbor
		{	
			if(dfs(c->getNeighbor()[i], word, pos, vec))
				return true;
		}
	}

	vec.pop_back();
	pos-=cSize;
	c->reset();
	return false;
}

/**
 * use the setBoard() in this function to customize the arrayDice[][], note that the new_board
 * is not allocated for us, we need to allocate its memory by ourselves.
 */
void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols) {
}

/* fail stack method
vector<int> BogglePlayer::dfs(Cell* c, const string& word){
	vector<int> path;
	int pos=0;									//mark pointed to the next char should be read in word
	stack<Cell*> st;
	Cell* top;

	string cString;
	int cSize;
	string sub_word;

	st.push(c);
	while(!st.empty())
	{
		top = st.top();
		st.pop();

		if(!top->isVisit())
		{
			cString = top->getString();
			cSize = cString.length();
			if(cSize <= word.length()-pos)
				sub_word = word.substr(pos, cSize);
			else
				sub_word = word.substr(pos);

			if(cString != sub_word)
				continue;											//if cell string dont match the word, stop diving

			//if(pos == word.length())
				//break;

			path.push_back(top->getIndex());						//record the index of cell in the path list
			
			pos+=cSize;
			if(pos == word.length())								//all word char matched
				break;

			top->markVisit();										//mark top as visited
			for(int i=0;i<top->nSize();i++)
			{
				st.push(top->getNeighbor()[i]);						//add top's neighbors which satisfy the correct path to the stack
					
			}
		}
	}

	if(pos != word.length())
		path.clear();

	return path;
}
*/
