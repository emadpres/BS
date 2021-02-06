

#include <iostream>
#include <algorithm>
#include <assert.h>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <set>

#include "dirent.h"
//#include "myTime.h"

#define TARGETFOLDER "./Docs/"
//------------------------------------------------------------------
using namespace std;

struct CDocNode
{
	CDocNode(int pDoc = 0, CDocNode *pNext = NULL)
	{
		mDoc = pDoc;
		mFreq = 1;
		mNext = pNext;
	}
	
	int mDoc, mFreq;
	CDocNode *mNext;
};

//------------------------------------------------------------------

typedef map<string, pair<int, CDocNode*>> inv;







class CSearcher
{
public:
	CSearcher();
	void MakeIndex();
	void LoadIndex();
	vector<int> SearchWithQuery(const char * pQuery);


private:
	void ProcessDoc(int pFile);

	vector<string> docs;

	//vector<vector<pair<string, long double>>> documentVectors;
	inv invertedIndex;

	set<string> stop;

};
