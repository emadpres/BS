#ifndef _AVERAGE_CLUSTER_H_
#define _AVERAGE_CLUSTER_H_

#include "searcher.h"

class CAverageCluster
{
public:
	CAverageCluster(CSearcher *pParent);
	void Cluster(int k);

	int N;
	bool *mChecked;
	long double **mSimilarityTable, **mSimDoc;
	vector<int> *mClusters;
	CSearcher *mParent;


private:
	void Merge(int pCluster1, int pCluster2);

	long double Similarity(int pDocnum1, int pDocnum2);
	long double PreSimilarity(vector<pair<string, long double> > &pDoc1, vector<pair<string, long double> > &pDoc2);

};


#endif
