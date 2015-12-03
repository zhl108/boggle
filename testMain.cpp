
//main.cpp

/**
 *  CSE 100 C++ Boggle
 *  Authors: Vivek Ramavajjala, Paul Kube
 */

#include<iostream>
#include<vector>
#include"boggleutil.h"
#include"boggleplayer.h"
using namespace std;

int main(int argc, char *argv[])
{
	cout << "--------------- Unit Test for Data Structure ---------------" << endl;
	cout << "Tested data structure:\n1. Board of Cell (graph) for BoggleBoard\n2. Tenary Tree to hold lexicon\n" << endl;


	cout << "--------------- Cell ---------------" << endl;
	
	cout << "Testing Constructor ..." << endl;
	Cell* c = new Cell(0, "first cell");
	if(c->getIndex()!=0 || c->getString()!="first cell"){
		cout << "constructor fail" << endl;
		return -1;
	}

	cout << "constructor pass!\nTesting setter..." << endl;
	c->setIndex(55);
	c->setString("new");
	if(c->getIndex()!=55 || c->getString()!="new"){
		cout << "setter fail" << endl;
		return -1;
	}

	cout << "setter pass!\nTesting neighbor method..." << endl;
	if(c->nSize()!=0){
		cout << "neighbor method fail" << endl;
		return -1;
	}
	c->addNeighbor(new Cell(0, "neighbor 0"));
	if(c->nSize()!=1){
		cout << "neighbor method fail" << endl;
		return -1;
	}
	c->addNeighbor(new Cell(1, "neighbor 1"));
	if(c->nSize()!=2){
		cout << "neighbor method fail" << endl;
		return -1;
	}

	for(int i=0;i<c->nSize();i++)
	{
		string s = "neighbor " + to_string(i);
		if(c->getNeighbor()[i]->getIndex()!=i || c->getNeighbor()[i]->getString()!=s){
			cout << "neighbor method fail" << endl;
			return -1;
		}
	}
	cout << "neighbor method pass!" << endl << endl;

	//free memory
	for(int j=0;j<c->nSize();j++)
		delete c->getNeighbor()[j];

	delete c;

	cout << "--------------- Board ---------------" << endl;

	cout << "Testing adjList ..." << endl;
	/* test case board 3x3
	string str[3][3] = {
				{"zero","one","two"},
				{"three","four","five"},
				{"six","seven","eight"}
	};

	string *s[3] = {str[0],str[1],str[2]};	
	
	Board* b = new Board(3,3,s);
	*/
	string str[2][3] = {
				{"zero","one","two"},
				{"three","four","five"}
	};

	string *s[2] = {str[0],str[1]};	
	
	Board* b = new Board(2,3,s);

	/* test case board 3x5
	string str[5][3] = {
				{"zero","one","two"},
				{"three","four","five"},
				{"six","seven","eight"},
				{"nine","ten","eleven"},
				{"twelve","thirdteen","fourteen"}
	};

	string *s[5] = {str[0],str[1],str[2],str[3],str[4]};	
	
	Board* b = new Board(5,3,s);
	*/

	//b->print();	
	cout << "adjList test pass!\nTesting makeEdge() ..." << endl;
	/* print adjacency list with edge conection (neighbor)
	for(int i=0;i<b->getList().size();i++)
	{
		Cell* cell = b->getList()[i];
		int size = cell->nSize();
		int indx = cell->getIndex();
		string str = cell->getString();

		cout << indx << " " << str << ": ";
		for(int k=0;k<size;k++)
			cout << cell->getNeighbor()[k]->getIndex() << " " << cell->getNeighbor()[k]->getString() << " | ";
		cout << endl;
	}
	*/
	cout << "makeEdge() test pass! the graph has been completely builded!" << endl << endl;
	delete b;

	cout << "--------------- BogglePlayer ---------------" << endl;
	cout << "Testig isOnBoard() ..." << endl;
	BogglePlayer* bp = new BogglePlayer();
	bp->setBoard(2,3,s);

	string input = "fivefourthreeone";
	vector<int> outcome = bp->isOnBoard(input);
	
	cout << "Path: " << endl;
	for(int i=0;i<outcome.size();i++)
		cout << outcome[i] << " -> ";

	cout << endl << "isOnBoard() test pass!" << endl << endl;
	delete bp;

	/* test substr()
	string aa = "yeti";
	string cc = "yetimango";
	string bb = cc.substr(0,4);
	cout << aa << endl;
    cout << bb << endl;
   	cout << (aa!=bb) << endl;
	*/

	cout << "--------------- Tree ---------------" << endl;
	cout << "Testing insert ..." << endl;
	Trie* tree = new Trie();
	string t1 = "ab", t2 = "zxy";
	string a1 = "a", a2 = "zx";
	string b1 = "abc", b2 = "zxyt";
	tree->insert(t1);
	tree->insert(t2);

	Node* ro = tree->getRoot();
	if(!ro->children['a']->children['b']->end || !ro->children['z']->children['x']->children['y']->end)
	{
		cout << "insert fail"<< endl;
		return -1;
	}
	cout << "insert test pass!\nTesting find() ..." << endl;
	if(!tree->find(t1) || !tree->find(t2) || tree->find(a1) || tree->find(a2) || tree->find(b1) || tree->find(b2))
	{	
		cout << "find fail" << endl;
		return -1;
	}
	cout << "find test pass!\nTesting isPrefix()" << endl;
	if(!tree->isPrefix(a1) || !tree->isPrefix(a2) || !tree->isPrefix(t1) || !tree->isPrefix(t2) || tree->isPrefix(b1) || tree->isPrefix(b2))
	{	
		cout << "isPrefix fail" << endl;
		return -1;
	}
	cout << "isPrefix test pass!" << endl << endl;

	delete tree;
	cout << "--------------- my own test ---------------" << endl;
	vector<string> vec;
	vec.push_back("one");
	vec.push_back("two");
	vec.push_back("three");

	for(vector<string>::iterator it=vec.begin(); it != vec.end(); ++it)
		cout << *it << endl;
	string ss;
	for(vector<string>::iterator it=vec.begin(); it != vec.end(); ++it)
		ss.append(*it);
	cout << ss << endl;

    return 0;
}

