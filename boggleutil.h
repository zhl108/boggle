
//boggleutil.h

#ifndef BOGGLEUTIL_H
#define BOGGLEUTIL_H
#include<vector>
#include<string>

using namespace std;

//Data structures for lexicon and board should reside in this file.
//All of the operations your data structures support should be declared within your data structures.

class Cell
{
	private:
		string dice;					// content of the cell
		vector<Cell*> neighbors;		// all Cells attached to this Cell
		int index;
		bool visit;

	public:
		Cell(int indx, string s);
		void setString(string s);		// set cell content
		string getString();				// return the dice
		int nSize();					// return the # of neighbors
		void addNeighbor(Cell* c);		// add a pointer of Cell to the neighbors list
		vector<Cell*> getNeighbor();	// return a list of neighbors
		void printNeighBor();			// for test only
		void setIndex(int i);			// set cell index for path
		int getIndex();					// return the index of cell
		bool isVisit();					// return visit status of the cell
		void reset();					// toggle the visit back to false
		void markVisit();

		~Cell();
};

/** board is a graph class whose vertices are the cell of the board */
class Board
{
	private:
		unsigned int row, col;
		vector<Cell*> adjList;										// adjacency list of the graph

	public:
		Board(unsigned int row, unsigned int col, string** s);
		void print();												// print the adjacency list, for test only
		void makeEdge();											// associate Cells on the Board
		vector<Cell*> getList();									// return the adjacency list of the graph
		void resetVisit();											// toggle all Cells of the graph back to unvisited
		~Board();
};

/** Ternary Trie to hold lexicon dictironary */
class Tree
{
	private:

	public:
};

#endif
