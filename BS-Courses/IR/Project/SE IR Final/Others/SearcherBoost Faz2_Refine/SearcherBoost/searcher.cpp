#include "searcher.h"
//#include <QString>
//#include <QDir>
#include "stem.h"
bool mycomp(pair<long double,int> a,pair<long double,int> b )
		{
			return a.first>b.first ;
		}

void CSearcher::ProcessDoc(int fileNumber) // make inverted index
{
	char c[100], line[1000], *temp;
	string s(TARGETFOLDER);
	s = s + string(docs[fileNumber]);

	ifstream in(s.c_str());

	do
	{
		in.getline(line, 1000);
		temp = strtok(line, " .,:;'’\"\t[](){}/?!@#$%^&*-_=+`~<>|0123456789");
		while ( temp != NULL)
		{
			strcpy(c, temp);
			for (int i = 0; c[i]; i++)
				c[i] = tolower(c[i]);
			if (stop.find(c) == stop.end())
			{
			//	c[stem(c, 0, strlen(c)-1) +1] = 0;
	
				if (invertedIndex.find(c) == invertedIndex.end())
				{
					//lib[string(c)] = lib.size();
					invertedIndex[string(c)].first = 1;
					invertedIndex[string(c)].second = new CDocNode(fileNumber);
				}
				else
				{
					//invertedIndex[c].first++; // increase total number of term
					if (invertedIndex[c].second->mDoc == fileNumber)
						invertedIndex[c].second->mFreq++;
					else
					{
						invertedIndex[c].first++; // increase number of Doc
						invertedIndex[c].second = new CDocNode(fileNumber, invertedIndex[c].second);
					}
				}
			}
			temp = strtok(NULL, " .,:;'’\"\t[](){}/?!@#$%^&*-_=+`~<>|0123456789");
		}

	}while(!in.eof());

}





CSearcher::CSearcher()
{
	stop.insert("a"); stop.insert("about"); stop.insert("above");stop.insert("across"); stop.insert("after"); stop.insert("afterwards"); stop.insert("again"); stop.insert("against"); stop.insert("all"); stop.insert("almost"); stop.insert("alone"); stop.insert("along"); stop.insert("already"); stop.insert("also"); stop.insert("although"); stop.insert("always"); stop.insert("am"); stop.insert("among"); stop.insert("amongst"); stop.insert("amoungst"); stop.insert("amount"); stop.insert("an"); stop.insert("and"); stop.insert("another"); stop.insert("any"); stop.insert("anyhow"); stop.insert("anyone"); stop.insert("anything"); stop.insert("anyway"); stop.insert("anywhere"); stop.insert("are"); stop.insert("around"); stop.insert("as"); stop.insert("at"); stop.insert("back"); stop.insert("be"); stop.insert("became"); stop.insert("because"); stop.insert("become"); stop.insert("becomes"); stop.insert("becoming"); stop.insert("been"); stop.insert("before"); stop.insert("beforehand"); stop.insert("behind"); stop.insert("being"); stop.insert("below"); stop.insert("beside"); stop.insert("besides"); stop.insert("between"); stop.insert("beyond"); stop.insert("bill"); stop.insert("both"); stop.insert("bottom"); stop.insert("but"); stop.insert("by"); stop.insert("call"); stop.insert("can"); stop.insert("cannot"); stop.insert("cant"); stop.insert("co"); stop.insert("computer"); stop.insert("con"); stop.insert("could"); stop.insert("couldnt"); stop.insert("cry"); stop.insert("de"); stop.insert("describe"); stop.insert("detail"); stop.insert("do"); stop.insert("done"); stop.insert("down"); stop.insert("due"); stop.insert("during"); stop.insert("each"); stop.insert("eg"); stop.insert("eight"); stop.insert("either"); stop.insert("eleven"); stop.insert("else"); stop.insert("elsewhere"); stop.insert("empty"); stop.insert("enough"); stop.insert("etc"); stop.insert("even"); stop.insert("ever"); stop.insert("every"); stop.insert("everyone"); stop.insert("everything"); stop.insert("everywhere"); stop.insert("except"); stop.insert("few"); stop.insert("fifteen"); stop.insert("fify"); stop.insert("fill"); stop.insert("find"); stop.insert("fire"); stop.insert("first"); stop.insert("five"); stop.insert("for"); stop.insert("former"); stop.insert("formerly"); stop.insert("forty"); stop.insert("found"); stop.insert("four"); stop.insert("from"); stop.insert("front"); stop.insert("full"); stop.insert("further"); stop.insert("get"); stop.insert("give"); stop.insert("go"); stop.insert("had"); stop.insert("has"); stop.insert("hasnt"); stop.insert("have"); stop.insert("he"); stop.insert("hence"); stop.insert("her"); stop.insert("here"); stop.insert("hereafter"); stop.insert("hereby"); stop.insert("herein"); stop.insert("hereupon"); stop.insert("hers"); stop.insert("herself"); stop.insert("him"); stop.insert("himself"); stop.insert("his"); stop.insert("how"); stop.insert("however"); stop.insert("hundred"); stop.insert("i"); stop.insert("ie"); stop.insert("if"); stop.insert("in"); stop.insert("inc"); stop.insert("indeed"); stop.insert("interest"); stop.insert("into"); stop.insert("is"); stop.insert("it"); stop.insert("its"); stop.insert("itself"); stop.insert("keep"); stop.insert("last"); stop.insert("latter"); stop.insert("latterly"); stop.insert("least"); stop.insert("less"); stop.insert("ltd"); stop.insert("made"); stop.insert("many"); stop.insert("may"); stop.insert("me"); stop.insert("meanwhile"); stop.insert("might"); stop.insert("mill"); stop.insert("mine"); stop.insert("more"); stop.insert("moreover"); stop.insert("most"); stop.insert("mostly"); stop.insert("move"); stop.insert("much"); stop.insert("must"); stop.insert("my"); stop.insert("myself"); stop.insert("name"); stop.insert("namely"); stop.insert("neither"); stop.insert("never"); stop.insert("nevertheless"); stop.insert("next"); stop.insert("nine"); stop.insert("no"); stop.insert("nobody"); stop.insert("none"); stop.insert("noone"); stop.insert("nor"); stop.insert("not"); stop.insert("nothing"); stop.insert("now"); stop.insert("nowhere"); stop.insert("of"); stop.insert("off"); stop.insert("often"); stop.insert("on"); stop.insert("once"); stop.insert("one"); stop.insert("only"); stop.insert("onto"); stop.insert("or"); stop.insert("other"); stop.insert("others"); stop.insert("otherwise"); stop.insert("our"); stop.insert("ours"); stop.insert("ourselves"); stop.insert("out"); stop.insert("over"); stop.insert("own"); stop.insert("part"); stop.insert("per"); stop.insert("perhaps"); stop.insert("please"); stop.insert("put"); stop.insert("rather"); stop.insert("re"); stop.insert("same"); stop.insert("see"); stop.insert("seem"); stop.insert("seemed"); stop.insert("seeming"); stop.insert("seems"); stop.insert("serious"); stop.insert("several"); stop.insert("she"); stop.insert("should"); stop.insert("show"); stop.insert("side"); stop.insert("since"); stop.insert("sincere"); stop.insert("six"); stop.insert("sixty"); stop.insert("so"); stop.insert("some");
	stop.insert("somehow"); stop.insert("someone"); stop.insert("something"); stop.insert("sometime"); stop.insert("sometimes"); stop.insert("somewhere"); stop.insert("still"); stop.insert("such"); stop.insert("system"); stop.insert("take"); stop.insert("ten"); stop.insert("than"); stop.insert("that"); stop.insert("the"); stop.insert("their"); stop.insert("them"); stop.insert("themselves"); stop.insert("then"); stop.insert("thence"); stop.insert("there"); stop.insert("thereafter"); stop.insert("thereby"); stop.insert("therefore"); stop.insert("therein"); stop.insert("thereupon"); stop.insert("these"); stop.insert("they"); stop.insert("thick"); stop.insert("thin"); stop.insert("third"); stop.insert("this"); stop.insert("those"); stop.insert("though"); stop.insert("three"); stop.insert("through"); stop.insert("throughout"); stop.insert("thru"); stop.insert("thus"); stop.insert("to"); stop.insert("together"); stop.insert("too"); stop.insert("top"); stop.insert("toward"); stop.insert("towards"); stop.insert("twelve"); stop.insert("twenty"); stop.insert("two"); stop.insert("un"); stop.insert("under"); stop.insert("until"); stop.insert("up"); stop.insert("upon"); stop.insert("us"); stop.insert("very"); stop.insert("via"); stop.insert("was"); stop.insert("we"); stop.insert("well"); stop.insert("were"); stop.insert("what"); stop.insert("whatever"); stop.insert("when"); stop.insert("whence"); stop.insert("whenever"); stop.insert("where"); stop.insert("whereafter"); stop.insert("whereas"); stop.insert("whereby"); stop.insert("wherein"); stop.insert("whereupon"); stop.insert("wherever"); stop.insert("whether"); stop.insert("which"); stop.insert("while"); stop.insert("whither"); stop.insert("who"); stop.insert("whoever"); stop.insert("whole"); stop.insert("whom"); stop.insert("whose"); stop.insert("why"); stop.insert("will"); stop.insert("with"); stop.insert("within"); stop.insert("without"); stop.insert("would"); stop.insert("yet"); stop.insert("you"); stop.insert("your"); stop.insert("yours"); stop.insert("yourself"); stop.insert("yourselves"); stop.insert("b"); stop.insert("c"); stop.insert("d"); stop.insert("e"); stop.insert("f"); stop.insert("g"); stop.insert("h"); stop.insert("i"); stop.insert("j"); stop.insert("k"); stop.insert("l"); stop.insert("m"); stop.insert("n"); stop.insert("o"); stop.insert("p"); stop.insert("q"); stop.insert("r"); stop.insert("s"); stop.insert("t"); stop.insert("u"); stop.insert("v"); stop.insert("w"); stop.insert("x"); stop.insert("y"); stop.insert("z"); 0;
}


void CSearcher::MakeIndex()
{
	// Reading corpus//
	DIR *dir;
	dirent *ent;
	dir = opendir(TARGETFOLDER);
	if (!dir)
	{
		printf ("opendir() failure; terminating");
		exit(1);
	}

	while ( (ent = readdir(dir)) )
	{
		if (!strcmp(ent->d_name,".") || !strcmp(ent->d_name,"..") )
			continue;

		docs.push_back(ent->d_name);

		ProcessDoc(docs.size()-1);
	}

	closedir(dir);
	/*
	QDir directory(TARGETFOLDER);
	directory.setFilter(QDir::Files);
	QStringList filesName = directory.entryList() ;
	for ( int i=0; i<filesName.size(); ++i )
	{
		docs.push_back(filesName[i].toStdString());
	//------------------- Processing Documents -------------------------
		ProcessDoc(docs.size()-1);
	}*/

/*
	//------------------- Making Document Vectors ----------------------
	documentVectors.resize(docs.size());
	for (map<string, pair<int, CDocsFreq*> >::iterator i = invertedIndex.begin(); i != invertedIndex.end(); ++i)
	{
		CDocsFreq *r = i->second.second;
		for (int j = 0; j < i->second.first; j++)
		{
			long double w;
			w = (1 + log10((long double)r->mFreq)) * log10((long double)docs.size() / (long double)i->second.first);
			documentVectors[r->mDoc].push_back(pair<string, long double>(i->first, w));
			r = r->mNext;
		}
	}

	//----------------- Normalizing Document Vectors -------------------
	for (int i = 0; i < documentVectors.size(); i++)
	{
		long double norm = 0;
		for (int j = 0; j < documentVectors[i].size(); j++)
			norm += (documentVectors[i][j].second) * (documentVectors[i][j].second);
		norm = sqrt(norm);
		for (int j = 0; j < documentVectors[i].size(); j++)
			documentVectors[i][j].second /= norm;
	}
*/
}
vector<int> CSearcher::SearchWithQuery(const char * q)
{
	char query[100],*temp;
	strcpy(query,q);
	//long long double query_vector_size;
	map<string,int> queryVec;

		//queryVector.insert(queryVector.begin(),queryVector.size(),0); //clear queryVector
		//query_vector_size=0;
		if(query[0]==0)
			return vector<int>() ;
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
			//	c[stem(c, 0, strlen(c)-1) +1] = 0;
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
			return vector<int>();
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
		
		/*map<string,int>::const_iterator  it=queryVec.begin();
		for(;it!=queryVec.end();it++)
		{
			string curTerm=(*it).first;
			assert(invertedIndex.find(curTerm) != invertedIndex.end());
			long Nt= (*invertedIndex.find(curTerm)).second.first ;
			assert(Nt!=0);
			long double IDF = log10(N/Nt);
			long double TFQuery= 1+log10(long double((*it).second));
			queryVec_size += IDF*TFQuery * IDF*TFQuery ;

			//****** Check exist doc for curTerm *********************/
		/*
			CDocNode * p = (invertedIndex[curTerm]).second;
			while(p!=NULL)
			{
				long double TFDoc = 1+ log10(long double(p->mFreq));
				/************************/
		/*		results[p->mDoc] += IDF * IDF * TFQuery * TFDoc ;
				DocsVec_size[p->mDoc] += IDF * TFDoc * IDF * TFDoc;
				/************************/	
		/*		p=p->mNext;
			}
		}*/
			
		inv::const_iterator  it=invertedIndex.begin();
		int isQuery=-1;
		for(;it!=invertedIndex.end();it++)
		{
			isQuery=-1;
			string curTerm = (*it).first ;
			for(int i=0;i<queryVec.size(); ++ i)
				if( queryVec.find(curTerm)!=queryVec.end())
					isQuery=i;

			long Nt = (*it).second.first ;
			assert(Nt!=0);
			long double IDF = log10(N/Nt);
			long double TFQuery= 1+log10(long double((queryVec[(*it).first])));

			CDocNode * p = (*it).second.second;
				while(p!=NULL)
				{
					long double TFDoc = 1+ log10(long double(p->mFreq));
					/************************/
					if(isQuery)
						results[p->mDoc] += IDF * IDF * TFQuery * TFDoc ;

					DocsVec_size[p->mDoc] += IDF * TFDoc * IDF * TFDoc;
					/************************/	
					p=p->mNext;
				}
			if(isQuery)
				queryVec_size += IDF*TFQuery * IDF*TFQuery ;

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


}

/*vector<int> CSearcher::SearchWithQuery(char *pQuery)
{
	//------------------- Getting Query From User ----------------------
	char *temp, line[1000], c[100];
	vector< pair<string, long double> >query;

	strcpy(line, pQuery);

	temp = strtok(line, " .,:;\"\t[](){}/?!@#$%^&*-_=+`~<>|0123456789");
	while ( temp != NULL)
	{
		strcpy(c, temp);
		for (int i = 0; c[i]; i++)
			c[i] = tolower(c[i]);
		if (stop.find(c) == stop.end())
		{
			c[CPorter::stem(c, 0, strlen(c)-1) +1] = 0;

			string s(c);
			bool f = false;
			for (int i = 0; i < query.size(); i++)
				if (query[i].first == s)
				{
					query[i].second += 1;
					f = true;
					break;
				}

			if (!f)
				query.push_back(pair<string, long double>(s, 1));
		}

		temp = strtok(NULL, " .,:;\"\t[](){}/?!@#$%^&*-_=+`~<>|0123456789");
	}

	sort(query.begin(), query.end(), QueryCompare);

	//------------------- Making The Query Vector ----------------------
	for (int i = 0; i < query.size(); i++)
		query[i].second = (1 + log10(query[i].second))* log10((long double)docs.size() / (long double)invertedIndex[query[i].first].first);

	//------------- Compairing The Query With Documents ----------------

	long double max = 0;
	int maxi = -1;
	map<long double, int> bestDocs;

	for (int i = 0; i < documentVectors.size(); i++)
	{
		long double cos = 0;
		int counter = 0;

		for (int j = 0; j < documentVectors[i].size() && counter < query.size();)
		{
			if (strcmp(documentVectors[i][j].first.c_str(), query[counter].first.c_str()) > 0)
				counter ++;
			else if (strcmp(documentVectors[i][j].first.c_str(), query[counter].first.c_str()) == 0)
			{
				cos += documentVectors[i][j].second * query[counter].second;
				counter++;
				j++;
			}
			else
				j++;

		}

		if (cos != 0)
		{
			bestDocs[cos] = i;
		}

	}

	//--------------- Outputing Results and opening --------------------
	vector<int> reverse;
	int reverseCounter = bestDocs.size()-1;
	reverse.resize(bestDocs.size());
	map<long double, int>::iterator i = bestDocs.begin();

	for (; i != bestDocs.end(); ++i)
	{
		reverse[reverseCounter] = i->second;
		reverseCounter--;
	}

	return reverse;
}


void CSearcher::ProcessDoc(int pFile)
{
	char c[100], line[1000], *temp;
	string s(TARGETFOLDER);
	s = s + string(docs[pFile]);

	ifstream in(s.c_str());

	do
	{
		in.getline(line, 1000);
		temp = strtok(line, " .,:;\"\t[](){}/?!@#$%^&*-_=+`~<>|0123456789");
		while ( temp != NULL)
		{
			strcpy(c, temp);
			for (int i = 0; c[i]; i++)
				c[i] = tolower(c[i]);
			if (stop.find(c) == stop.end())
			{
				c[CPorter::stem(c, 0, strlen(c)-1) +1] = 0;
				if (invertedIndex.find(c) == invertedIndex.end())
				{
					invertedIndex[string(c)].first = 1;
					invertedIndex[string(c)].second = new CDocsFreq(pFile);
				}
				else
				{
					if (invertedIndex[c].second->mDoc == pFile)
						invertedIndex[c].second->mFreq++;
					else
					{
						invertedIndex[c].second = new CDocsFreq(pFile, invertedIndex[c].second);
						invertedIndex[c].first++;
					}
				}
			}
			temp = strtok(NULL, " .,:;\"\t[](){}/?!@#$%^&*-_=+`~<>|0123456789");
		}

	}while(!in.eof());

}
*/