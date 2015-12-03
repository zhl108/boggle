
//boggleutil.cpp

#include<iostream>
#include<algorithm>			//std::transform
#include"boggleutil.h"

using namespace std;
//In this file, implement all of the operations your data structures support (you have declared these operations in boggleutil.h).

//------------------------------ Cell -------------------------------
Cell::Cell(int indx, string s){
	setIndex(indx);
	setString(s);
	visit = false;
	//leave neighbor blank, connecting vertices should be Board's job
}

void Cell::setString(string s){
	dice = s;
}
		
string Cell::getString(){
	return dice;
}

int Cell::nSize(){ return neighbors.size();}		

void Cell::addNeighbor(Cell* c){
	neighbors.push_back(c);
}

vector<Cell*> Cell::getNeighbor(){ return neighbors;}

void Cell::printNeighBor(){
	for(int i=0;i<nSize();i++){
		cout << "Neighbors of this:\n[";
		cout << getIndex();
		cout << "] " + neighbors[i]->getString() << endl;
	}
}

void Cell::setIndex(int i){ index = i;}

int Cell::getIndex(){ return index;}

bool Cell::isVisit(){ return visit;}	

void Cell::reset(){ visit = false;}	

void Cell::markVisit(){ visit = true;}

Cell::~Cell(){ neighbors.clear();}		//TODO: dont know if I should clear the vector here

//------------------------------ Board -------------------------------
Board::Board(unsigned int row, unsigned int col, string** s){
	this->row = row;
	this->col = col;
	for(unsigned int r=0;r<row;r++)
	{
		for(unsigned int c=0;c<col;c++)
		{
			unsigned int indx = col*r+c;
			//convert the string s[r][c] to lower case
			transform(s[r][c].begin(), s[r][c].end(), s[r][c].begin(), ::tolower);
			Cell* cell = new Cell(indx, s[r][c]);
			adjList.push_back(cell);					// add the new cell to the graph adjacency list
		}
	}	
	makeEdge();
}

void Board::print(){
	unsigned int size = row*col;
	for(unsigned int i=0;i<size;i++)
		cout << adjList[i]->getIndex() << " " << adjList[i]->getString() << endl;
}

vector<Cell*> Board::getList(){ return adjList;}

void Board::resetVisit(){
	for(unsigned int i=0;i<adjList.size();i++)
		adjList[i]->reset();	
}

void Board::makeEdge(){
	unsigned int size = row * col;
	for(unsigned int i=0;i<size;i++)
	{
		if(i==0)
		{
			//upper left corner
			adjList[i]->addNeighbor(adjList[i+1]);			
			adjList[i]->addNeighbor(adjList[i+col]);
			adjList[i]->addNeighbor(adjList[i+col+1]);
		}
		else if(i==col-1)
		{
			//upper right corner
			adjList[i]->addNeighbor(adjList[i-1]);			
			adjList[i]->addNeighbor(adjList[i+col]);
			adjList[i]->addNeighbor(adjList[i+col-1]);
		}
		else if(i==(row-1)*col)
		{
			//bottom left corner
			adjList[i]->addNeighbor(adjList[i+1]);			
			adjList[i]->addNeighbor(adjList[i-col]);
			adjList[i]->addNeighbor(adjList[i-col+1]);
		}
		else if(i==size-1)
		{
			//bottom right corner
			adjList[i]->addNeighbor(adjList[i-1]);			
			adjList[i]->addNeighbor(adjList[i-col]);
			adjList[i]->addNeighbor(adjList[i-col-1]);
		}
		else if(i>0 && i<col-1)
		{
			//top border
			adjList[i]->addNeighbor(adjList[i-1]);			
			adjList[i]->addNeighbor(adjList[i+1]);			
			adjList[i]->addNeighbor(adjList[i+col]);			
			adjList[i]->addNeighbor(adjList[i+col-1]);			
			adjList[i]->addNeighbor(adjList[i+col+1]);			
		}
		else if(i>(row-1)*col && i<size-1)
		{
			//bottom border
			adjList[i]->addNeighbor(adjList[i-1]);			
			adjList[i]->addNeighbor(adjList[i+1]);			
			adjList[i]->addNeighbor(adjList[i-col]);			
			adjList[i]->addNeighbor(adjList[i-col-1]);			
			adjList[i]->addNeighbor(adjList[i-col+1]);			
		}
		else if(i%col==0)		//TODO: not sure if it should exclude corner cases
		{
			//left border
			adjList[i]->addNeighbor(adjList[i+1]);			
			adjList[i]->addNeighbor(adjList[i-col]);			
			adjList[i]->addNeighbor(adjList[i-col+1]);			
			adjList[i]->addNeighbor(adjList[i+col]);			
			adjList[i]->addNeighbor(adjList[i+col+1]);			
		}
		else if(i%col==col-1)
		{
			//right border
			adjList[i]->addNeighbor(adjList[i-1]);			
			adjList[i]->addNeighbor(adjList[i-col]);			
			adjList[i]->addNeighbor(adjList[i-col-1]);			
			adjList[i]->addNeighbor(adjList[i+col]);			
			adjList[i]->addNeighbor(adjList[i+col-1]);			
		}
		else
		{
			//normal case: middle of the Board
			adjList[i]->addNeighbor(adjList[i-1]);			
			adjList[i]->addNeighbor(adjList[i+1]);			
			adjList[i]->addNeighbor(adjList[i-col]);			
			adjList[i]->addNeighbor(adjList[i-col-1]);			
			adjList[i]->addNeighbor(adjList[i-col+1]);			
			adjList[i]->addNeighbor(adjList[i+col]);			
			adjList[i]->addNeighbor(adjList[i+col-1]);			
			adjList[i]->addNeighbor(adjList[i+col+1]);			
		}
	}
}

Board::~Board(){
	for(unsigned int i=0;i<adjList.size();i++)
		delete adjList[i];
}



/* ---------------------- Tree ------------------------------ */

Trie::Trie(){
	root = new Node();
	size=1;
}

Trie::~Trie(){
	if(size>0)
		post(root);
}

void Trie::post(Node* n){
	for(map<char,Node*>::iterator i=n->children.begin();i!=n->children.end();i++)
		post(i->second);
	
	delete n;
	size--;
}

void Trie::insert (string &word){
	//start with the root
	Node* current = root;
	for(unsigned int i=0;i<word.length();i++)									//for every letter of the word
	{
		char c = word[i];
		if(current->children.find(c) == current->children.end())		//character not exist in the children map
		{
			Node* n = new Node();
			current->children.insert(std::make_pair(c,n));
			current = current->children[c];
			if(i == word.length()-1)									//check if the word has been run out
				current->end = true;

			size++;
		}
		else															// character already exist in the children map
		{
			current = current->children[c];
			if(i == word.length()-1)
				current->end = true;
		}
	}
}

bool Trie::find (string &word){
	Node* current = root;

	for(unsigned int i=0;i<word.length();i++)
	{
		char c = word[i];

		if(current->children.find(c) == current->children.end())		//character not found in the children map
			return false;
		else															// character already exist in the children map
			current = current->children[c];

		if(i == word.length()-1)
			return current->end;
	}
	return false;
}

Node* Trie::getRoot(){ return root;}

bool Trie::isPrefix(string word){
	Node* current = root;

	for(unsigned int i=0;i<word.length();i++)
	{
		char c = word[i];

		if(current->children.find(c) == current->children.end())	
			return false;
		else												
			current = current->children[c];
	}	
	return true;
}
