#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <list>
#include <map>
#include <set>
#include <limits>
#include "FPTree.h"

using namespace std;

struct TreeNode {
	int elementValue;
	int elementFrequency;
	TreeNode* up;
	list<TreeNode*> down;
	TreeNode* nextSimilar;
	TreeNode* prevSimilar;
};

struct ConnectionRow {
	TreeNode* firstOccurrence;
	map <int, int> connectedElements; //key value is element number and the other value is frequency
	int elementFrequency;
	TreeNode* lastOccurrence;
};

class SRPTree {
	int rareMinSup;
	int freqMinSup;
	int windowSize; //number of transactions after which mining should start
	int inputWindowSize; //input window size given by a user
	int distinctElements;
	int inputDistinctElements;
	string filename;
	string sConfigFileLine;
	ifstream in;
	ifstream configStream;
	TreeNode *rootNode;
	bool useDfs;

	map <int, ConnectionRow*> connectionTable;
	string sTransaction;  //One Transaction information in string
	list<int> iTransaction;  //List of integers for each transaction

	void ExtractIntegersToList();
	void AddElementFrequency();
	void AddToTree();
	void AddToConnectionTable();
	TreeNode* AllocateTreeNodeMemory(int value);
	ConnectionRow* AllocateConnectionRow();
	void clearPreviousWindow();
	void DeleteTreeNodes();
	void ClearWhiteSpace();

public:
	SRPTree();

	int Initialize();
	int Finalize();
	int ReadTransaction();
	int GetWindowSize();
	map<set<int>, int> Mine();
};
