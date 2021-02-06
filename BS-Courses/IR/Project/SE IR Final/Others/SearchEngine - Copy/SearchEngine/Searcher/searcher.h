#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <map>
#include <math.h>
#include <algorithm>
#include "porter.h"

#define TARGETFOLDER "./Docs/"

//------------------------------------------------------------------
using namespace std;

struct CDocsFreq
{
	CDocsFreq(int pDoc = 0, CDocsFreq *pNext = NULL)
	{
		mDoc = pDoc;
		mFreq = 1;
		mNext = pNext;
	}

	int mDoc, mFreq;
	CDocsFreq *mNext;
};

//------------------------------------------------------------------

class CSearcher
{
public:
	CSearcher();
	void MakeIndex();
	void LoadIndex();
	vector<int> SearchWithQuery(const char *pQuery);


	vector<string> docs;
	vector< vector<pair<string, long double> > > documentVectors;
	map<string, pair<int, CDocsFreq*> > invertedIndex;

private:
	void ProcessDoc(int pFile);

	map<string, char> stop;

};
