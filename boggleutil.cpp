
//boggleutil.cpp

#include<iostream>
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
	for(int i=0;i<adjList.size();i++)
		adjList[i]->reset();	
}

void Board::makeEdge(){
	int size = row * col;
	for(int i=0;i<size;i++)
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
	for(int i=0;i<adjList.size();i++)
		delete adjList[i];
}
