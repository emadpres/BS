#include <iostream>
#include <boost/container/vector.hpp>
using namespace std;
namespace container = boost::container;

#include <wrench/foreach.h>

int main() {

	container::vector<int> v;
	for(int i=0; i<10; i++) v.push_back(i);

	foreach(int i, v) {
		cout << i << endl;
	}
}

