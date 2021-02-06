#include "searcher.h"

/*#include <boost/serialization/map.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include <boost/serialization/throw_exception.hpp>

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
//#include <boost/archive/binary_oarchive.hpp>
//#include <boost/archive/binary_iarchive.hpp>
*/




// ********************* Storage Structure ******************


/**************************/
//map<string, int> lib;
//vector<pair<vector<unsigned long long double>,int>> table; //int: size of long double* ( size of vector )
//vector<unsigned long long double> docVecSize; //int: size of each doc's vector



/*void vectorValidatation(long long double *queryVector)
{
	
	for(map<string, int>::iterator i=lib.begin(); i!=lib.end();i++)
	{
		if( queryVector[(*i).second]!=0)
		{
			if(queryVector[(*i).second]<=0)
				cout<<"BOOGHJ";
			cout<<(*i).first<<" : "<<queryVector[(*i).second]<<endl;
		}
	}
}*/



/*void makeVectorial()
{
	int max=lib.size();
	for(vector<string>::iterator i=docs.begin(); i!=docs.end() ; i++ )
	{
		table.push_back(pair<vector<unsigned long long double>,int>(vector<unsigned long long double>(max,0),max));
	}
	int N=docs.size() ;
	for(inv::iterator i=invertedIndex.begin(); i!=invertedIndex.end() ; i++ )
	{
		// per each token
		int index=lib[(*i).first];
		long double Nt=(*i).second.first;
		if(Nt==0)
			exit(0);
		long double idf=log10(N/Nt);
		if(idf<=0);
			//cout<<"BOOGH"; // formala bug

		CDocNode* j=(*i).second.second;
		while(j!=NULL)
		{
			if(j->mFreq==0)
				cout<<"BOOOgh";
			if((1+log10(long double(j->mFreq)))* idf <0)
				cout<<"BOOHH ";
			(table[j->mDoc].first)[index]=(1+log10(long double(j->mFreq)))* idf ;
			j=j->mNext;
		}
	}

	for(int i=0; i<table.size(); i++ )
	{
		long long double t=0;
		cout<<"Indexing vector doc :: "<<docs[i] <<" :\n";
		//vectorValidatation(table[i].first);
		for(int j=0; j<table[i].second; j++ )
		{
			if(t>0 && t+(table[i].first)[j] * (table[i].first)[j] < 0 )
				cout<<"BABABAAA !!";
			long long double temp = (table[i].first)[j] ;
			temp = temp * temp ;
			t+=temp;
		}
		docVecSize.push_back(sqrt(long long double(t)));
		cout<< endl ;
	}

}*/

/*------------- Serializing File *********************
void saveXML(){
	ofstream out("CorpusXML.xml");
	boost::archive::xml_oarchive arch(out) ;
	arch << boost::serialization::make_nvp("GROUP", invertedIndex );
	out.close();

}

void saveBIN()
{
	ofstream out("CorpusBIN.dat");
	boost::archive::binary_oarchive arch(out) ;
	arch << invertedIndex ;
	out.close();

}

//------------ unSerializing File *********************
int loadXML(){
	try{
		ifstream in("CorpusXML.xml");
		boost::archive::xml_iarchive arch(in) ;
		arch >> boost::serialization::make_nvp("GROUP", invertedIndex );
		in.close();
	}

	catch (boost::archive::archive_exception e)
	{
		cout<< e.what() <<endl;
		return NULL;
	}
}
int loadBIN(){
	try{
		ifstream in("CorpusBIN.dat");
		boost::archive::binary_iarchive arch(in) ;
		arch >> invertedIndex;;
		in.close();
	}
	catch (boost::archive::archive_exception e)
	{
		cout<< e.what() <<endl;
		return NULL;
	}
}*/
//----------------------- Stop Words----------------


//-----------------------------------------------
// ******************* Main *********************
int main()
{
	/*initial();

	_int64 t1;
	
	// Reading corpus//
	DIR *dir;
	dirent *ent;
	dir = opendir(TARGETFOLDER);
	if (!dir)
	{
		printf ("opendir() failure; terminating");
		exit(1);
	}

	StartTimer(&t1);

	while ( (ent = readdir(dir)) )
	{
		if (!strcmp(ent->d_name,".") || !strcmp(ent->d_name,"..") )
			continue;

		docs.push_back(ent->d_name);

		ProcessDoc(docs.size()-1);
	}

	cout <<"making inverted index takes ... " << StopTimer(t1) <<" ms\n";
	StartTimer(&t1);

	closedir(dir);*/
	/***************************/

//	cout<<"WOWOWWW : "<<(*invertedIndex.begin()).first<<endl;
//	makeVectorial();

	// SAVE 
	//saveXML();
	
	// LOAD 
	//loadXML();

	//cout <<"making Vectorial table takes ... " << StopTimer(t1) << "ms\n";

	/****** Processing Query **********/
	char query[100], *temp;
	//long long double query_vector_size;
	map<string,int> queryVec;

	while(true){
		//queryVector.insert(queryVector.begin(),queryVector.size(),0); //clear queryVector
		//query_vector_size=0;
		cout<<"\n***Enter yout Query : ";
		cin.getline(query, 100);
		if(query[0]==0)
			break;
		temp = strtok(query, " .,:;'’\"\t[](){}/?!@#$%^&*-_=+`~<>|");
		cout<< "*your query vector created for :  \" ";
		while ( temp!=NULL )
		{
			char c[100];
			strcpy(c,temp);
			for (int i = 0; c[i]; i++)
					c[i] = tolower(c[i]);

			if (stop.find(c) == stop.end()) // if isn't stopword ..
			{
				c[stem(c, 0, strlen(c)-1) +1] = 0;
				if (invertedIndex.find(c) != invertedIndex.end()) // if exist in any corpus's doc ..
				{
					if(queryVec.find(string(c))==queryVec.end() )
						queryVec[string(c)]=1;
					else
						(*queryVec.find(string(c))).second ++;


					/*query_vector_size -=  (queryVector[lib[string(c)]] * queryVector[lib[string(c)]]);
					queryVector[lib[string(c)]]++;	
					query_vector_size += (queryVector[lib[string(c)]] * queryVector[lib[string(c)]] );*/
				}
				else
					cout<<"#"; // mean entered word in in none of our docs !	
			}	
			else
				cout<<"*"; // mean a stop word
			cout<<c<<" ";
			temp = strtok(NULL, " .,:;'’\"\t[](){}/?!@#$%^&*-_=+`~<>|");
		}
		cout<<"\"\n";
		// now query consist of words : 1) is in both qury and corpus 2) is not stopword

		
		if(queryVec.size()==0)
		{
			cout<<"Query vector size = 0 !!!\n" ;
			continue;
		}
		//else
		//	query_vector_size = sqrt(long long double(query_vector_size)) ;
		
		/** validating query Vector ***/
		//vectorValidatation(queryVector);
		// Comapring Query with table's Doc


		// NEW //
		long double N=docs.size();		
		// sim(Q,d)= ( Q.d) / ( Q_size * d_size)
		long double *results=new long double[N]; // Q . d[i]
		long double queryVec_size=0;
		long double *DocsVec_size=new long double[N];
		for(int f=0;f<N;f++)
		{
			results[f]=0;
			DocsVec_size[f]=0;
		}
		
		map<string,int>::const_iterator  it=queryVec.begin();
		for(;it!=queryVec.end();it++)
		{
			string curTerm=(*it).first;
			assert(invertedIndex.find(curTerm) != invertedIndex.end());
			long Nt= (*invertedIndex.find(curTerm)).second.first ;
			assert(Nt!=0);
			long double IDF = log10(N/Nt);
			long double TFQuery= 1+log10(long double((*it).second));
			queryVec_size += IDF*TFQuery * IDF*TFQuery ;

			/******* Check exist doc for curTerm **********************/
			CDocNode * p = (invertedIndex[curTerm]).second;
			while(p!=NULL)
			{
				long double TFDoc = 1+ log10(long double(p->mFreq));
				/************************/
				results[p->mDoc] += IDF * IDF * TFQuery * TFDoc ;
				DocsVec_size[p->mDoc] += IDF * TFDoc * IDF * TFDoc;
				/************************/	
				p=p->mNext;
			}
		}
		vector<pair<long double,int>> final_result;
		for(int i=0; i<N; i++)
		{
			if(results[i]!=0)
			{
				assert(queryVec_size!=0);
				assert(DocsVec_size[i]!=0);

				final_result.push_back(pair<long double,int>(results[i]/sqrt((queryVec_size*DocsVec_size[i])),i)); 
			}
		}
		sort(final_result.begin(),final_result.end(),mycomp);
		delete [] results;
		delete [] DocsVec_size;
		queryVec.clear();

		for(int i=0; i<final_result.size(); i++ )
			cout<<">>> "<<docs[final_result[i].second]<< "      :   "<<final_result[i].first <<endl;

		// END_OF_NEW //


	/*	map<long long double,int> result_map;	// grade :: docNumber
		for(int i=0; i<table.size(); i++ )
		{
			long long double below = docVecSize[i] * query_vector_size , above=0;
			if(docVecSize[i]==0)
				continue;
			for(int j=0; j<table[i].second; j++ )
				above += (table[i].first)[j] * queryVector[j] ;
			long long double result = above / below ;
			if(result!=0)
				result_map[result]=i;
		}

		int counter=1;
		cout<<"Result : \n------------------------------\n\n";
		
		vector<pair<long double,int>>::iterator x=final_result.end();
		--x;
		do{
			cout<<counter++<<": "<<docs[(*x).second]<<"\t      score:  "<<(*x).first <<endl ;
		}while((x--)!=final_result.begin());
		cout<<endl;

		cout<<"Enter a number to show Doc : ";
		int inp=0;
		while(cin>>inp , inp!=0 )
		{
			inp++;
			string show("notepad ");
			show.append(TARGETFOLDER);
			x=final_result.begin();
			for(int i=1; i<=(final_result.size()-inp+1) ; i++)
				++x;
			show.append(docs[(*x).second]);
			system(show.c_str());
			show.clear();
			cout<<"Enter a number to show Doc ( 0 to continue): ";
		}
		cin.ignore();*/

	}
	return 0;
}
