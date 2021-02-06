#include "searcher.h"
#include <QString>
#include <QDir>



bool QueryCompare(pair<string, long double> a, pair<string, long double> b)
{
	if (strcmp(a.first.c_str(), b.first.c_str()) > 0)
		return false;
	return true;
}

bool CosCompare(pair<long double, int> a, pair<long double, int> b)
{
	if (a.first > b.first)
		return true;

	return false;
}


CSearcher::CSearcher()
{

	//------------------------------------------------------------------

	stop["a"] = stop["about"] = stop["above"] = stop["across"] = stop["after"] = stop["afterwards"] = stop["again"] = stop["against"] = stop["all"] = stop["almost"] = stop["alone"] = stop["along"] = stop["already"] = stop["also"] = stop["although"] = stop["always"] = stop["am"] = stop["among"] = stop["amongst"] = stop["amoungst"] = stop["amount"] = stop["an"] = stop["and"] = stop["another"] = stop["any"] = stop["anyhow"] = stop["anyone"] = stop["anything"] = stop["anyway"] = stop["anywhere"] = stop["are"] = stop["around"] = stop["as"] = stop["at"] = 0;
	stop["back"] = stop["be"] = stop["became"] = stop["because"] = stop["become"] = stop["becomes"] = stop["becoming"] = stop["been"] = stop["before"] = stop["beforehand"] = stop["behind"] = stop["being"] = stop["below"] = stop["beside"] = stop["besides"] = stop["between"] = stop["beyond"] = stop["bill"] = stop["both"] = stop["bottom"] = stop["but"] = stop["by"] = 0;
	stop["call"] = stop["can"] = stop["cannot"] = stop["cant"] = stop["co"] = stop["computer"] = stop["con"] = stop["could"] = stop["couldnt"] = stop["cry"] = 0;
	stop["de"] = stop["describe"] = stop["detail"] = stop["do"] = stop["done"] = stop["down"] = stop["due"] = stop["during"] = 0;
	stop["each"] = stop["eg"] = stop["eight"] = stop["either"] = stop["eleven"] = stop["else"] = stop["elsewhere"] = stop["empty"] = stop["enough"] = stop["etc"] = stop["even"] = stop["ever"] = stop["every"] = stop["everyone"] = stop["everything"] = stop["everywhere"] = stop["except"] = stop["few"] = stop["fifteen"] = stop["fify"] = stop["fill"] = stop["find"] = stop["fire"] = stop["first"] = stop["five"] = stop["for"] = stop["former"] = stop["formerly"] = stop["forty"] = stop["found"] = stop["four"] = stop["from"] = stop["front"] = stop["full"] = stop["further"] = stop["get"] = stop["give"] = stop["go"] = stop["had"] = stop["has"] = stop["hasnt"] = stop["have"] = stop["he"] = stop["hence"] = stop["her"] = stop["here"] = stop["hereafter"] = stop["hereby"] = stop["herein"] = stop["hereupon"] = stop["hers"] = stop["herself"] = stop["him"] = stop["himself"] = stop["his"] = stop["how"] = stop["however"] = stop["hundred"] = stop["i"] = stop["ie"] = stop["if"] = stop["in"] = stop["inc"] = stop["indeed"] = stop["interest"] = stop["into"] = stop["is"] = stop["it"] = stop["its"] = stop["itself"] = stop["keep"] = stop["last"] = stop["latter"] = stop["latterly"] = stop["least"] = stop["less"] = stop["ltd"] = stop["made"] = stop["many"] = stop["may"] = stop["me"] = stop["meanwhile"] = stop["might"] = stop["mill"] = stop["mine"] = stop["more"] = stop["moreover"] = stop["most"] = stop["mostly"] = stop["move"] = stop["much"] = stop["must"] = stop["my"] = stop["myself"] = stop["name"] = stop["namely"] = stop["neither"] = stop["never"] = stop["nevertheless"] = stop["next"] = stop["nine"] = stop["no"] = stop["nobody"] = stop["none"] = stop["noone"] = stop["nor"] = stop["not"] = stop["nothing"] = stop["now"] = stop["nowhere"] = stop["of"] = stop["off"] = stop["often"] = stop["on"] = stop["once"] = stop["one"] = stop["only"] = stop["onto"] = stop["or"] = stop["other"] = stop["others"] = stop["otherwise"] = stop["our"] = stop["ours"] = stop["ourselves"] = stop["out"] = stop["over"] = stop["own"] = stop["part"] = stop["per"] = stop["perhaps"] = stop["please"] = stop["put"] = stop["rather"] = stop["re"] = stop["same"] = stop["see"] = stop["seem"] = stop["seemed"] = stop["seeming"] = stop["seems"] = stop["serious"] = stop["several"] = stop["she"] = stop["should"] = stop["show"] = stop["side"] = stop["since"] = stop["sincere"] = stop["six"] = stop["sixty"] = stop["so"] = stop["some"] = stop["somehow"] = stop["someone"] = stop["something"] = stop["sometime"] = stop["sometimes"] = stop["somewhere"] = stop["still"] = stop["such"] = stop["system"] = stop["take"] = stop["ten"] = stop["than"] = stop["that"] = stop["the"] = stop["their"] = stop["them"] = stop["themselves"] = stop["then"] = stop["thence"] = stop["there"] = stop["thereafter"] = stop["thereby"] = stop["therefore"] = stop["therein"] = stop["thereupon"] = stop["these"] = stop["they"] = stop["thick"] = stop["thin"] = stop["third"] = stop["this"] = stop["those"] = stop["though"] = stop["three"] = stop["through"] = stop["throughout"] = stop["thru"] = stop["thus"] = stop["to"] = stop["together"] = stop["too"] = stop["top"] = stop["toward"] = stop["towards"] = stop["twelve"] = stop["twenty"] = stop["two"] = stop["un"] = stop["under"] = stop["until"] = stop["up"] = stop["upon"] = stop["us"] = stop["very"] = stop["via"] = stop["was"] = stop["we"] = stop["well"] = stop["were"] = stop["what"] = stop["whatever"] = stop["when"] = stop["whence"] = stop["whenever"] = stop["where"] = stop["whereafter"] = stop["whereas"] = stop["whereby"] = stop["wherein"] = stop["whereupon"] = stop["wherever"] = stop["whether"] = stop["which"] = stop["while"] = stop["whither"] = stop["who"] = stop["whoever"] = stop["whole"] = stop["whom"] = stop["whose"] = stop["why"] = stop["will"] = stop["with"] = stop["within"] = stop["without"] = stop["would"] = stop["yet"] = stop["you"] = stop["your"] = stop["yours"] = stop["yourself"] = stop["yourselves"] = 0;
	stop["b"] = stop["c"] = stop["d"] = stop["e"] = stop["f"] = stop["g"] = stop["h"] = stop["i"] = stop["j"] = stop["k"] = stop["l"] = stop["m"] = stop["n"] = stop["o"] = stop["p"] = stop["q"] = stop["r"] = stop["s"] = stop["t"] = stop["u"] = stop["v"] = stop["w"] = stop["x"] = stop["y"] = stop["z"] = 0;


}


void CSearcher::MakeIndex()
{

	QDir directory(TARGETFOLDER);
	directory.setFilter(QDir::Files);
	QStringList filesName = directory.entryList() ;
	for ( int i=0; i<filesName.size(); ++i )
	{
		docs.push_back(filesName[i].toStdString());
	//------------------- Processing Documents -------------------------
		ProcessDoc(docs.size()-1);
	}


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

}


vector<int> CSearcher::SearchWithQuery(const char *pQuery)
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
	vector< pair<long double, int> > bestDocs;
	bestDocs.resize(documentVectors.size());

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
			bestDocs[i] = pair<long double, int>(cos, i);
		}

	}

	sort(bestDocs.begin(), bestDocs.end(), CosCompare);
	//--------------- Outputing Results and opening --------------------
	vector<int> reverse;

	int i = 0;
	while(bestDocs[i].first != 0)
	{
		reverse.push_back(bestDocs[i].second);
		i++;
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
