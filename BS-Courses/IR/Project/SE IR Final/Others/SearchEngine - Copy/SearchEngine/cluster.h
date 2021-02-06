#ifndef _CLUSTER_H_
#define _CLUSTER_H_

#include "Searcher/searcher.h"

class CCluster
{
public:
	CCluster(CSearcher *pParent);
	void Cluster(int k);

	int N;
	bool *mChecked;
	long double **mSimilarityTable, *mSelfSimilarity;
	vector<int> *mClusters;
	vector<pair<string, long double> > *mClustersVectors;
	CSearcher *mParent;


private:
	void Merge(int pCluster1, int pCluster2);

	long double Similarity(int pDocnum1, int pDocnum2);
//	long double Similarity(vector<pair<string, long double> > &pDoc1, vector<pair<string, long double> > &pDoc2);

};


#endif
