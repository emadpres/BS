#include "cluster.h"

CCluster::CCluster(CSearcher *pParent)
{
	mParent = pParent;
	N = mParent->docs.size();

	mChecked = new bool[N];
	mClusters = new vector<int> [N];
	mClustersVectors = new vector<pair<string, long double> > [N];
	mSimilarityTable = new long double *[N];
	for (int i = 0 ; i < N; i++)
	{
		mSimilarityTable[i] = new long double[N];

		mClusters[i].push_back(i);
		mClustersVectors[i] = mParent->documentVectors[i];
		if (mClustersVectors[i].size())
			mChecked[i] = true;
		else
			mChecked[i] = false;
	}

	for (int i = 0; i < N; i++)
		for (int j = i; j < N; j++)
			mSimilarityTable[i][j] = mSimilarityTable[j][i] = Similarity(mClustersVectors[i], mClustersVectors[j]);
}


void CCluster::Cluster(int k)
{
	int n = N, x = -1, y = -1;
	long double max = 0;
	for (int i = 0; i < N; i++)
		if (mChecked[i] == false)
			n--;
	while (n > k)
	{
		for (int i = 0; i < N; i++)
		{
			if (mChecked[i] == false)
				continue;
			for (int j = i+1; j < N; j++)
				if (mChecked[j] == true && mSimilarityTable[i][j] > max)

					{
						max = mSimilarityTable[i][j];
						x = i;
						y = j;
					}
		}
		Merge(x, y);
		n--;
		x = -1;
		y = -1;
		max = 0;
	}

	ofstream out("cluster.txt");

	out << n << endl;
	for (int i = 0; i < N; i++)
	{
		if (mChecked[i] == false)
			continue;
		out << "Unknown" << endl;
		for (int j = 0; j < mClusters[i].size(); j++)
			out << mClusters[i][j] << " ";
		out << endl;
	}
	out.close();
}


void CCluster::Merge(int pCluster1, int pCluster2)
{
	mSimilarityTable[pCluster1][pCluster1] += mSimilarityTable[pCluster2][pCluster2] + mSimilarityTable[pCluster1][pCluster2];

	vector<pair<string, long double> > temp;
	int x = 0, y = 0, size1 = mClusters[pCluster1].size(), size2 = mClusters[pCluster2].size();
	long double sum = 0.f;

	while ( x < mClustersVectors[pCluster1].size() && y < mClustersVectors[pCluster2].size() )
	{
		if (strcmp(mClustersVectors[pCluster1][x].first.c_str(), mClustersVectors[pCluster2][y].first.c_str()) > 0)
		{
			temp.push_back(mClustersVectors[pCluster2][y]);
			temp[temp.size()-1].second *= (size2 / (size1 + size2));
			y++;
		}
		else if (strcmp(mClustersVectors[pCluster1][x].first.c_str(), mClustersVectors[pCluster2][y].first.c_str()) < 0)
		{
			temp.push_back(mClustersVectors[pCluster1][x]);
			temp[temp.size()-1].second *= (size1 / (size1 + size2));
			x++;
		}
		else
		{
			temp.push_back(mClustersVectors[pCluster1][x]);
			temp[temp.size()-1].second *= size1;
			temp[temp.size()-1].second += mClustersVectors[pCluster2][y].second * size2;
			temp[temp.size()-1].second /= (size1 + size2);
			x++;
			y++;
		}
		sum += temp[temp.size()-1].second * temp[temp.size()-1].second;
	}

	while (x < mClustersVectors[pCluster1].size())
	{
		temp.push_back(mClustersVectors[pCluster1][x]);
		temp[temp.size()-1].second *= (size1 / (size1 + size2));
		sum += temp[temp.size()-1].second * temp[temp.size()-1].second;
		x++;
	}

	while (y < mClustersVectors[pCluster2].size())
	{
		temp.push_back(mClustersVectors[pCluster2][y]);
		temp[temp.size()-1].second *= (size2 / (size1 + size2));
		sum += temp[temp.size()-1].second * temp[temp.size()-1].second;
		y++;
	}

	sum = sqrt(sum);
	for (int i = 0; i < temp.size(); i++)
		temp[i].second /= sum;
	mClustersVectors[pCluster1] = temp;
	mClustersVectors[pCluster2].clear();


	for (int i = 0; i < N; i++)
		if (mChecked[i] == true)
			mSimilarityTable[i][pCluster1] = mSimilarityTable[pCluster1][i] = Similarity(mClustersVectors[pCluster1], mClustersVectors[i]);

	mChecked[pCluster2] = false;
	for (int i = 0; i < mClusters[pCluster2].size(); i++)
		mClusters[pCluster1].push_back(mClusters[pCluster2][i]);
	mClusters[pCluster2].clear();

}


long double CCluster::Similarity(int pDocnum1, int pDocnum2)
{
	long double cos = 0;
	int counter1 = 0, counter2 = 0, size1 = mClusters[pDocnum1].size(), size2 = mClusters[pDocnum2].size();
	vector<pair<string, long double> > pDoc1, pDoc2;
	pDoc1 = mClustersVectors[pDocnum1];
	pDoc2 = mClustersVectors[pDocnum2];


	for (; counter1 < pDoc1.size() && counter2 < pDoc2.size();)
	{
		if (strcmp(pDoc1[counter1].first.c_str(), pDoc2[counter2].first.c_str()) > 0)
			counter2 ++;
		else if (strcmp(pDoc1[counter1].first.c_str(), pDoc2[counter2].first.c_str()) == 0)
		{
			cos += pDoc1[counter1].second * pDoc2[counter2].second;
			counter1++;
			counter2++;
		}
		else
			counter1++;
	}

	return cos;
}

//long double CCluster::Similarity(vector<pair<string, long double> > &pDoc1, vector<pair<string, long double> > &pDoc2)
//{
//	long double cos = 0;
//	int counter1 = 0, counter2 = 0;
//
//	for (; counter1 < pDoc1.size() && counter2 < pDoc2.size();)
//	{
//		if (strcmp(pDoc1[counter1].first.c_str(), pDoc2[counter2].first.c_str()) > 0)
//			counter2 ++;
//		else if (strcmp(pDoc1[counter1].first.c_str(), pDoc2[counter2].first.c_str()) == 0)
//		{
//			cos += pDoc1[counter1].second * pDoc2[counter2].second;
//			counter1++;
//			counter2++;
//		}
//		else
//			counter1++;
//	}
//
//	return cos;
//}
