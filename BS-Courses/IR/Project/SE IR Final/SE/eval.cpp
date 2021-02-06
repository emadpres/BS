#include "eval.h"
#include <fstream>
#include <stdlib.h>
using namespace std;

eval::eval(string Pcluster_name,string Pclass_name, double *pRI, double *pPurity)
{
        mRI=pRI;
        mPurity=pPurity;
	RI=Purity=0;
	cluster_name=Pcluster_name;
	class_name=Pclass_name;
}

void eval::Run()
{
	ifstream inpClusters(class_name.c_str());
	ifstream inpMyCluster(cluster_name.c_str());

	int num_of_cluster=0,num_of_mycluster=0;
	int N=0;  // real #doc
	int _N=0;

	//**** Reading Clusters *******//
	string topic,temp;
	while(inpClusters>>temp)
	{
		if(temp[0]>='0' && temp[0]<='9' )
		{
			_N++;
                        int num = atoi(temp.c_str()) ;
			if(clusters.find(num)==clusters.end())
			{
				N++;
				clusters[num] = vector<string>();
			}
			clusters[num].push_back(topic);

		}
		else
		{
			topic=temp;
			clusters_list[topic] = num_of_cluster;  // make a uniq list of all topic with it's indexes
			num_of_cluster++;
		}
	}
        inpClusters.close();

        //cout<<"> "<<num_of_cluster<<"  Clusters ! \n\n";

	
	//**** Reading MyClusters *******//

	inpMyCluster >> num_of_mycluster;

	int **table=new int*[num_of_mycluster];
	for ( int i=0; i<num_of_mycluster ; ++i )
		table[i] = new int [num_of_cluster];
	for ( int i=0; i< num_of_mycluster; ++i )
		for ( int j=0; j< num_of_cluster; ++j )
			table[i][j]=0;

	//**************************************//
	int tableTotal=0;
	int *total_row = new int[num_of_cluster];
	for ( int i=0; i< num_of_cluster; ++i )
		total_row[i]=0;
	
	int *total_col = new int[num_of_mycluster];
	for ( int i=0; i< num_of_mycluster; ++i )
		total_col[i]=0;

	topic=temp="";
	int cur_cluster=-1;
	int cur_cluster_max=0;

	while(inpMyCluster>>temp)
	{
		if(temp[0]>='0' && temp[0]<='9' )
		{
			int num = atoi(temp.c_str()) ;
			for(int i=0; i<clusters[num].size(); ++i )
			{
				string doc_topic = clusters[num][i] ;
				// find maximum of curuent_myCluster
				int tmp = ++table[cur_cluster][clusters_list[doc_topic]] ;
				if ( tmp > cur_cluster_max )
					cur_cluster_max = tmp;

				total_col[cur_cluster]++;
				total_row[clusters_list[doc_topic]]++;
			}
		}
		else //next myCluster
		{
			if(cur_cluster>=0)
				tableTotal += total_col[cur_cluster];
			cur_cluster++;
			Purity += cur_cluster_max ;  // Calc of Purity_Numerator
			cur_cluster_max=-1;
		}
	}
	// calc for last myCluster
	Purity += cur_cluster_max ;
	tableTotal += total_col[cur_cluster];

	Purity /= _N ; // TODO : N is real total num of docs OR should doublicate number of soft_cluster_doc !
					// Here N is number of soft_cluster_doc ;)

        //cout<<">> Purity : "<<Purity<<endl;
        *mPurity = Purity ;

	//********** Calc of IR ***********// O(N^2)?
        //assert( cur_cluster+1 == 	num_of_mycluster ) ;

	int RI_TN=0,RI_TP=0;

	for ( int i=0; i< num_of_mycluster; ++i )
		for ( int j=0; j< num_of_cluster; ++j )
		{
			//TP
			if ( table[i][j]>=2 )
				RI_TP += ( (table[i][j] * (table[i][j]-1)) /2);
			//TN
			if(table[i][j]>0)
				RI_TN += table[i][j]* ( tableTotal - total_col[i] - total_row[j] + table[i][j] ) ;
		}
	RI = RI_TP + (RI_TN/2.0) ;
	RI /= ((tableTotal*(tableTotal-1))/2) ;

        //cout<<">> RI : "<<RI<<endl;
        *mRI = RI ;

}

eval::~eval(){}
