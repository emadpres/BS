#include "averagecluster.h"

CAverageCluster::CAverageCluster(CSearcher *pParent)
{
	mParent = pParent;
	N = mParent->docs.size();

	mChecked = new bool[N];
	mClusters = new vector<int> [N];
//	mClustersVectors = new vector<pair<string, long double> > [N];
	mSimilarityTable = new long double *[N];
	mSimDoc = new long double *[N];
	for (int i = 0 ; i < N; i++)
	{
		mSimilarityTable[i] = new long double[N];
		mSimDoc[i] = new long double[N];

		mClusters[i].push_back(i);
//		mClustersVectors[i] = mParent->documentVectors[i];
		if (mParent->documentVectors[i].size())//mClustersVectors[i].size())
			mChecked[i] = true;
		else
			mChecked[i] = false;
	}

	for (int i = 0; i < N; i++)
		for (int j = i; j < N; j++)
			mSimilarityTable[i][j] = mSimilarityTable[j][i] = mSimDoc[i][j] = mSimDoc[j][i] = PreSimilarity(mParent->documentVectors[i], mParent->documentVectors[j]);
}


void CAverageCluster::Cluster(int k)
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
                {
                    string s = mParent->docs[mClusters[i][j]];
                    char c[100];
                    for (int i = 0; i < s.size(); i++)
                        if (s[i] != '.')
                            c[i] = s[i];
                        else
                        {
                            c[i] = 0;
                            break;
                        }
                        out << c << " ";
                }
		out << endl;
	}
	out.close();
}


void CAverageCluster::Merge(int pCluster1, int pCluster2)
{
//	mSimilarityTable[pCluster1][pCluster1] += mSimilarityTable[pCluster2][pCluster2] + mSimilarityTable[pCluster1][pCluster2];

/*	vector<pair<string, long double> > temp;
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

*/
	mChecked[pCluster2] = false;
	for (int i = 0; i < mClusters[pCluster2].size(); i++)
		mClusters[pCluster1].push_back(mClusters[pCluster2][i]);


	for (int i = 0; i < N; i++)
		if (mChecked[i] == true)
			mSimilarityTable[i][pCluster1] = mSimilarityTable[pCluster1][i] = Similarity(pCluster1, i);

	mClusters[pCluster2].clear();

}


long double CAverageCluster::Similarity(int pDocnum1, int pDocnum2)
{
/*	long double cos = 0, sum = 0.f;
	int x = 0, y = 0, size1 = mClusters[pDocnum1].size(), size2 = mClusters[pDocnum2].size();
	vector<pair<string, long double> > pDoc1, pDoc2, temp;


	while ( x < mClustersVectors[pDocnum1].size() && y < mClustersVectors[pDocnum2].size() )
	{
		if (strcmp(mClustersVectors[pDocnum1][x].first.c_str(), mClustersVectors[pDocnum2][y].first.c_str()) > 0)
		{
			temp.push_back(mClustersVectors[pDocnum2][y]);
			temp[temp.size()-1].second *= size2;
			y++;
		}
		else if (strcmp(mClustersVectors[pDocnum1][x].first.c_str(), mClustersVectors[pDocnum2][y].first.c_str()) < 0)
		{
			temp.push_back(mClustersVectors[pDocnum1][x]);
			temp[temp.size()-1].second *= size1;
			x++;
		}
		else
		{
			temp.push_back(mClustersVectors[pDocnum1][x]);
			temp[temp.size()-1].second *= size1;
			temp[temp.size()-1].second += mClustersVectors[pDocnum2][y].second * size2;
			x++;
			y++;
		}
		sum += temp[temp.size()-1].second * temp[temp.size()-1].second;
	}

	while (x < mClustersVectors[pDocnum1].size())
	{
		temp.push_back(mClustersVectors[pDocnum1][x]);
		temp[temp.size()-1].second *= size1;
		sum += temp[temp.size()-1].second * temp[temp.size()-1].second;
		x++;
	}

	while (y < mClustersVectors[pDocnum2].size())
	{
		temp.push_back(mClustersVectors[pDocnum2][y]);
		temp[temp.size()-1].second *= size2;
		sum += temp[temp.size()-1].second * temp[temp.size()-1].second;
		y++;
	}

	sum = sqrt(sum);
	for (int i = 0; i < temp.size(); i++)
	{
//		temp[i].second /= sum;
		cos += temp[i].second * temp[i].second;
	}
	cos -= (size1 + size2);
	cos /= ((size1 + size2) * (size1 + size2 - 1));
*/
	long double cos = 0;
	int size = 0;
	vector<int> dm;
	for (int i = 0; i < mClusters[pDocnum1].size(); i++)
		dm.push_back(mClusters[pDocnum1][i]);
	for (int i = 0; i < mClusters[pDocnum2].size(); i++)
		dm.push_back(mClusters[pDocnum2][i]);

	size = dm.size();
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
				cos += mSimDoc[dm[i]][dm[j]];

	cos -= size;
	cos /= (size * (size-1));

	return cos;
}

long double CAverageCluster::PreSimilarity(vector<pair<string, long double> > &pDoc1, vector<pair<string, long double> > &pDoc2)
{
	long double cos = 0;
	int counter1 = 0, counter2 = 0;

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
