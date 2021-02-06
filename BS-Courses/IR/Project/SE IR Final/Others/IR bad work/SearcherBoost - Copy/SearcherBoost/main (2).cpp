#include <iostream>
#include <fstream>
#include <map>
#include <hash_map>
#include <string>
#include <ctype.h>       /* for isupper, islower, tolower */
#include "dirent.h"
#include "stem.h"
#include "myTime.h"

#include <boost/serialization/map.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>


#define MAX_LENGTH  50
#define LETTER(ch) (isupper(ch) || islower(ch))
#define DATA_PATH   "./data/"
using namespace std;

struct A{
	int doc;
	long freq;
	A* next;
	A(int pdoc=0,A* pnext=NULL):doc(pdoc),freq(1),next(pnext){}
	template<class Archive>
    void serialize(Archive & ar, const unsigned int /* file_version */){
        ar & boost::serialization::make_nvp("ADoc",doc);
        ar & boost::serialization::make_nvp("AFreq",freq);
        ar & boost::serialization::make_nvp("Anext",next);
    }
};

std::map<string,A*> index;
std::map<string,A*> loadIndex;
char temp[MAX_LENGTH];

int processDoc(const char * file)
{
	static int docNum=0;
	docNum++;
	ifstream in;

	strcpy(temp,DATA_PATH);
	strcat(temp,file);
	in.open(temp);
	if(!in)
		return -1;
	cout<<"\tFile:\""<<file<<"\"\n";
	///

	while(in>>temp)
	{
		cout<<"\t\tPrc:\""<<temp<<"\"  -->   ";

		//** Proccess a Word

		int k=strlen(temp);
		while(--k>-1)
			if(!LETTER(temp[k]))
				break;

		//if(k==-1)
		{
			temp[stem(temp,0,strlen(temp)-1)+1] = 0;

			//A* a=index[temp];
			if(index.find(temp)==index.end()){
				// new Word
				index[string(temp)]=new A(docNum,NULL);
				cout<<"New Record-> ";
			}
			else
			{
				if(index[temp]->doc==docNum)
					++(index[temp]->freq);
				else
				{
					index[temp]=new A(docNum,index[temp]);
					cout<<"newDoc- ";
				}
			}
		
			cout<<temp<<endl;
		}
	//	else
		{
		//	cout<<"**NA**\n"; // should not steeming !
		}



		
	}


	///
	in.close();
	return true;
}

int main()
{
	_int64 t1;
   

	DIR *pdir;
	struct dirent *pent;
	pdir=opendir("./data"); //"." refers to the current dir
	if (!pdir){
		printf ("opendir() failure; terminating");
		exit(1);
	}
	int a=8;
	if(a=0)
	{
		a=0;
	}
	StartTimer( &t1 );
	while ((pent=readdir(pdir))){
		if(!strcmp(pent->d_name,".") || !strcmp(pent->d_name,"..") )
			continue;
		cout<<"Current : "<<pent->d_name<<"   Indexing... \n";		
		cout<<processDoc(pent->d_name)<<endl;
	}
	cout<<"Time : "<<StopTimer(t1)<<endl;
	closedir(pdir);
	
	// Save
	ofstream out("OUT.xml");
	boost::archive::xml_oarchive arch(out) ;
	arch << boost::serialization::make_nvp("GROUP", index );
	out.close();
	//Load
	ifstream in("OUT.xml");
	boost::archive::xml_iarchive arc(in) ;
	arc >> boost::serialization::make_nvp("GROUP", loadIndex );
	in.close();

	return 0;
}