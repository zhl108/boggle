
//boggleplayer.h

#ifndef BOGGLEPLAYER_H
#define BOGGLEPLAYER_H
#include "baseboggleplayer.h"
#include "boggleutil.h"
#include <stack>
using namespace std;

class BogglePlayer : public BaseBogglePlayer {
  public:
  //create a multiway tries and insert all string into it
  void buildLexicon(const set<string>& word_list);
  
  //initialize the internal 2d array
  void setBoard(unsigned int rows, unsigned int cols, string** diceArray); 

  bool getAllValidWords(unsigned int minimum_word_length, set<string>* words);
  
  bool isInLexicon(const string& word_to_check); 

  vector<int> isOnBoard(const string& word);

  void getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols);

  BogglePlayer() {
  }
  
  ~BogglePlayer() {
  }

  private:
  Board* b;												// data structure to hold the board
  //vector<int> dfs(Cell* c, const string& word);		// helper function for isOnBoard
  bool dfs(Cell* c, const string& word, int& pos, vector<int>& vec);
};

#endif
