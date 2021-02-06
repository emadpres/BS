#include <iostream>
#include <fstream>
#include <ctype.h>       /* for isupper, islower, tolower */
#include <string>
#include <vector>
#include <string.h>
#include <map>
#include "porter.h"
#include "dirent.h"
#include "myTime.h"

#include <boost/serialization/map.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>

//#include <boost\interprocess\containers\container\detail\pair.hpp>
//#include <boost\fusion\include\std_pair.hpp>
//#include <boost\mpl\pair.hpp>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>


//#include <boost\archive\basic_binary_iarchive.hpp>


#include <boost/serialization/throw_exception.hpp>

//-----------------Setting Mode------------------

#define XML
//#define Binary

#define MAKEMODE
#define LOADMODE

#define TARGETFOLDER "./Docs/"

//-----------------------------------------------
#ifdef XML
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#endif
#ifdef Binary
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#endif

//-----------------------------------------------
using namespace std;

struct CDocsFreq
{
	CDocsFreq(int pDoc = 0, CDocsFreq *pNext = NULL)
	{
		mDoc = pDoc;
		mFreq = 1;
		mNext = pNext;
	}
	template<class Archive>
	void serialize(Archive & ar, const unsigned int ver/* file_version */){
#ifdef Binary
		ar & mDoc;
		ar & mFreq;
		ar & mNext;
#endif
#ifdef XML
		ar & boost::serialization::make_nvp("CDocFreqmDoc",mDoc);
		ar & boost::serialization::make_nvp("CDocFreqmFreq",mFreq);
		ar & boost::serialization::make_nvp("CDocFreqmNext",mNext);
#endif

	}


	int mDoc, mFreq;
	CDocsFreq *mNext;
};


//-----------------------------------------------

vector<char*> docs;
map<string, pair<int, CDocsFreq*> > invertedIndex;
map<string, char> stop;

void ProcessDoc(int pFile)
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
						invertedIndex[c].first++;
						invertedIndex[c].second = new CDocsFreq(pFile, invertedIndex[c].second);
					}
				}
			}
			temp = strtok(NULL, " .,:;\"\t[](){}/?!@#$%^&*-_=+`~<>|0123456789");
		}

	}while(!in.eof());

}

//-----------------------------------------------

int main()
{

	_int64 t1;
	//-----------------------------------------------

	stop["a"] = stop["about"] = stop["above"] = stop["across"] = stop["after"] = stop["afterwards"] = stop["again"] = stop["against"] = stop["all"] = stop["almost"] = stop["alone"] = stop["along"] = stop["already"] = stop["also"] = stop["although"] = stop["always"] = stop["am"] = stop["among"] = stop["amongst"] = stop["amoungst"] = stop["amount"] = stop["an"] = stop["and"] = stop["another"] = stop["any"] = stop["anyhow"] = stop["anyone"] = stop["anything"] = stop["anyway"] = stop["anywhere"] = stop["are"] = stop["around"] = stop["as"] = stop["at"] = stop["back"] = stop["be"] = stop["became"] = stop["because"] = stop["become"] = stop["becomes"] = stop["becoming"] = stop["been"] = stop["before"] = stop["beforehand"] = stop["behind"] = stop["being"] = stop["below"] = stop["beside"] = stop["besides"] = stop["between"] = stop["beyond"] = stop["bill"] = stop["both"] = stop["bottom"] = stop["but"] = stop["by"] = stop["call"] = stop["can"] = stop["cannot"] = stop["cant"] = stop["co"] = stop["computer"] = stop["con"] = stop["could"] = stop["couldnt"] = stop["cry"] = stop["de"] = stop["describe"] = stop["detail"] = stop["do"] = stop["done"] = stop["down"] = stop["due"] = stop["during"] = stop["each"] = stop["eg"] = stop["eight"] = stop["either"] = stop["eleven"] = stop["else"] = stop["elsewhere"] = stop["empty"] = stop["enough"] = stop["etc"] = stop["even"] = stop["ever"] = stop["every"] = stop["everyone"] = stop["everything"] = stop["everywhere"] = stop["except"] = stop["few"] = stop["fifteen"] = stop["fify"] = stop["fill"] = stop["find"] = stop["fire"] = stop["first"] = stop["five"] = stop["for"] = stop["former"] = stop["formerly"] = stop["forty"] = stop["found"] = stop["four"] = stop["from"] = stop["front"] = stop["full"] = stop["further"] = stop["get"] = stop["give"] = stop["go"] = stop["had"] = stop["has"] = stop["hasnt"] = stop["have"] = stop["he"] = stop["hence"] = stop["her"] = stop["here"] = stop["hereafter"] = stop["hereby"] = stop["herein"] = stop["hereupon"] = stop["hers"] = stop["herself"] = stop["him"] = stop["himself"] = stop["his"] = stop["how"] = stop["however"] = stop["hundred"] = stop["i"] = stop["ie"] = stop["if"] = stop["in"] = stop["inc"] = stop["indeed"] = stop["interest"] = stop["into"] = stop["is"] = stop["it"] = stop["its"] = stop["itself"] = stop["keep"] = stop["last"] = stop["latter"] = stop["latterly"] = stop["least"] = stop["less"] = stop["ltd"] = stop["made"] = stop["many"] = stop["may"] = stop["me"] = stop["meanwhile"] = stop["might"] = stop["mill"] = stop["mine"] = stop["more"] = stop["moreover"] = stop["most"] = stop["mostly"] = stop["move"] = stop["much"] = stop["must"] = stop["my"] = stop["myself"] = stop["name"] = stop["namely"] = stop["neither"] = stop["never"] = stop["nevertheless"] = stop["next"] = stop["nine"] = stop["no"] = stop["nobody"] = stop["none"] = stop["noone"] = stop["nor"] = stop["not"] = stop["nothing"] = stop["now"] = stop["nowhere"] = stop["of"] = stop["off"] = stop["often"] = stop["on"] = stop["once"] = stop["one"] = stop["only"] = stop["onto"] = stop["or"] = stop["other"] = stop["others"] = stop["otherwise"] = stop["our"] = stop["ours"] = stop["ourselves"] = stop["out"] = stop["over"] = stop["own"] = stop["part"] = stop["per"] = stop["perhaps"] = stop["please"] = stop["put"] = stop["rather"] = stop["re"] = stop["same"] = stop["see"] = stop["seem"] = stop["seemed"] = stop["seeming"] = stop["seems"] = stop["serious"] = stop["several"] = stop["she"] = stop["should"] = stop["show"] = stop["side"] = stop["since"] = stop["sincere"] = stop["six"] = stop["sixty"] = stop["so"] = stop["some"] = stop["somehow"] = stop["someone"] = stop["something"] = stop["sometime"] = stop["sometimes"] = stop["somewhere"] = stop["still"] = stop["such"] = stop["system"] = stop["take"] = stop["ten"] = stop["than"] = stop["that"] = stop["the"] = stop["their"] = stop["them"] = stop["themselves"] = stop["then"] = stop["thence"] = stop["there"] = stop["thereafter"] = stop["thereby"] = stop["therefore"] = stop["therein"] = stop["thereupon"] = stop["these"] = stop["they"] = stop["thick"] = stop["thin"] = stop["third"] = stop["this"] = stop["those"] = stop["though"] = stop["three"] = stop["through"] = stop["throughout"] = stop["thru"] = stop["thus"] = stop["to"] = stop["together"] = stop["too"] = stop["top"] = stop["toward"] = stop["towards"] = stop["twelve"] = stop["twenty"] = stop["two"] = stop["un"] = stop["under"] = stop["until"] = stop["up"] = stop["upon"] = stop["us"] = stop["very"] = stop["via"] = stop["was"] = stop["we"] = stop["well"] = stop["were"] = stop["what"] = stop["whatever"] = stop["when"] = stop["whence"] = stop["whenever"] = stop["where"] = stop["whereafter"] = stop["whereas"] = stop["whereby"] = stop["wherein"] = stop["whereupon"] = stop["wherever"] = stop["whether"] = stop["which"] = stop["while"] = stop["whither"] = stop["who"] = stop["whoever"] = stop["whole"] = stop["whom"] = stop["whose"] = stop["why"] = stop["will"] = stop["with"] = stop["within"] = stop["without"] = stop["would"] = stop["yet"] = stop["you"] = stop["your"] = stop["yours"] = stop["yourself"] = stop["yourselves"] = 0;
	stop["b"] = stop["c"] = stop["d"] = stop["e"] = stop["f"] = stop["g"] = stop["h"] = stop["i"] = stop["j"] = stop["k"] = stop["l"] = stop["m"] = stop["n"] = stop["o"] = stop["p"] = stop["q"] = stop["r"] = stop["s"] = stop["t"] = stop["u"] = stop["v"] = stop["w"] = stop["x"] = stop["y"] = stop["z"] = 0;

	//-----------------------------------------------

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
#ifdef MAKEMODE
		ProcessDoc(docs.size()-1);
#endif
	}

	cout <<"Stage 1 take.. " << StopTimer(t1) << endl;
	StartTimer(&t1);

	closedir(dir);

	//------------- Making XML File -----------------
#ifdef MAKEMODE
#ifdef XML
	ofstream out("CorpusXML.xml");
	boost::archive::xml_oarchive arch(out) ;
	arch << boost::serialization::make_nvp("GROUP", invertedIndex );
#endif
#ifdef Binary
	ofstream out("CorpusBIN.dat");
	boost::archive::binary_oarchive arch(out) ;
	arch << invertedIndex ;
#endif
	out.close();
#endif

	//------------- Loading XML File ----------------
#ifdef LOADMODE
	try{
#ifdef XML

		ifstream in("CorpusXML.xml");
		boost::archive::xml_iarchive arch(in) ;
		arch >> boost::serialization::make_nvp("GROUP", invertedIndex );
#endif
#ifdef Binary
		ifstream in("CorpusBIN.dat");
		boost::archive::binary_iarchive arch(in) ;
		arch >> invertedIndex;;
#endif
		in.close();
	}
	catch (boost::archive::archive_exception e)
	{
		cout<< e.what() <<endl;
		return NULL;
	}
#endif
	cout <<"Stage 2 take.. " << StopTimer(t1) << endl;
	return 0;
}
