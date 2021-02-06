#include "searcher.h"

int main()
{
	CSearcher *a=new CSearcher;
	a->MakeIndex();
	
	a->SearchWithQuery("love best");

	return 0;
}
